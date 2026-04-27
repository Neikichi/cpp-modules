export default function Intro() {
	return (
		<div className="flex flex-col justify-center items-center left-0 top-0 w-full min-h-screen overflow-hidden ml-16 frosted-card outline-none rounded-2xl border-[3px] border-amber-500 shadow-[2px_0_3px_rgba(0,0,0,0.4)] transition-all duration-500 ease-in-out">
			{/* Floating Particles */}
			<div className="absolute inset-0 overflow-hidden pointer-events-none">
				{[...Array(20)].map((_, i) => (
					<div
						key={i}
						className="absolute w-1 h-1 bg-amber-500/40 rounded-full animate-pulse"
						style={{
							left: `${Math.random() * 100}%`,
							top: `${Math.random() * 100}%`,
							animationDelay: `${Math.random() * 3}s`,
							animationDuration: `${2 + Math.random() * 3}s`,
						}}
					/>
				))}
			</div>

			<h2 className="absolute text-white text-4xl py-4 font-bold effect-hover hover:text-amber-500 hover:scale-110 hover:-translate-y-0.5 justify-center items-center flex">
				Welcome to Womp-Pong!
			</h2>
		</div>
	);
}
