import Fastify from 'fastify';
import cors from '@fastify/cors';
import { verifyToken, extractTokenFromHeader } from '../../db/jwt.js';

const PORT = Number(process.env.PORT) || 3000;
const HOST = process.env.HOST || '0.0.0.0';

// Service URLs - use Docker service names in production, localhost in dev
const SERVICES = {
	login: process.env.LOGIN_SERVICE_URL || 'http://localhost:3001',
	register: process.env.REGISTER_SERVICE_URL || 'http://localhost:3002',
	game: process.env.GAME_SERVICE_URL || 'http://localhost:3003',
	chat: process.env.CHAT_SERVICE_URL || 'http://localhost:3004',
};

async function start() {
	const fastify = Fastify({ logger: true });

	await fastify.register(cors, {
		origin: true,
		credentials: true,
	});

	// Helper function to verify JWT and get user headers
	const getAuthHeaders = (req: any): Record<string, string> => {
		const token = extractTokenFromHeader(req.headers.authorization);
		
		if (!token) {
			return {};
		}

		const user = verifyToken(token);
		
		if (!user) {
			return {};
		}

		// Forward user info to microservices via headers
		return {
			'X-User-Id': user.id.toString(),
			'X-User-Username': user.username,
			'X-User-Email': user.email,
		};
	};

	// Helper function to check authentication
	const requireAuth = (req: any, reply: any) => {
		const token = extractTokenFromHeader(req.headers.authorization);
		
		if (!token) {
			reply.status(401).send({
				error: 'Authentication required',
				message: 'No token provided',
			});
			return false;
		}

		const user = verifyToken(token);
		
		if (!user) {
			reply.status(401).send({
				error: 'Authentication failed',
				message: 'Invalid or expired token',
			});
			return false;
		}

		return true;
	};

	// Health check
	fastify.get('/api/health', async () => {
		return { status: 'ok', service: 'gateway' };
	});

	// Route to login service
	fastify.post('/api/login', async (req, reply) => {
		try {
			const response = await fetch(`${SERVICES.login}/login`, {
				method: 'POST',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify(req.body),
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Login service error');
			reply.status(503).send({ error: 'Login service unavailable' });
		}
	});

	// Route to refresh token
	fastify.post('/api/refresh', async (req, reply) => {
		try {
			const response = await fetch(`${SERVICES.login}/refresh`, {
				method: 'POST',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify(req.body),
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Token refresh error');
			reply.status(503).send({ error: 'Login service unavailable' });
		}
	});

	// Route to register service
	fastify.post('/api/register', async (req, reply) => {
		try {
			const response = await fetch(`${SERVICES.register}/register`, {
				method: 'POST',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify(req.body),
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Register service error');
			reply.status(503).send({ error: 'Register service unavailable' });
		}
	});

	// Route to game service
	fastify.get('/api/game/state', async (req, reply) => {
		// Verify JWT at gateway
		if (!requireAuth(req, reply)) return;

		try {
			const userHeaders = getAuthHeaders(req);
			
			const response = await fetch(`${SERVICES.game}/game/state`, {
				headers: userHeaders,
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Game service error');
			reply.status(503).send({ error: 'Game service unavailable' });
		}
	});

	fastify.post('/api/game/create', async (req, reply) => {
		// Verify JWT at gateway
		if (!requireAuth(req, reply)) return;

		try {
			const userHeaders = getAuthHeaders(req);
			
			const response = await fetch(`${SERVICES.game}/game/create`, {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					...userHeaders,
				},
				body: JSON.stringify(req.body),
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Game service error');
			reply.status(503).send({ error: 'Game service unavailable' });
		}
	});

	fastify.post('/api/game/join', async (req, reply) => {
		// Verify JWT at gateway
		if (!requireAuth(req, reply)) return;

		try {
			const userHeaders = getAuthHeaders(req);
			
			const response = await fetch(`${SERVICES.game}/game/join`, {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					...userHeaders,
				},
				body: JSON.stringify(req.body),
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Game service error');
			reply.status(503).send({ error: 'Game service unavailable' });
		}
	});

	// Route to chat service
	fastify.get('/api/chat/messages', async (req, reply) => {
		// Verify JWT at gateway
		if (!requireAuth(req, reply)) return;

		try {
			const userHeaders = getAuthHeaders(req);
			
			const response = await fetch(`${SERVICES.chat}/chat/messages`, {
				headers: userHeaders,
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Chat service error');
			reply.status(503).send({ error: 'Chat service unavailable' });
		}
	});

	fastify.post('/api/chat/send', async (req, reply) => {
		// Verify JWT at gateway
		if (!requireAuth(req, reply)) return;

		try {
			const userHeaders = getAuthHeaders(req);
			
			const response = await fetch(`${SERVICES.chat}/chat/send`, {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					...userHeaders,
				},
				body: JSON.stringify(req.body),
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Chat service error');
			reply.status(503).send({ error: 'Chat service unavailable' });
		}
	});

	fastify.get('/api/chat/rooms', async (req, reply) => {
		// Verify JWT at gateway
		if (!requireAuth(req, reply)) return;

		try {
			const userHeaders = getAuthHeaders(req);
			
			const response = await fetch(`${SERVICES.chat}/chat/rooms`, {
				headers: userHeaders,
			});
			const data = await response.json();
			reply.status(response.status).send(data);
		} catch (error) {
			fastify.log.error({ err: error }, 'Chat service error');
			reply.status(503).send({ error: 'Chat service unavailable' });
		}
	});

	// Legacy endpoint for compatibility
	fastify.get('/api/hello', async () => {
		return { message: 'Hello from API Gateway' };
	});

	try {
		await fastify.listen({ port: PORT, host: HOST });
		console.log(`🌐 API Gateway running at http://${HOST}:${PORT}`);
		console.log('Routing to services:', SERVICES);
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
}

start();
