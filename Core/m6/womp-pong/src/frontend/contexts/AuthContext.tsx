import {
	createContext,
	useContext,
	useState,
	ReactNode,
	useEffect,
} from 'react';
import { useAppView } from './ViewContext';

type User = { username: string; token?: string };

type AuthContextType = {
	user: User | null;
	login: (username: string, password: string) => Promise<void>;
	logout: () => void;
	register: (
		username: string,
		password: string,
		email: string
	) => Promise<void>;
};

const AuthContext = createContext<AuthContextType | null>(null);

export function AuthProvider({ children }: { children: ReactNode }) {
	const [user, setUser] = useState<User | null>(null);
	const { setView } = useAppView();

	async function login(username: string, password: string) {
		const res = await fetch('/api/login', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify({ username, password }),
		});

		const data = await res.json().catch(() => ({}));
		if (!res.ok) throw new Error(data.error || 'Login failed');

		console.log('Login successful:', data);

		setUser({ username, token: data.token });
		setView('logged');
		localStorage.setItem('token', data.token);
	}

	function logout() {
		setUser(null);
		setView('login');
		localStorage.removeItem('token');
	}

	async function register(username: string, password: string, email: string) {
		const res = await fetch('/api/register', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify({ username, password, email }),
		});

		const data = await res.json().catch(() => ({}));
		if (!res.ok) throw new Error(data.error || 'Registration failed');

		console.log('Registration successful:', data);
		setView('login');
	}

	useEffect(() => {
		const token = localStorage.getItem('token');
		if (token) setUser({ username: 'session', token });
	}, []);

	return (
		<AuthContext.Provider value={{ user, login, logout, register }}>
			{children}
		</AuthContext.Provider>
	);
}

export function useAuth() {
	const ctx = useContext(AuthContext);
	if (!ctx) throw new Error('useAuth must be used within AuthProvider');
	return ctx;
}
