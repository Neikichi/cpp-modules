import { useState } from 'react';
import { useAuth } from '../../contexts/AuthContext.js'; // ✅ note lowercase 'contexts' path
import { useAppView } from '../../contexts/ViewContext.js';

export default function Login() {
	const { login } = useAuth();
	const { setView } = useAppView();

	// 🔸 State hooks
	const [username, setUsername] = useState('');
	const [password, setPassword] = useState('');
	const [error, setError] = useState<string | null>(null);
	const [loading, setLoading] = useState(false);

	// 🔸 Handle form submit
	async function handleSubmit(e: React.FormEvent) {
		e.preventDefault();
		setError(null);

		if (!username || !password) {
			setError('Please enter both username and password.');
			return;
		}

		try {
			setLoading(true);
			await login(username, password); // from AuthContext
		} catch (err) {
			if (err instanceof Error) {
				setError(err.message);
			} else {
				setError(String(err));
			}
			// return false;
		} finally {
			setLoading(false);
			return;
		}
	}

	return (
		<form
			onSubmit={handleSubmit}
			className="flex flex-col justify-center items-center gap-4 w-full"
		>
			{/* Username Input */}
			<div className="relative rounded-md w-3/4 flex justify-center items-center hover:shadow-[0_0_10px_rgba(245,158,11,0.4)] hover:shadow-amber-500/40">
				<input
					type="text"
					placeholder={error && !username ? '' : 'Username'}
					value={username}
					onChange={(e) => setUsername(e.target.value)}
					className="bg-zinc-700 p-2 rounded-md text-amber-500 w-full outline-none focus:ring-2 focus:ring-amber-500"
				/>
				{error && !username && (
					<span className="absolute left-3 text-red-400 text-sm animate-pulse">
						Required
					</span>
				)}
			</div>

			{/* Password Input */}
			<div className="relative rounded-md w-3/4 flex justify-center items-center hover:shadow-[0_0_10px_rgba(245,158,11,0.4)] hover:shadow-amber-500/40">
				<input
					type="password"
					placeholder={error && !password ? '' : 'Password'}
					value={password}
					onChange={(e) => setPassword(e.target.value)}
					className="bg-zinc-700 p-2 rounded-md text-amber-500 w-full outline-none focus:ring-2 focus:ring-amber-500"
				/>
				{error && !password && (
					<span className="absolute left-3 text-red-400 text-sm animate-pulse">
						Required
					</span>
				)}
			</div>

			{/* Remember / Forgot */}
			<div className="flex items-center justify-start w-3/4 text-sm">
				<input type="checkbox" className="accent-amber-500 mr-2" />
				<span className="text-white p-0 inline-block">Remember Me</span>
				<span
					onClick={() => setView('forgot')}
					className="ml-auto cursor-pointer transition-transform duration-300 ease-in-out hover:-translate-y-0.5 hover:scale-110 text-amber-600 hover:text-amber-400 font-semibold hover:underline"
				>
					Forgot Password?
				</span>
			</div>

			{/* Error message */}
			{error && (
				<p className="text-red-400 text-sm font-medium animate-pulse text-center w-3/4">
					{error}
				</p>
			)}

			{/* Sign In Button */}
			<button
				type="submit"
				disabled={loading}
				className={`bg-zinc-700 text-amber-500 px-4 py-2 rounded-md font-semibold w-3/4 transition-all duration-200 ${
					loading
						? 'opacity-50 cursor-not-allowed'
						: 'hover:bg-amber-600 hover:scale-105 hover:-translate-y-0.5 hover:text-black'
				}`}
			>
				{loading ? 'Signing in...' : 'Sign In'}
			</button>

			{/* Divider */}
			<div className="flex items-center w-3/4">
				<hr className="grow border-t border-gray-400" />
				<span className="mx-4 text-gray-500 uppercase">or</span>
				<hr className="grow border-t border-gray-400" />
			</div>

			{/* Social Login */}
			<div className="flex gap-4 mb-4">
				{['anonymity', 'google', 'facebook'].map((name) => (
					<button
						key={name}
						type="button"
						className="bg-transparent outline-none border-none rounded-md hover:scale-125 hover:-translate-y-0.5 transition-transform"
					>
						<img
							src={`assets/${name}.png`}
							alt={name}
							className="inline-block w-6 h-6 align-middle"
						/>
					</button>
				))}
			</div>

			{/* Signup Link */}
			<span className="text-sm text-gray-400 justify-center w-full flex gap-2">
				Don&apos;t have an account?
				<span
					onClick={() => setView('register')}
					className="cursor-pointer transition-transform duration-300 ease-in-out hover:-translate-y-0.5 hover:scale-110 text-amber-600 hover:text-amber-400 font-semibold hover:underline"
				>
					Sign Up
				</span>
			</span>
		</form>
	);
}
