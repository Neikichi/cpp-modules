import { getDatabase } from './database.js';
import bcrypt from 'bcrypt';

const SALT_ROUNDS = 10;

export interface User {
	id: number;
	username: string;
	email: string;
	password_hash: string;
	created_at: string;
	updated_at: string;
	last_login: string | null;
}

export interface CreateUserData {
	username: string;
	email: string;
	password: string;
}

export class UserRepository {
	private db = getDatabase();

	async createUser(data: CreateUserData): Promise<User> {
		const passwordHash = await bcrypt.hash(data.password, SALT_ROUNDS);
		
		const stmt = this.db.prepare(`
			INSERT INTO users (username, email, password_hash)
			VALUES (?, ?, ?)
		`);

		const result = stmt.run(data.username, data.email, passwordHash);
		
		return this.getUserById(Number(result.lastInsertRowid))!;
	}

	getUserById(id: number): User | undefined {
		const stmt = this.db.prepare(`
			SELECT * FROM users WHERE id = ?
		`);
		
		return stmt.get(id) as User | undefined;
	}

	getUserByUsername(username: string): User | undefined {
		const stmt = this.db.prepare(`
			SELECT * FROM users WHERE username = ?
		`);
		
		return stmt.get(username) as User | undefined;
	}

	getUserByEmail(email: string): User | undefined {
		const stmt = this.db.prepare(`
			SELECT * FROM users WHERE email = ?
		`);
		
		return stmt.get(email) as User | undefined;
	}

	async verifyPassword(user: User, password: string): Promise<boolean> {
		return bcrypt.compare(password, user.password_hash);
	}

	updateLastLogin(userId: number): void {
		const stmt = this.db.prepare(`
			UPDATE users SET last_login = CURRENT_TIMESTAMP WHERE id = ?
		`);
		
		stmt.run(userId);
	}

	getAllUsers(): User[] {
		const stmt = this.db.prepare(`
			SELECT id, username, email, created_at, last_login FROM users
		`);
		
		return stmt.all() as User[];
	}
}

export default new UserRepository();
