import { useAuth } from '../../contexts/AuthContext.js';

export default function Logged() {
	const { user, logout } = useAuth();

	const handleLogout = (e: React.FormEvent) => {
		e.preventDefault();
		logout();
	};

	return (
		<form
			onSubmit={handleLogout}
			className="flex flex-col justify-center items-center outline-none gap-4 w-full"
		>
			<h2 className="text-white text-4xl py-4 font-bold effect-hover hover:text-amber-500 hover:scale-110 hover:-translate-y-0.5 text-center">
				Welcome Back{user?.username ? `, ${user.username}` : ''}!
			</h2>
			<p className="text-white text-[14px] mb-2 text-center w-3/4 text-wrap font-light">
				You are successfully logged in. Explore your profile, play
				games, and connect with friends!
			</p>
			<button
				type="submit"
				className="bg-amber-500 text-black px-4 py-2 rounded-md font-semibold w-3/4 transition-all duration-200 hover:bg-amber-600 hover:scale-105 hover:-translate-y-0.5"
			>
				Logout
			</button>
		</form>
	);
}
