import jwt, { SignOptions } from 'jsonwebtoken';

// JWT Configuration
const JWT_SECRET: string = process.env.JWT_SECRET || 'womp-pong-secret-change-in-production';
const JWT_EXPIRES_IN: string | number = process.env.JWT_EXPIRES_IN || '24h';
const JWT_REFRESH_EXPIRES_IN: string | number = process.env.JWT_REFRESH_EXPIRES_IN || '7d';

export interface JWTPayload {
	id: number;
	username: string;
	email: string;
	iat?: number;
	exp?: number;
}

/**
 * Generate an access token for a user
 */
export function generateToken(user: { id: number; username: string; email: string }): string {
	const payload: JWTPayload = {
		id: user.id,
		username: user.username,
		email: user.email,
	};

	const options: SignOptions = {
		expiresIn: JWT_EXPIRES_IN as any,
	};

	return jwt.sign(payload, JWT_SECRET, options);
}

/**
 * Generate a refresh token for a user
 */
export function generateRefreshToken(user: { id: number; username: string; email: string }): string {
	const payload: JWTPayload = {
		id: user.id,
		username: user.username,
		email: user.email,
	};

	const options: SignOptions = {
		expiresIn: JWT_REFRESH_EXPIRES_IN as any,
	};

	return jwt.sign(payload, JWT_SECRET, options);
}

/**
 * Verify and decode a JWT token
 */
export function verifyToken(token: string): JWTPayload | null {
	try {
		const decoded = jwt.verify(token, JWT_SECRET) as JWTPayload;
		return decoded;
	} catch (error) {
		console.error('JWT verification failed:', error);
		return null;
	}
}

/**
 * Refresh an access token using a refresh token
 */
export function refreshAccessToken(refreshToken: string): string | null {
	const decoded = verifyToken(refreshToken);
	if (!decoded) {
		return null;
	}

	// Generate a new access token
	return generateToken({
		id: decoded.id,
		username: decoded.username,
		email: decoded.email,
	});
}

/**
 * Extract token from Authorization header
 */
export function extractTokenFromHeader(authHeader: string | undefined): string | null {
	if (!authHeader) {
		return null;
	}

	// Authorization: Bearer <token>
	const parts = authHeader.split(' ');
	if (parts.length !== 2 || parts[0] !== 'Bearer') {
		return null;
	}

	return parts[1];
}
