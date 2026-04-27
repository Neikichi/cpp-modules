#!/bin/bash

echo "🧪 Testing JWT Authentication"
echo "================================"
echo ""

# Test 1: Login
echo "1️⃣ Testing Login..."
LOGIN_RESPONSE=$(curl -s -X POST http://localhost:3000/api/login \
  -H "Content-Type: application/json" \
  -d '{"username":"admin","password":"adminWomp@42"}')

echo "$LOGIN_RESPONSE"
echo ""

# Extract tokens using grep and sed
TOKEN=$(echo "$LOGIN_RESPONSE" | grep -o '"token":"[^"]*"' | head -1 | sed 's/"token":"//;s/"//')
REFRESH_TOKEN=$(echo "$LOGIN_RESPONSE" | grep -o '"refreshToken":"[^"]*"' | head -1 | sed 's/"refreshToken":"//;s/"//')

if [ -z "$TOKEN" ]; then
  echo "❌ Login failed - no token received"
  exit 1
fi

echo "✅ Login successful!"
echo "Access Token: ${TOKEN:0:50}..."
echo ""

# Test 2: Access protected endpoint (Game)
echo "2️⃣ Testing Protected Game Endpoint..."
GAME_RESPONSE=$(curl -s http://localhost:3000/api/game/state \
  -H "Authorization: Bearer $TOKEN")

echo "$GAME_RESPONSE"
echo ""

# Test 3: Create a game
echo "3️⃣ Testing Create Game..."
CREATE_GAME=$(curl -s -X POST http://localhost:3000/api/game/create \
  -H "Authorization: Bearer $TOKEN" \
  -H "Content-Type: application/json" \
  -d '{}')

echo "$CREATE_GAME"
echo ""

# Test 4: Get chat messages
echo "4️⃣ Testing Chat Messages..."
CHAT_RESPONSE=$(curl -s http://localhost:3000/api/chat/messages \
  -H "Authorization: Bearer $TOKEN")

echo "$CHAT_RESPONSE"
echo ""

# Test 5: Send chat message
echo "5️⃣ Testing Send Chat Message..."
SEND_MSG=$(curl -s -X POST http://localhost:3000/api/chat/send \
  -H "Authorization: Bearer $TOKEN" \
  -H "Content-Type: application/json" \
  -d '{"text":"Hello from JWT authenticated user!","roomId":"general"}')

echo "$SEND_MSG"
echo ""

# Test 6: Refresh token
echo "6️⃣ Testing Token Refresh..."
REFRESH_RESPONSE=$(curl -s -X POST http://localhost:3000/api/refresh \
  -H "Content-Type: application/json" \
  -d "{\"refreshToken\":\"$REFRESH_TOKEN\"}")

echo "$REFRESH_RESPONSE"
NEW_TOKEN=$(echo "$REFRESH_RESPONSE" | grep -o '"token":"[^"]*"' | sed 's/"token":"//;s/"//')

if [ -n "$NEW_TOKEN" ]; then
  echo "✅ Token refresh successful!"
  echo "New Token: ${NEW_TOKEN:0:50}..."
else
  echo "❌ Token refresh failed"
fi

echo ""
echo "================================"
echo "🎉 JWT Authentication Tests Complete!"
