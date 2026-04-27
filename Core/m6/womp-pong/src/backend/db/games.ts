import { getDatabase } from './database.js';

export interface GameSession {
	id: string;
	player1_id: number | null;
	player2_id: number | null;
	status: 'waiting' | 'active' | 'completed';
	score_player1: number;
	score_player2: number;
	created_at: string;
	started_at: string | null;
	ended_at: string | null;
}

export class GameRepository {
	private db = getDatabase();

	createGame(gameId: string, player1Id?: number): GameSession {
		const stmt = this.db.prepare(`
			INSERT INTO game_sessions (id, player1_id, status)
			VALUES (?, ?, 'waiting')
		`);

		stmt.run(gameId, player1Id || null);
		
		return this.getGameById(gameId)!;
	}

	getGameById(gameId: string): GameSession | undefined {
		const stmt = this.db.prepare(`
			SELECT * FROM game_sessions WHERE id = ?
		`);
		
		return stmt.get(gameId) as GameSession | undefined;
	}

	joinGame(gameId: string, player2Id: number): GameSession | undefined {
		const stmt = this.db.prepare(`
			UPDATE game_sessions 
			SET player2_id = ?, status = 'active', started_at = CURRENT_TIMESTAMP
			WHERE id = ? AND player2_id IS NULL
		`);

		const result = stmt.run(player2Id, gameId);
		
		if (result.changes === 0) {
			return undefined;
		}
		
		return this.getGameById(gameId);
	}

	updateScore(gameId: string, player1Score: number, player2Score: number): void {
		const stmt = this.db.prepare(`
			UPDATE game_sessions 
			SET score_player1 = ?, score_player2 = ?
			WHERE id = ?
		`);

		stmt.run(player1Score, player2Score, gameId);
	}

	endGame(gameId: string): void {
		const stmt = this.db.prepare(`
			UPDATE game_sessions 
			SET status = 'completed', ended_at = CURRENT_TIMESTAMP
			WHERE id = ?
		`);

		stmt.run(gameId);
	}

	getActiveGames(): GameSession[] {
		const stmt = this.db.prepare(`
			SELECT * FROM game_sessions 
			WHERE status IN ('waiting', 'active')
			ORDER BY created_at DESC
		`);
		
		return stmt.all() as GameSession[];
	}
}

export default new GameRepository();
