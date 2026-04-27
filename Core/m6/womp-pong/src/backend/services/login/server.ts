import Fastify from 'fastify';
import cors from '@fastify/cors';
import { initializeDatabase } from '../../db/database.js';
import userRepository from '../../db/users.js';
import { generateToken, generateRefreshToken, verifyToken, extractTokenFromHeader } from '../../db/jwt.js';

const PORT = Number(process.env.PORT) || 3001;
const HOST = process.env.HOST || '0.0.0.0';

async function start() {
	const fastify = Fastify({ logger: true });

	// Initialize database
	initializeDatabase();

	await fastify.register(cors, {
		origin: true,
		credentials: true,
	});

	fastify.post<{
		Body: { username: string; password: string };
	}>('/login', async (req, reply) => {
		const { username, password } = req.body;

		if (!username || !password) {
			return reply
				.status(400)
				.send({ error: 'Username and password required' });
		}

		// ✅ Username: 4–20 chars, alphanumeric only
		const usernameRegex = /^[a-zA-Z0-9]{4,20}$/;
		if (!usernameRegex.test(username)) {
			return reply.status(400).send({
				error: 'Username must be at least 4 to 20 characters long alphanumeric',
			});
		}

		// ✅ Password: at least 8 chars, 1 upper, 1 lower, 1 digit, 1 special
		const passwordRegex =
			/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{8,}$/;
		if (!passwordRegex.test(password)) {
			return reply.status(400).send({
				error: 'Password must be at least 8 characters long, include uppercase, lowercase, number, and special character.',
			});
		}

		fastify.log.info(`Login attempt for user: ${username}`);

		try {
			// Get user from database
			const user = userRepository.getUserByUsername(username);
			
			if (!user) {
				return reply.status(401).send({ error: 'Invalid credentials' });
			}

			// Verify password
			const isValid = await userRepository.verifyPassword(user, password);
			
			if (!isValid) {
				return reply.status(401).send({ error: 'Invalid credentials' });
			}

			// Update last login
			userRepository.updateLastLogin(user.id);

			// Generate JWT tokens
			const token = generateToken({
				id: user.id,
				username: user.username,
				email: user.email,
			});
			const refreshToken = generateRefreshToken({
				id: user.id,
				username: user.username,
				email: user.email,
			});

			return reply.send({
				message: 'Login successful',
				token,
				refreshToken,
				user: {
					id: user.id,
					username: user.username,
					email: user.email,
				},
			});
		} catch (error) {
			fastify.log.error({ err: error }, 'Login error');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	fastify.post<{
		Body: { refreshToken: string };
	}>('/refresh', async (req, reply) => {
		const { refreshToken } = req.body;

		if (!refreshToken) {
			return reply.status(400).send({ error: 'Refresh token required' });
		}

		try {
			const decoded = verifyToken(refreshToken);

			if (!decoded) {
				return reply.status(401).send({ error: 'Invalid refresh token' });
			}

			// Generate new access token
			const newToken = generateToken({
				id: decoded.id,
				username: decoded.username,
				email: decoded.email,
			});

			return reply.send({
				token: newToken,
			});
		} catch (error) {
			fastify.log.error({ err: error }, 'Token refresh error');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	fastify.get('/health', async () => {
		return { status: 'ok', service: 'login' };
	});

	try {
		await fastify.listen({ port: PORT, host: HOST });
		console.log(`🔐 Login service running at http://${HOST}:${PORT}`);
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
}

start();
