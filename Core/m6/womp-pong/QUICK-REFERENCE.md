# 🚀 Quick Reference Card

## Development Modes

### 🔥 Mode 1: Local Dev (Recommended)
**Best for**: Frontend & Backend development with hot reload

```bash
# Terminal 1
npm run dev:services:watch

# Terminal 2  
npm run dev:services:start

# Terminal 3
npm run dev:vite
```

**Access**: http://localhost:5173
**Hot Reload**: ✅ Yes (Vite HMR)

---

### 🐳 Mode 2: Docker Dev
**Best for**: Testing full stack integration

```bash
npm run docker:dev
```

**Access**: http://localhost:3000 (via Gateway)
**Hot Reload**: ❌ No (rebuild needed)

---

### 🚢 Mode 3: Production
**Best for**: Production deployment

```bash
npm run prod:build
npm run prod:start
```

**Access**: https://localhost (via Nginx)
**Hot Reload**: ❌ No

---

## Service Ports

| Service         | Port | Health Check                  |
|----------------|------|-------------------------------|
| Vite (Dev)     | 5173 | http://localhost:5173         |
| API Gateway    | 3000 | http://localhost:3000/api/health |
| Login          | 3001 | http://localhost:3001/health  |
| Register       | 3002 | http://localhost:3002/health  |
| Game           | 3003 | http://localhost:3003/health  |
| Chat           | 3004 | http://localhost:3004/health  |
| Nginx (Prod)   | 443  | https://localhost             |

---

## Common Commands

```bash
# Development
npm run dev:vite              # Start Vite only
npm run dev:services:start    # Start all services
npm run dev:services:watch    # Watch TypeScript

# Database
npm run db:seed              # Create initial users
npm run db:reset             # Reset database

# Docker
npm run docker:dev            # Docker dev mode
npm run docker:dev:down       # Stop dev containers
npm run docker:prod           # Docker production
npm run docker:prod:down      # Stop prod containers

# Build
npm run build:services        # Compile TypeScript
npm run build:vite           # Build frontend
npm run prod:build           # Build everything

# Utilities
./check-health.sh            # Check service status
make help                    # Show Makefile commands
```

---

## API Endpoints

All via `/api` prefix:

```http
POST /api/login              # Authenticate user
POST /api/register           # Create new user
GET  /api/game/state         # Get game state
POST /api/game/create        # Create game session
POST /api/game/join          # Join game
GET  /api/chat/messages      # Get messages
POST /api/chat/send          # Send message
GET  /api/chat/rooms         # List rooms
GET  /api/health             # Gateway health
```

---

## File Locations

```
Microservices:  src/backend/services/{gateway,login,register,game,chat}/
Frontend:       src/frontend/
Nginx Config:   src/nginx/conf/inception.conf
Docker Compose: src/docker-compose.yml (prod)
                docker-compose.dev.yml (dev)
Vite Config:    vite.config.ts
```

---

## Troubleshooting

**Check if services are running:**
```bash
./check-health.sh
```

**View Docker logs:**
```bash
docker-compose -f docker-compose.dev.yml logs -f
```

**Rebuild everything:**
```bash
npm run prod:build
```

**Clean start:**
```bash
make clean
npm install
npm run build:services
```

---

## Request Flow

### Dev Mode
```
Browser → Vite (5173) → Gateway (3000) → Services (3001-3004)
```

### Prod Mode  
```
Browser → Nginx (443) → Gateway → Services
```

---

## 💡 Pro Tips

1. Use **Vite dev** for fastest frontend development
2. Use **Docker dev** to test service integration
3. Each service has `/health` endpoint for monitoring
4. Services communicate via gateway (no direct calls)
5. Frontend makes all API calls to `/api/*`

---

**Happy Coding! 🎮**
