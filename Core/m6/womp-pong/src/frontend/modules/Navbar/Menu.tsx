async function handleSubmit(e: React.FormEvent) {
	e.preventDefault();
	try {
		const res = await fetch('http://localhost:3000/api/hello', {
			method: 'GET',
			headers: { 'Content-Type': 'application/json' },
		});
		const data = await res.json();
		console.log(data);
	} catch (error) {
		console.error('Error fetching API:', error);
	}
}
export default function Menu() {
	return (
		<div className="flex flex-col justify-center items-center outline-none gap-4 w-full">
			<h2 className="text-white text-4xl py-4 font-bold effect-hover hover:text-amber-500 hover:scale-110 hover:-translate-y-0.5">
				Womp-Pong
			</h2>
			<div className="w-11/12 h-px bg-amber-500 mt-4 mb-4"></div>

			<form
				onSubmit={handleSubmit}
				className="flex flex-col justify-center items-center outline-none gap-4 w-3/4"
			>
				<button
					type="submit"
					className="bg-amber-500 hover:bg-amber-600 text-white p-2 font-bold rounded-lg shadow-md transition duration-300 ease-in-out"
				>
					Play Now
				</button>
			</form>

			<div className="w-11/12 h-px bg-amber-500 mt-4 mb-4"></div>
		</div>
	);
}
