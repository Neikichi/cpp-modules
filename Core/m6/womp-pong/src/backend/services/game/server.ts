import Fastify from 'fastify';
import cors from '@fastify/cors';
import { initializeDatabase } from '../../db/database.js';
import gameRepository from '../../db/games.js';

const PORT = Number(process.env.PORT) || 3003;
const HOST = process.env.HOST || '0.0.0.0';

// Helper to extract user from gateway headers
const getUserFromHeaders = (headers: any) => {
	const userId = headers['x-user-id'];
	const username = headers['x-user-username'];
	const email = headers['x-user-email'];

	if (!userId) {
		return null;
	}

	return {
		id: parseInt(userId),
		username: username || '',
		email: email || '',
	};
};

async function start() {
	const fastify = Fastify({ logger: true });

	// Initialize database
	initializeDatabase();

	await fastify.register(cors, {
		origin: true,
		credentials: true,
	});

	// Game state endpoint (authenticated by gateway)
	fastify.get('/game/state', async (req, reply) => {
		try {
			const user = getUserFromHeaders(req.headers);
			const activeGames = gameRepository.getActiveGames();
			return {
				status: 'ok',
				activeGames,
				user,
			};
		} catch (error) {
			fastify.log.error({ err: error }, 'Error fetching game state');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	// Create new game session (authenticated by gateway)
	fastify.post<{
		Body: { playerId?: number };
	}>('/game/create', async (req, reply) => {
		try {
			const user = getUserFromHeaders(req.headers);
			// Use user from gateway headers
			const playerId = req.body.playerId || user?.id;
			const gameId = `game-${Date.now()}`;
			
			const game = gameRepository.createGame(gameId, playerId);
			fastify.log.info(`New game created: ${gameId} by user ${user?.username}`);
			
			return {
				gameId: game.id,
				message: 'Game session created',
				game,
			};
		} catch (error) {
			fastify.log.error({ err: error }, 'Error creating game');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	// Join game session (authenticated by gateway)
	fastify.post<{
		Body: { gameId: string; playerId?: number };
	}>('/game/join', async (req, reply) => {
		const { gameId } = req.body;
		const user = getUserFromHeaders(req.headers);
		// Use user from gateway headers
		const playerId = req.body.playerId || user?.id;
		
		if (!gameId || !playerId) {
			return reply.status(400).send({ error: 'gameId and playerId required' });
		}

		try {
			const game = gameRepository.joinGame(gameId, playerId);
			
			if (!game) {
				return reply.status(404).send({ error: 'Game not found or already full' });
			}

			fastify.log.info(`Player ${playerId} (${user?.username}) joined game ${gameId}`);
			
			return {
				message: 'Joined game successfully',
				game,
			};
		} catch (error) {
			fastify.log.error({ err: error }, 'Error joining game');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	fastify.get('/health', async () => {
		return { status: 'ok', service: 'game' };
	});

	try {
		await fastify.listen({ port: PORT, host: HOST });
		console.log(`🎮 Game service running at http://${HOST}:${PORT}`);
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
}

start();
