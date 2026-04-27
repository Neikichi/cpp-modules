import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';
import path from 'path';
import tailwindcss from '@tailwindcss/vite';

export default defineConfig({
	plugins: [react(), tailwindcss()],
	root: 'src/frontend',
	build: {
		outDir: '../../dist/frontend',
		emptyOutDir: true,
	},
	server: {
		port: 5173,
		host: '0.0.0.0',
		strictPort: true,
		proxy: {
			// Proxy all /api requests to the API Gateway
			'/api': {
				target: 'http://localhost:3000',
				changeOrigin: true,
				secure: false,
				rewrite: (path) => path, // Keep /api prefix
			},
		},
	},
	resolve: {
		alias: {
			'@': path.resolve(__dirname, 'src/frontend'),
		},
	},
});
