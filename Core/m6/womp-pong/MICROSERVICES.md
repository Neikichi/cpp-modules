# Womp Pong - Microservices Architecture

This project has been refactored into a microservices architecture with separate services for different functionalities.

## Architecture Overview

### Microservices
- **API Gateway** (Port 3000): Routes requests to appropriate microservices
- **Login Service** (Port 3001): Handles user authentication
- **Register Service** (Port 3002): Handles user registration
- **Game Service** (Port 3003): Manages game sessions and logic
- **Chat Service** (Port 3004): Handles chat messages and rooms

### Frontend
- **Vite Dev Server** (Port 5173): Development with Hot Module Replacement (HMR)
- **Production**: Built static files served by Nginx

### Infrastructure
- **Nginx** (Ports 80/443): Production reverse proxy and static file server
- **Docker Compose**: Service orchestration

## Development Modes

### 1. Local Development with Vite HMR (Recommended for frontend work)

Start all microservices locally + Vite dev server:

```bash
# Terminal 1: Build and watch TypeScript services
npm run dev:services:watch

# Terminal 2: Start all microservices
npm run dev:services:start

# Terminal 3: Start Vite dev server
npm run dev:vite
```

Or use the combined command:
```bash
npm run dev:local
```

**Access:**
- Frontend: http://localhost:5173 (with HMR)
- API Gateway: http://localhost:3000
- Login Service: http://localhost:3001
- Register Service: http://localhost:3002
- Game Service: http://localhost:3003
- Chat Service: http://localhost:3004

### 2. Docker Development Mode

Run all services in Docker with volume mounting:

```bash
npm run docker:dev
```

**Access:**
- All services available at their respective ports
- Use Vite dev server separately if you need HMR

### 3. Production Mode

Build and deploy with Docker Compose + Nginx:

```bash
# Build everything
npm run prod:build

# Start production services
npm run prod:start
```

Or in the src directory:
```bash
cd src
docker-compose up --build
```

**Access:**
- Application: https://localhost (via Nginx)
- All API requests proxied through /api

## Project Structure

```
src/
├── backend/
│   ├── services/
│   │   ├── gateway/          # API Gateway (3000)
│   │   ├── login/            # Login Service (3001)
│   │   ├── register/         # Register Service (3002)
│   │   ├── game/             # Game Service (3003)
│   │   └── chat/             # Chat Service (3004)
│   └── db/                   # Database utilities (if needed)
├── frontend/
│   ├── App.tsx
│   ├── main.tsx
│   └── ...
├── nginx/
│   ├── Dockerfile
│   └── conf/
│       └── inception.conf    # Nginx config with /api proxy
└── docker-compose.yml        # Production compose
```

## API Endpoints

All API requests go through the gateway at `/api/*`:

### Authentication
- `POST /api/login` → Login Service
- `POST /api/register` → Register Service

### Game
- `GET /api/game/state` → Game Service
- `POST /api/game/create` → Game Service
- `POST /api/game/join` → Game Service

### Chat
- `GET /api/chat/messages` → Chat Service
- `POST /api/chat/send` → Chat Service
- `GET /api/chat/rooms` → Chat Service

### Health Checks
- `GET /api/health` → Gateway health

## Environment Variables

Each service supports:
- `PORT`: Service port (default varies by service)
- `HOST`: Bind host (default: 0.0.0.0)

Gateway additionally uses:
- `LOGIN_SERVICE_URL`: URL to login service
- `REGISTER_SERVICE_URL`: URL to register service
- `GAME_SERVICE_URL`: URL to game service
- `CHAT_SERVICE_URL`: URL to chat service

## Development Workflow

1. **Frontend Development**: Use `npm run dev:vite` for fast HMR
2. **Backend Development**: Use `npm run dev:services:watch` + individual service scripts
3. **Full Stack Testing**: Use `npm run docker:dev` to test the complete system
4. **Production Deploy**: Use `npm run prod:start` for production deployment

## Commands Reference

| Command | Description |
|---------|-------------|
| `npm run dev:vite` | Start Vite dev server with HMR |
| `npm run dev:services:watch` | Watch and compile TypeScript services |
| `npm run dev:services:start` | Start all microservices locally |
| `npm run dev:local` | Full local dev mode (Vite + Services) |
| `npm run docker:dev` | Docker development mode |
| `npm run docker:dev:down` | Stop Docker dev containers |
| `npm run prod:build` | Build for production |
| `npm run prod:start` | Start production Docker containers |
| `npm run docker:prod:down` | Stop production containers |

## Notes

- In development, Vite proxies `/api` requests to `http://localhost:3000` (Gateway)
- In production, Nginx proxies `/api` requests to the Gateway container
- Each microservice is independent and can be scaled separately
- The gateway handles service discovery and routing
- All services use Fastify for consistent API structure
