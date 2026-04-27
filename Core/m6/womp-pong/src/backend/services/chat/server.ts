import Fastify from 'fastify';
import cors from '@fastify/cors';
import { initializeDatabase } from '../../db/database.js';
import chatRepository from '../../db/chat.js';

const PORT = Number(process.env.PORT) || 3004;
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

	// Get chat messages (authenticated by gateway)
	fastify.get<{
		Querystring: { roomId?: string; limit?: string };
	}>('/chat/messages', async (req, reply) => {
		try {
			const user = getUserFromHeaders(req.headers);
			const roomId = req.query.roomId || 'general';
			const limit = req.query.limit ? parseInt(req.query.limit) : 50;
			
			const messages = chatRepository.getMessages(roomId, limit);
			
			return { messages, user };
		} catch (error) {
			fastify.log.error({ err: error }, 'Error fetching messages');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	// Send a message (authenticated by gateway)
	fastify.post<{
		Body: { userId?: number; text: string; roomId?: string };
	}>('/chat/send', async (req, reply) => {
		const { text, roomId } = req.body;
		const user = getUserFromHeaders(req.headers);
		// Use user from gateway headers
		const userId = req.body.userId || user?.id;

		if (!userId || !text) {
			return reply.status(400).send({ error: 'text required' });
		}

		try {
			const message = chatRepository.sendMessage(
				userId,
				roomId || 'general',
				text
			);
			
			fastify.log.info(`Message from user ${userId} (${user?.username}): ${text}`);

			return {
				message: 'Message sent successfully',
				data: message,
			};
		} catch (error) {
			fastify.log.error({ err: error }, 'Error sending message');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	// Get chat rooms (authenticated by gateway)
	fastify.get('/chat/rooms', async (req, reply) => {
		try {
			const user = getUserFromHeaders(req.headers);
			const rooms = chatRepository.getRooms();
			return { rooms, user };
		} catch (error) {
			fastify.log.error({ err: error }, 'Error fetching rooms');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	fastify.get('/health', async () => {
		return { status: 'ok', service: 'chat' };
	});

	try {
		await fastify.listen({ port: PORT, host: HOST });
		console.log(`💬 Chat service running at http://${HOST}:${PORT}`);
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
}

start();
