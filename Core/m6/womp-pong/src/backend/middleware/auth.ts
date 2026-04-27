import { FastifyRequest, FastifyReply } from 'fastify';
import { verifyToken, extractTokenFromHeader, JWTPayload } from '../db/jwt.js';

// Extend FastifyRequest to include user property
declare module 'fastify' {
	interface FastifyRequest {
		user?: JWTPayload;
	}
}

/**
 * Authentication middleware for Fastify routes
 * Verifies JWT token and attaches user to request
 */
export async function authenticateJWT(
	request: FastifyRequest,
	reply: FastifyReply
): Promise<void> {
	const token = extractTokenFromHeader(request.headers.authorization);

	if (!token) {
		return reply.status(401).send({
			error: 'Authentication required',
			message: 'No token provided',
		});
	}

	const decoded = verifyToken(token);

	if (!decoded) {
		return reply.status(401).send({
			error: 'Authentication failed',
			message: 'Invalid or expired token',
		});
	}

	// Attach user to request
	request.user = decoded;
}

/**
 * Optional authentication middleware
 * Attaches user if valid token is provided, but doesn't require it
 */
export async function optionalAuth(
	request: FastifyRequest,
	reply: FastifyReply
): Promise<void> {
	const token = extractTokenFromHeader(request.headers.authorization);

	if (token) {
		const decoded = verifyToken(token);
		if (decoded) {
			request.user = decoded;
		}
	}
}
