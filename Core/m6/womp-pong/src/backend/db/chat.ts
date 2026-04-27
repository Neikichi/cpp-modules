import { getDatabase } from './database.js';

export interface ChatMessage {
	id: number;
	user_id: number;
	room_id: string;
	message: string;
	created_at: string;
}

export interface ChatRoom {
	id: string;
	name: string;
	created_at: string;
}

export class ChatRepository {
	private db = getDatabase();

	sendMessage(userId: number, roomId: string, message: string): ChatMessage {
		const stmt = this.db.prepare(`
			INSERT INTO chat_messages (user_id, room_id, message)
			VALUES (?, ?, ?)
		`);

		const result = stmt.run(userId, roomId, message);
		
		return this.getMessageById(Number(result.lastInsertRowid))!;
	}

	getMessageById(id: number): ChatMessage | undefined {
		const stmt = this.db.prepare(`
			SELECT * FROM chat_messages WHERE id = ?
		`);
		
		return stmt.get(id) as ChatMessage | undefined;
	}

	getMessages(roomId: string, limit: number = 50): ChatMessage[] {
		const stmt = this.db.prepare(`
			SELECT cm.*, u.username
			FROM chat_messages cm
			JOIN users u ON cm.user_id = u.id
			WHERE cm.room_id = ?
			ORDER BY cm.created_at DESC
			LIMIT ?
		`);
		
		const messages = stmt.all(roomId, limit) as any[];
		return messages.reverse(); // Return in chronological order
	}

	getRooms(): ChatRoom[] {
		const stmt = this.db.prepare(`
			SELECT cr.*, 
				   (SELECT COUNT(*) FROM chat_messages WHERE room_id = cr.id) as message_count
			FROM chat_rooms cr
			ORDER BY cr.name
		`);
		
		return stmt.all() as ChatRoom[];
	}

	createRoom(roomId: string, name: string): ChatRoom {
		const stmt = this.db.prepare(`
			INSERT INTO chat_rooms (id, name)
			VALUES (?, ?)
		`);

		stmt.run(roomId, name);
		
		return { id: roomId, name, created_at: new Date().toISOString() };
	}
}

export default new ChatRepository();
