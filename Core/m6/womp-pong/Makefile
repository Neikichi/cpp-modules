.PHONY: help dev dev-docker prod clean install build

help:
	@echo "Womp Pong - Microservices Makefile"
	@echo "=================================="
	@echo ""
	@echo "Development Commands:"
	@echo "  make dev          - Start local dev mode (Vite + Services)"
	@echo "  make dev-docker   - Start Docker dev mode"
	@echo "  make dev-services - Start all microservices locally"
	@echo "  make dev-vite     - Start Vite dev server only"
	@echo ""
	@echo "Production Commands:"
	@echo "  make prod         - Build and start production mode"
	@echo "  make build        - Build all services and frontend"
	@echo ""
	@echo "Utility Commands:"
	@echo "  make install      - Install dependencies"
	@echo "  make clean        - Clean build artifacts"
	@echo "  make stop         - Stop all Docker containers"
	@echo ""

install:
	npm install

build:
	npm run build:services
	npm run build:vite

dev:
	@echo "Starting Local Development..."
	@echo "Run these in separate terminals:"
	@echo "  Terminal 1: make watch-services"
	@echo "  Terminal 2: make dev-services"
	@echo "  Terminal 3: make dev-vite"

watch-services:
	npm run dev:services:watch

dev-services:
	npm run dev:services:start

dev-vite:
	npm run dev:vite

dev-docker:
	npm run docker:dev

prod:
	npm run prod:build
	npm run prod:start

stop:
	npm run docker:dev:down
	npm run docker:prod:down

clean:
	rm -rf dist node_modules package-lock.json

logs-docker:
	docker-compose -f docker-compose.dev.yml logs -f

logs-prod:
	cd src && docker-compose logs -f
