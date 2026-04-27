# JWT Authentication

## Overview

The womp-pong microservices architecture now uses JWT (JSON Web Tokens) for authentication and authorization. This provides a stateless, secure way to authenticate users across all services.

## Architecture

### Components

1. **JWT Utility Module** (`src/backend/db/jwt.ts`)
   - Token generation and verification
   - Token refresh functionality
   - Header parsing utilities

2. **Authentication Middleware** (`src/backend/middleware/auth.ts`)
   - `authenticateJWT`: Requires valid JWT token
   - `optionalAuth`: Accepts optional JWT token

3. **Login Service** (`:3001`)
   - `/login`: Authenticates users and issues tokens
   - `/refresh`: Refreshes access tokens using refresh tokens

4. **Protected Services**
   - Game Service (`:3003`): All endpoints require authentication
   - Chat Service (`:3004`): All endpoints require authentication

## Token Types

### Access Token
- **Purpose**: Short-lived token for API requests
- **Expiration**: 24 hours (configurable via `JWT_EXPIRES_IN`)
- **Usage**: Include in `Authorization` header for all protected endpoints

### Refresh Token
- **Purpose**: Long-lived token for obtaining new access tokens
- **Expiration**: 7 days (configurable via `JWT_REFRESH_EXPIRES_IN`)
- **Usage**: Send to `/refresh` endpoint when access token expires

## Configuration

Set these environment variables (optional):

```bash
JWT_SECRET=your-secret-key-here          # Default: 'womp-pong-secret-change-in-production'
JWT_EXPIRES_IN=24h                        # Default: 24 hours
JWT_REFRESH_EXPIRES_IN=7d                 # Default: 7 days
```

⚠️ **IMPORTANT**: Change `JWT_SECRET` in production!

## Usage

### 1. Login

**Request:**
```bash
POST http://localhost:3001/login
Content-Type: application/json

{
  "username": "admin",
  "password": "adminWomp@42"
}
```

**Response:**
```json
{
  "message": "Login successful",
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
  "refreshToken": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
  "user": {
    "id": 1,
    "username": "admin",
    "email": "admin@wompbpong.local"
  }
}
```

### 2. Access Protected Endpoints

Include the access token in the `Authorization` header:

**Request:**
```bash
GET http://localhost:3003/game/state
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
```

**Response:**
```json
{
  "status": "ok",
  "activeGames": [...],
  "user": {
    "id": 1,
    "username": "admin",
    "email": "admin@wompbpong.local"
  }
}
```

### 3. Refresh Token

When the access token expires (401 error), use the refresh token:

**Request:**
```bash
POST http://localhost:3001/refresh
Content-Type: application/json

{
  "refreshToken": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

**Response:**
```json
{
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

## Protected Endpoints

### Game Service (`:3003`)

All endpoints require authentication:

- `GET /game/state` - Get active game sessions
- `POST /game/create` - Create new game (uses `req.user.id` automatically)
- `POST /game/join` - Join existing game (uses `req.user.id` automatically)

### Chat Service (`:3004`)

All endpoints require authentication:

- `GET /chat/messages?roomId=general&limit=50` - Get chat messages
- `POST /chat/send` - Send message (uses `req.user.id` automatically)
- `GET /chat/rooms` - Get chat rooms

## Frontend Integration

### Store Tokens

```typescript
// After login
const response = await fetch('http://localhost:3000/api/login', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({ username, password }),
});

const { token, refreshToken, user } = await response.json();

// Store in localStorage or secure cookie
localStorage.setItem('accessToken', token);
localStorage.setItem('refreshToken', refreshToken);
localStorage.setItem('user', JSON.stringify(user));
```

### Use Tokens

```typescript
// Add to all API requests
const token = localStorage.getItem('accessToken');

const response = await fetch('http://localhost:3000/api/game/state', {
  headers: {
    'Authorization': `Bearer ${token}`,
  },
});

if (response.status === 401) {
  // Token expired, refresh it
  await refreshAccessToken();
}
```

### Refresh Flow

```typescript
async function refreshAccessToken() {
  const refreshToken = localStorage.getItem('refreshToken');
  
  const response = await fetch('http://localhost:3000/api/refresh', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ refreshToken }),
  });

  if (response.ok) {
    const { token } = await response.json();
    localStorage.setItem('accessToken', token);
    return token;
  } else {
    // Refresh token invalid, redirect to login
    localStorage.clear();
    window.location.href = '/login';
  }
}
```

## Security Best Practices

1. **Always use HTTPS in production** - Tokens should never be transmitted over HTTP
2. **Change JWT_SECRET** - Use a strong, random secret in production
3. **Store tokens securely** - Use httpOnly cookies instead of localStorage for better security
4. **Implement token rotation** - Regularly refresh tokens
5. **Validate on every request** - Middleware checks token validity
6. **Handle expired tokens** - Gracefully refresh or redirect to login

## Error Handling

### 401 Unauthorized

**Missing Token:**
```json
{
  "error": "Authentication required",
  "message": "No token provided"
}
```

**Invalid/Expired Token:**
```json
{
  "error": "Authentication failed",
  "message": "Invalid or expired token"
}
```

### 400 Bad Request

**Missing Refresh Token:**
```json
{
  "error": "Refresh token required"
}
```

## Testing

### Test Login
```bash
curl -X POST http://localhost:3001/login \
  -H "Content-Type: application/json" \
  -d '{"username":"admin","password":"adminWomp@42"}'
```

### Test Protected Endpoint
```bash
TOKEN="your-token-here"
curl http://localhost:3003/game/state \
  -H "Authorization: Bearer $TOKEN"
```

### Test Refresh
```bash
REFRESH_TOKEN="your-refresh-token-here"
curl -X POST http://localhost:3001/refresh \
  -H "Content-Type: application/json" \
  -d "{\"refreshToken\":\"$REFRESH_TOKEN\"}"
```

## JWT Payload Structure

```json
{
  "id": 1,
  "username": "admin",
  "email": "admin@wompbpong.local",
  "iat": 1234567890,
  "exp": 1234654290
}
```

- `id`: User database ID
- `username`: User's username
- `email`: User's email
- `iat`: Issued at timestamp
- `exp`: Expiration timestamp

## Migration Notes

The following changes were made to implement JWT:

1. ✅ Added `jsonwebtoken` and `@types/jsonwebtoken` dependencies
2. ✅ Created JWT utility module with token generation/verification
3. ✅ Created authentication middleware for Fastify
4. ✅ Updated login service to generate real JWT tokens (removed mock tokens)
5. ✅ Added `/refresh` endpoint for token refresh
6. ✅ Protected all game service endpoints with JWT middleware
7. ✅ Protected all chat service endpoints with JWT middleware
8. ✅ User IDs now automatically extracted from JWT tokens (no need to pass `userId` in requests)

## Next Steps

1. Install dependencies: `npm install`
2. Rebuild native modules: `npm rebuild better-sqlite3` (from WSL terminal)
3. Start services: `npm run dev:services:start`
4. Test authentication flow with seeded users:
   - `admin` / `adminWomp@42`
   - `testuser` / `Test1234!`
