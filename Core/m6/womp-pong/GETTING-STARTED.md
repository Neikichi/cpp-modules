# 🚀 Getting Started - Womp Pong Microservices

## ✅ Installation Complete!

Your microservices architecture with SQLite database is now set up and ready to use.

## 📦 What You Have

- **5 Microservices** running independently
- **SQLite Database** with user authentication
- **Vite Dev Server** with hot module replacement
- **2 Test Users** already created

## 🎯 Quick Start (3 Steps)

### Step 1: Start the Backend Services

Open a terminal and run:

```bash
npm run dev:services:start
```

This starts all 5 microservices:
- 🌐 API Gateway (port 3000)
- 🔐 Login Service (port 3001)
- 📝 Register Service (port 3002)
- 🎮 Game Service (port 3003)
- 💬 Chat Service (port 3004)

### Step 2: Start the Frontend

Open a **second terminal** and run:

```bash
npm run dev:vite
```

This starts Vite dev server at http://localhost:5173

### Step 3: Login!

Open your browser to: **http://localhost:5173**

Use these credentials:
- **Username**: `admin`
- **Password**: `adminWomp@42`

Or:
- **Username**: `testuser`
- **Password**: `Test1234!`

## 🔄 Alternative: Watch Mode Development

For active development with auto-recompile:

```bash
# Terminal 1: Watch TypeScript files
npm run dev:services:watch

# Terminal 2: Run all services
npm run dev:services:start

# Terminal 3: Vite dev server
npm run dev:vite
```

## 📋 Available Commands

### Development
```bash
npm run dev:vite              # Vite dev server (HMR)
npm run dev:services:start    # All microservices
npm run dev:services:watch    # Watch TypeScript
```

### Database
```bash
npm run db:seed              # Create test users
npm run db:reset             # Reset database
```

### Production
```bash
npm run prod:build           # Build everything
npm run prod:start           # Start with Docker
```

### Utilities
```bash
npm run clean                # Clean build files
npm run clean:install        # Clean reinstall
```

## 🗄️ Database Info

**Location**: `data/womp-pong.db`

**Default Users**:
1. Admin user
   - Username: `admin`
   - Password: `adminWomp@42`
   - Email: `admin@wompbpong.local`

2. Test user
   - Username: `testuser`
   - Password: `Test1234!`
   - Email: `test@wompbpong.local`

## 🌐 Service Ports

| Service | Port | URL |
|---------|------|-----|
| Vite Dev | 5173 | http://localhost:5173 |
| Gateway | 3000 | http://localhost:3000 |
| Login | 3001 | http://localhost:3001 |
| Register | 3002 | http://localhost:3002 |
| Game | 3003 | http://localhost:3003 |
| Chat | 3004 | http://localhost:3004 |

## 🔍 Verify Services

Check if all services are running:

```bash
./check-health.sh
```

Or manually check:
- Gateway: http://localhost:3000/api/health
- Login: http://localhost:3001/health
- Register: http://localhost:3002/health
- Game: http://localhost:3003/health
- Chat: http://localhost:3004/health

## 🐛 Troubleshooting

### Services won't start
```bash
# Check if ports are in use
lsof -i :3000-3004,5173

# Or on Windows
netstat -ano | findstr "3000"
```

### Database issues
```bash
# Reset database
npm run db:reset
```

### Installation issues
```bash
# Clean reinstall
npm run clean:install
```

### Node version warnings
The project requires Node.js v20+. If you see warnings, consider updating:
```bash
nvm install 20
nvm use 20
```

## 📚 Documentation

- **MICROSERVICES.md** - Architecture overview
- **DATABASE.md** - Database schema & API
- **ARCHITECTURE.md** - Visual diagrams
- **QUICK-REFERENCE.md** - Command reference

## 🎮 Next Steps

1. **Test the login** - Try logging in with the test users
2. **Explore the API** - Check out the microservices endpoints
3. **Build features** - Start developing your game!
4. **Read the docs** - Check out the documentation files

## ✨ Features Ready to Use

✅ User registration with validation  
✅ Login with bcrypt password hashing  
✅ Game session management  
✅ Chat system with rooms  
✅ Hot module replacement for frontend  
✅ Microservices architecture  
✅ SQLite database persistence  

---

**Happy coding! 🚀**

Need help? Check the documentation files or the SETUP-COMPLETE.md file.
