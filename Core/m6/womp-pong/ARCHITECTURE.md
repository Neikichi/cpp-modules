# Architecture Diagram

## Development Mode (Vite HMR)
```
┌─────────────────────────────────────────────────────────────────┐
│                         Developer                               │
│                         Browser                                 │
└───────┬─────────────────────────────────────────────────────────┘
        │
        │ http://localhost:5173
        │
┌───────▼─────────────────┐
│   Vite Dev Server       │ ← Hot Module Replacement (HMR)
│   Port 5173             │ ← Fast refresh for React
└───────┬─────────────────┘
        │
        │ Proxy /api → http://localhost:3000
        │
┌───────▼─────────────────┐
│   API Gateway           │
│   Port 3000             │ ← Routes requests to services
└───────┬─────────────────┘
        │
        ├─────────────┬─────────────┬─────────────┐
        │             │             │             │
┌───────▼──────┐ ┌───▼──────┐ ┌───▼──────┐ ┌───▼──────┐
│ Login        │ │Register  │ │  Game    │ │  Chat    │
│ Service      │ │Service   │ │ Service  │ │ Service  │
│ Port 3001    │ │Port 3002 │ │Port 3003 │ │Port 3004 │
└──────────────┘ └──────────┘ └──────────┘ └──────────┘
```

## Production Mode (Docker + Nginx)
```
┌─────────────────────────────────────────────────────────────────┐
│                         Client                                  │
│                         Browser                                 │
└───────┬─────────────────────────────────────────────────────────┘
        │
        │ https://localhost (443)
        │
┌───────▼─────────────────────────────────────────────────────────┐
│                    Nginx Container                              │
│   - Serves static built React app (/) ─────────────────┐        │
│   - Proxies /api to Gateway                            │        │
│   - SSL/TLS termination                                │        │
└───────┬────────────────────────────────────────────────┼────────┘
        │                                                 │
        │ /api/*                             ┌────────────▼────────┐
        │                                    │  Frontend Build     │
┌───────▼─────────────────┐                 │  (Docker Volume)    │
│   API Gateway           │                 │  Vite built app     │
│   Container: gateway    │                 └─────────────────────┘
│   Port 3000 (internal)  │
└───────┬─────────────────┘
        │
        │ Internal Docker Network: transcendence
        │
        ├──────────────┬──────────────┬──────────────┐
        │              │              │              │
┌───────▼──────┐ ┌────▼──────┐ ┌────▼──────┐ ┌────▼──────┐
│ login        │ │ register  │ │  game     │ │  chat     │
│ Container    │ │ Container │ │Container  │ │Container  │
│ Port 3001    │ │Port 3002  │ │Port 3003  │ │Port 3004  │
│ (internal)   │ │(internal) │ │(internal) │ │(internal) │
└──────────────┘ └───────────┘ └───────────┘ └───────────┘
```

## Service Communication

### Development (Local)
- Frontend → Gateway: Direct HTTP via Vite proxy
- Gateway → Services: Direct HTTP via localhost

### Production (Docker)
- Client → Nginx: HTTPS (443)
- Nginx → Frontend: Serve static files
- Nginx → Gateway: HTTP proxy (internal network)
- Gateway → Services: HTTP via Docker service names

## Port Mapping

| Service    | Dev Port | Docker Internal | Docker Exposed | Production Access |
|------------|----------|----------------|----------------|-------------------|
| Vite       | 5173     | -              | -              | Not used in prod  |
| Gateway    | 3000     | 3000           | 3000 (dev only)| Via Nginx         |
| Login      | 3001     | 3001           | 3001 (dev only)| Via Gateway       |
| Register   | 3002     | 3002           | 3002 (dev only)| Via Gateway       |
| Game       | 3003     | 3003           | 3003 (dev only)| Via Gateway       |
| Chat       | 3004     | 3004           | 3004 (dev only)| Via Gateway       |
| Nginx      | -        | 80, 443        | 80, 443        | Direct            |

## Request Flow Examples

### Development - Login Request
```
Browser → Vite (5173) → Gateway (3000) → Login Service (3001) → Response
```

### Production - Login Request
```
Browser → Nginx (443) → Gateway (3000) → Login Service (3001) → Response
        [HTTPS]        [HTTP proxy]     [Internal HTTP]
```

### Development - Static Asset
```
Browser → Vite (5173) → Serves from src/frontend
        [Direct HMR]
```

### Production - Static Asset
```
Browser → Nginx (443) → Serves from /var/www/html (built files)
        [HTTPS]        [Static file serving]
```
