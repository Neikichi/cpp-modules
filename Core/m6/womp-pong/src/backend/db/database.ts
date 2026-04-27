import Database from 'better-sqlite3';
import path from 'path';
import { fileURLToPath } from 'url';
import fs from 'fs';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Database path - use environment variable or default
const DB_PATH = process.env.DB_PATH || path.join(__dirname, '../../../data/womp-pong.db');

// Create a singleton database connection
let db: Database.Database | null = null;

export function getDatabase(): Database.Database {
	if (!db) {
		// Ensure the data directory exists
		const dbDir = path.dirname(DB_PATH);
		if (!fs.existsSync(dbDir)) {
			fs.mkdirSync(dbDir, { recursive: true });
		}

		db = new Database(DB_PATH, { 
			verbose: process.env.NODE_ENV === 'development' ? console.log : undefined 
		});
		
		// Enable foreign keys
		db.pragma('foreign_keys = ON');
		
		console.log(`📦 SQLite database connected: ${DB_PATH}`);
	}
	
	return db;
}

export function closeDatabase(): void {
	if (db) {
		db.close();
		db = null;
		console.log('📦 SQLite database closed');
	}
}

// Initialize database schema
export function initializeDatabase(): void {
	const database = getDatabase();
	
	// Users table
	database.exec(`
		CREATE TABLE IF NOT EXISTS users (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			username TEXT UNIQUE NOT NULL,
			email TEXT UNIQUE NOT NULL,
			password_hash TEXT NOT NULL,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			last_login DATETIME
		);
	`);

	// Sessions table (for JWT or session tokens)
	database.exec(`
		CREATE TABLE IF NOT EXISTS sessions (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			user_id INTEGER NOT NULL,
			token TEXT UNIQUE NOT NULL,
			expires_at DATETIME NOT NULL,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
		);
	`);

	// Game sessions table
	database.exec(`
		CREATE TABLE IF NOT EXISTS game_sessions (
			id TEXT PRIMARY KEY,
			player1_id INTEGER,
			player2_id INTEGER,
			status TEXT DEFAULT 'waiting',
			score_player1 INTEGER DEFAULT 0,
			score_player2 INTEGER DEFAULT 0,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			started_at DATETIME,
			ended_at DATETIME,
			FOREIGN KEY (player1_id) REFERENCES users(id),
			FOREIGN KEY (player2_id) REFERENCES users(id)
		);
	`);

	// Chat messages table
	database.exec(`
		CREATE TABLE IF NOT EXISTS chat_messages (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			user_id INTEGER NOT NULL,
			room_id TEXT DEFAULT 'general',
			message TEXT NOT NULL,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
		);
	`);

	// Chat rooms table
	database.exec(`
		CREATE TABLE IF NOT EXISTS chat_rooms (
			id TEXT PRIMARY KEY,
			name TEXT NOT NULL,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP
		);
	`);

	// Insert default rooms
	const insertRoom = database.prepare(`
		INSERT OR IGNORE INTO chat_rooms (id, name) VALUES (?, ?)
	`);
	
	insertRoom.run('general', 'General');
	insertRoom.run('game', 'Game Chat');

	// Create indexes for performance
	database.exec(`
		CREATE INDEX IF NOT EXISTS idx_users_username ON users(username);
		CREATE INDEX IF NOT EXISTS idx_users_email ON users(email);
		CREATE INDEX IF NOT EXISTS idx_sessions_user_id ON sessions(user_id);
		CREATE INDEX IF NOT EXISTS idx_sessions_token ON sessions(token);
		CREATE INDEX IF NOT EXISTS idx_game_sessions_status ON game_sessions(status);
		CREATE INDEX IF NOT EXISTS idx_chat_messages_room_id ON chat_messages(room_id);
		CREATE INDEX IF NOT EXISTS idx_chat_messages_created_at ON chat_messages(created_at);
	`);

	console.log('✅ Database schema initialized');
}

export default {
	getDatabase,
	closeDatabase,
	initializeDatabase,
};
