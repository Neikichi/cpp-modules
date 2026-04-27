import Fastify from 'fastify';
import cors from '@fastify/cors';
import { initializeDatabase } from '../../db/database.js';
import userRepository from '../../db/users.js';

const PORT = Number(process.env.PORT) || 3002;
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
		Body: { username: string; password: string; email: string };
	}>('/register', async (req, reply) => {
		const { username, password, email } = req.body;

		if (!username || !password || !email) {
			return reply
				.status(400)
				.send({ error: 'Username, password, and email required' });
		}

		const usernameRegex = /^[a-zA-Z0-9]{4,20}$/;
		if (!usernameRegex.test(username)) {
			return reply.status(400).send({
				error: 'Username must be at least 4 to 20 characters long alphanumeric',
			});
		}

		const passwordRegex =
			/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{8,}$/;
		if (!passwordRegex.test(password)) {
			return reply.status(400).send({
				error: 'Password must be at least 8 characters long, include uppercase, lowercase, number, and special character.',
			});
		}

		const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
		if (!emailRegex.test(email)) {
			return reply.status(400).send({
				error: 'Invalid email format.',
			});
		}

		fastify.log.info(`Registration attempt for user: ${username}`);

		try {
			// Check if username already exists
			const existingUsername = userRepository.getUserByUsername(username);
			if (existingUsername) {
				return reply.status(400).send({ error: 'Username already taken' });
			}

			// Check if email already exists
			const existingEmail = userRepository.getUserByEmail(email);
			if (existingEmail) {
				return reply.status(400).send({ error: 'Email already registered' });
			}

			// Create new user
			const newUser = await userRepository.createUser({
				username,
				email,
				password,
			});

			return reply.send({
				message: 'Registration successful',
				user: {
					id: newUser.id,
					username: newUser.username,
					email: newUser.email,
				},
			});
		} catch (error) {
			fastify.log.error({ err: error }, 'Registration error');
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	fastify.get('/health', async () => {
		return { status: 'ok', service: 'register' };
	});

	try {
		await fastify.listen({ port: PORT, host: HOST });
		console.log(`📝 Register service running at http://${HOST}:${PORT}`);
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
}

start();
