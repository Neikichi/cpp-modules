import react, { useState } from 'react';
import { useAuth } from '../../contexts/AuthContext.js';
import { useAppView } from '../../contexts/ViewContext.js';

export default function Forgot() {
	const {} = useAuth();
	const { setView } = useAppView();

	const [email, setEmail] = useState('');
	const [error, setError] = useState<string | null>(null);
	const [loading, setLoading] = useState(false);

	async function handleSubmit(e: React.FormEvent) {
		e.preventDefault();
		setError(null);

		if (!email) {
			setError('Please enter your email.');
			return;
		}

		try {
			setLoading(true);
			// await forgotPassword(email);
		} catch (err) {
			if (err instanceof Error) {
				setError(err.message);
			} else {
				setError(String(err));
			}
		} finally {
			setLoading(false);
		}
	}

	return (
		<form
			onSubmit={handleSubmit}
			className="flex flex-col justify-center items-center gap-4 w-full"
		>
			{/* Email Input */}
			<div className="relative rounded-md w-3/4 flex justify-center items-center hover:shadow-[0_0_10px_rgba(245,158,11,0.4)] hover:shadow-amber-500/40">
				<input
					type="email"
					placeholder={error && !email ? '' : 'Email'}
					value={email}
					onChange={(e) => setEmail(e.target.value)}
					className="bg-zinc-700 p-2 rounded-md text-amber-500 w-full outline-none focus:ring-2 focus:ring-amber-500"
				/>
				{error && !email && (
					<span className="absolute left-3 text-red-400 text-sm animate-pulse">
						Required
					</span>
				)}
			</div>
			{/* Error Message */}
			{error && (
				<p className="text-red-400 text-sm text-center w-3/4">
					{error}
				</p>
			)}

			{/* Submit Button */}
			<button
				type="submit"
				disabled={loading}
				className="bg-amber-500 text-white px-4 py-2 rounded-md hover:bg-amber-600 disabled:opacity-50 w-3/4"
			>
				{loading ? 'Submitting...' : 'Submit'}
			</button>
			{/* Go Back to login */}
			<span className="text-sm text-gray-400 justify-center w-full flex gap-2">
				Already have an account?
				<span
					onClick={() => setView('login')}
					className="cursor-pointer transition-transform duration-300 ease-in-out hover:-translate-y-0.5 hover:scale-110 text-amber-600 hover:text-amber-400 font-semibold hover:underline"
				>
					Log In
				</span>
			</span>
		</form>
	);
}
