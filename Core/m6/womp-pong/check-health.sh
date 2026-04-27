#!/bin/bash

echo "🔍 Checking Microservices Health..."
echo "===================================="
echo ""

check_service() {
    local name=$1
    local url=$2
    
    if curl -s -f "$url" > /dev/null 2>&1; then
        echo "✅ $name - Running"
    else
        echo "❌ $name - Not responding"
    fi
}

echo "Checking local services:"
check_service "API Gateway  (3000)" "http://localhost:3000/api/health"
check_service "Login Service(3001)" "http://localhost:3001/health"
check_service "Reg Service  (3002)" "http://localhost:3002/health"
check_service "Game Service (3003)" "http://localhost:3003/health"
check_service "Chat Service (3004)" "http://localhost:3004/health"
check_service "Vite Dev     (5173)" "http://localhost:5173"

echo ""
echo "Checking Docker containers:"
docker ps --filter "name=gateway" --filter "name=login" --filter "name=register" --filter "name=game" --filter "name=chat" --filter "name=nginx" --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}"

echo ""
echo "Network connectivity:"
echo "If services are in Docker, they communicate via the 'transcendence' network"
docker network inspect transcendence > /dev/null 2>&1 && echo "✅ Docker network 'transcendence' exists" || echo "ℹ️  Docker network not created (normal for local dev)"
