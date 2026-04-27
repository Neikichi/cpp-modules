#!/bin/bash

echo "🚀 Womp Pong - Microservices Quick Start"
echo "========================================"
echo ""
echo "Choose your development mode:"
echo ""
echo "1. Local Dev (Vite HMR + Local Services) - Recommended for development"
echo "2. Docker Dev (All services in Docker)"
echo "3. Production Mode (Docker + Nginx)"
echo ""
read -p "Enter choice [1-3]: " choice

case $choice in
  1)
    echo ""
    echo "Starting Local Development Mode..."
    echo "- Building TypeScript services..."
    npm run build:services
    echo ""
    echo "Opening 3 terminals for:"
    echo "  1. TypeScript watch mode"
    echo "  2. All microservices"
    echo "  3. Vite dev server"
    echo ""
    echo "Run these commands in separate terminals:"
    echo ""
    echo "Terminal 1: npm run dev:services:watch"
    echo "Terminal 2: npm run dev:services:start"
    echo "Terminal 3: npm run dev:vite"
    echo ""
    echo "Access: http://localhost:5173"
    ;;
  2)
    echo ""
    echo "Starting Docker Development Mode..."
    npm run docker:dev
    ;;
  3)
    echo ""
    echo "Starting Production Mode..."
    echo "Building application..."
    npm run prod:build
    echo "Starting Docker containers..."
    npm run prod:start
    ;;
  *)
    echo "Invalid choice. Exiting."
    exit 1
    ;;
esac
