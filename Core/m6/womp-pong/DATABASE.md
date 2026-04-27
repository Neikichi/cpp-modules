# 📦 SQLite Database Integration

The project now uses **SQLite** as an embedded database for all microservices.

## Database Location

- **Development**: `data/womp-pong.db` (in project root)
- **Docker**: Mounted volume for persistence

## Database Schema

### Users Table
Stores user accounts with password hashing (bcrypt).

```sql
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    email TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    last_login DATETIME
);
```

### Sessions Table
Stores user sessions/tokens.

```sql
CREATE TABLE sessions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    token TEXT UNIQUE NOT NULL,
    expires_at DATETIME NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);
```

### Game Sessions Table
Tracks active and completed games.

```sql
CREATE TABLE game_sessions (
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
```

### Chat Messages Table
Stores all chat messages.

```sql
CREATE TABLE chat_messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    room_id TEXT DEFAULT 'general',
    message TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);
```

### Chat Rooms Table
Available chat rooms.

```sql
CREATE TABLE chat_rooms (
    id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);
```

## Database Utilities

### Location
All database code is in `src/backend/db/`:

- **database.ts** - Database connection and schema initialization
- **users.ts** - User repository (CRUD operations)
- **games.ts** - Game repository
- **chat.ts** - Chat repository
- **seed.ts** - Database seeding script

### Usage in Services

All microservices automatically initialize the database:

```typescript
import { initializeDatabase } from '../../db/database.js';
import userRepository from '../../db/users.js';

// In service startup
initializeDatabase();

// Use repository
const user = userRepository.getUserByUsername('admin');
```

## Commands

### Seed Database
Create initial users (admin and testuser):

```bash
npm run db:seed
```

**Default users:**
- Username: `admin`, Password: `adminWomp@42`
- Username: `testuser`, Password: `Test1234!`

### Reset Database
Delete and recreate database with seed data:

```bash
npm run db:reset
```

## Password Security

- Passwords are hashed using **bcrypt** with 10 salt rounds
- Password requirements:
  - Minimum 8 characters
  - At least one uppercase letter
  - At least one lowercase letter
  - At least one digit
  - At least one special character

## Repositories API

### UserRepository

```typescript
// Create user
const user = await userRepository.createUser({
    username: 'john',
    email: 'john@example.com',
    password: 'Password123!'
});

// Get user
const user = userRepository.getUserByUsername('john');
const user = userRepository.getUserByEmail('john@example.com');
const user = userRepository.getUserById(1);

// Verify password
const isValid = await userRepository.verifyPassword(user, 'Password123!');

// Update last login
userRepository.updateLastLogin(userId);

// Get all users
const users = userRepository.getAllUsers();
```

### GameRepository

```typescript
// Create game
const game = gameRepository.createGame('game-123', playerId);

// Get game
const game = gameRepository.getGameById('game-123');

// Join game
const game = gameRepository.joinGame('game-123', player2Id);

// Update score
gameRepository.updateScore('game-123', 5, 3);

// End game
gameRepository.endGame('game-123');

// Get active games
const games = gameRepository.getActiveGames();
```

### ChatRepository

```typescript
// Send message
const message = chatRepository.sendMessage(userId, 'general', 'Hello!');

// Get messages
const messages = chatRepository.getMessages('general', 50);

// Get rooms
const rooms = chatRepository.getRooms();

// Create room
const room = chatRepository.createRoom('custom', 'Custom Room');
```

## Development Workflow

1. **First time setup:**
   ```bash
   npm install
   npm run build:services
   npm run db:seed
   ```

2. **Start development:**
   ```bash
   npm run dev:services:start
   npm run dev:vite
   ```

3. **Test login:**
   - Navigate to http://localhost:5173
   - Login with username: `admin`, password: `adminWomp@42`

## Database in Docker

The database file is stored in a Docker volume for persistence:

```yaml
volumes:
  db_data:
    driver: local
```

This ensures data persists between container restarts.

## Migration Strategy

Currently using a simple initialization approach. For future migrations:

1. Create migration files in `src/backend/db/migrations/`
2. Track migration version in database
3. Run migrations on startup

## Performance

SQLite is optimized with:
- **Indexes** on frequently queried columns
- **Foreign keys** enabled for data integrity
- **WAL mode** for better concurrency (can be enabled)
- **Prepared statements** for all queries

## Backup

To backup the database:

```bash
# Development
cp data/womp-pong.db data/womp-pong-backup.db

# Docker
docker cp container_name:/app/data/womp-pong.db ./backup.db
```

## Troubleshooting

**Database locked error:**
- Ensure only one instance of services is running
- Check for zombie processes

**Schema not created:**
- Run `npm run db:seed` to initialize

**Password doesn't work:**
- Ensure you're using the correct test credentials
- Password must meet all requirements
