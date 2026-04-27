@echo off
echo.
echo 🚀 Womp Pong - Microservices Quick Start
echo ========================================
echo.
echo Choose your development mode:
echo.
echo 1. Local Dev (Vite HMR + Local Services) - Recommended for development
echo 2. Docker Dev (All services in Docker)
echo 3. Production Mode (Docker + Nginx)
echo.
set /p choice="Enter choice [1-3]: "

if "%choice%"=="1" (
    echo.
    echo Starting Local Development Mode...
    echo - Building TypeScript services...
    call npm run build:services
    echo.
    echo Opening 3 terminals for:
    echo   1. TypeScript watch mode
    echo   2. All microservices
    echo   3. Vite dev server
    echo.
    echo Run these commands in separate terminals:
    echo.
    echo Terminal 1: npm run dev:services:watch
    echo Terminal 2: npm run dev:services:start
    echo Terminal 3: npm run dev:vite
    echo.
    echo Access: http://localhost:5173
) else if "%choice%"=="2" (
    echo.
    echo Starting Docker Development Mode...
    call npm run docker:dev
) else if "%choice%"=="3" (
    echo.
    echo Starting Production Mode...
    echo Building application...
    call npm run prod:build
    echo Starting Docker containers...
    call npm run prod:start
) else (
    echo Invalid choice. Exiting.
    exit /b 1
)
