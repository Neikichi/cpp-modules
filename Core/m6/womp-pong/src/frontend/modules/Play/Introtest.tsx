import { useState } from 'react';

export default function Introtest() {
	const [selectedMode, setSelectedMode] = useState<string | null>(null);

	const gameModes = [
		{
			id: 'quick',
			title: 'Quick Match',
			description: 'Jump into a fast-paced game',
			icon: '⚡',
			color: 'from-amber-500 to-orange-600',
		},
		{
			id: 'ranked',
			title: 'Ranked',
			description: 'Compete and climb the ladder',
			icon: '🏆',
			color: 'from-purple-500 to-pink-600',
		},
		{
			id: 'tournament',
			title: 'Tournament',
			description: 'Join competitive events',
			icon: '👑',
			color: 'from-cyan-500 to-blue-600',
		},
		{
			id: 'practice',
			title: 'Practice',
			description: 'Hone your skills vs AI',
			icon: '🎯',
			color: 'from-green-500 to-emerald-600',
		},
	];

	return (
		<div className="relative min-h-screen w-full flex flex-col items-center justify-center p-8 overflow-hidden debug-border">
			{/* Animated Background */}
			<div className="absolute inset-0 bg-linear-to-br from-slate-950 via-purple-950 to-slate-900">
				<div className="absolute inset-0 bg-[radial-gradient(circle_at_50%_50%,rgba(139,92,246,0.1),transparent_50%)]"></div>
				<div className="absolute inset-0 bg-[radial-gradient(circle_at_80%_20%,rgba(251,191,36,0.1),transparent_50%)]"></div>
			</div>

			{/* Floating Particles */}
			<div className="absolute inset-0 overflow-hidden pointer-events-none">
				{[...Array(20)].map((_, i) => (
					<div
						key={i}
						className="absolute w-1 h-1 bg-white/20 rounded-full animate-pulse"
						style={{
							left: `${Math.random() * 100}%`,
							top: `${Math.random() * 100}%`,
							animationDelay: `${Math.random() * 3}s`,
							animationDuration: `${2 + Math.random() * 3}s`,
						}}
					/>
				))}
			</div>

			{/* Main Content */}
			<div className="relative z-10 flex flex-col items-center space-y-12 max-w-6xl w-full">
				{/* Title Section */}
				<div className="text-center space-y-4 animate-fade-in">
					<h1 className="text-7xl md:text-8xl font-black bg-linear-to-r from-amber-400 via-orange-500 to-amber-600 bg-clip-text text-transparent drop-shadow-2xl animate-pulse-slow">
						TRANSCENDENCE
					</h1>
					<p className="text-xl md:text-2xl text-gray-300 font-light tracking-wide">
						Choose Your Battle
					</p>

					{/* Stats Bar */}
					<div className="flex gap-8 justify-center mt-6 text-sm text-gray-400">
						<div className="flex items-center gap-2">
							<span className="w-2 h-2 bg-green-500 rounded-full animate-pulse"></span>
							<span>248 Players Online</span>
						</div>
						<div className="flex items-center gap-2">
							<span className="text-amber-500">⚡</span>
							<span>1,337 Games Today</span>
						</div>
					</div>
				</div>

				{/* Game Modes Grid */}
				<div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-6 w-full">
					{gameModes.map((mode, index) => (
						<button
							key={mode.id}
							onClick={() => setSelectedMode(mode.id)}
							className={`frosted-card p-6 cursor-pointer group relative overflow-hidden effect-hover hover:scale-105 hover:-translate-y-2 ${
								selectedMode === mode.id
									? 'ring-2 ring-amber-500'
									: ''
							}`}
							style={{
								animationDelay: `${index * 100}ms`,
								animation: 'slideUp 0.6s ease-out forwards',
							}}
						>
							{/* Gradient Overlay on Hover */}
							<div
								className={`absolute inset-0 bg-linear-to-br ${mode.color} opacity-0 group-hover:opacity-20 transition-opacity duration-300`}
							></div>

							<div className="relative z-10 flex flex-col items-center text-center space-y-3">
								<span className="text-5xl group-hover:scale-110 effect-hover">
									{mode.icon}
								</span>
								<h3 className="text-xl font-bold text-white group-hover:text-amber-400 effect-hover">
									{mode.title}
								</h3>
								<p className="text-sm text-gray-400 group-hover:text-gray-300">
									{mode.description}
								</p>
							</div>

							{/* Selection Indicator */}
							{selectedMode === mode.id && (
								<div className="absolute bottom-2 left-1/2 transform -translate-x-1/2 w-8 h-1 bg-amber-500 rounded-full"></div>
							)}
						</button>
					))}
				</div>

				{/* CTA Button */}
				<button
					disabled={!selectedMode}
					className={`frosted-card px-12 py-4 text-xl font-bold text-white relative overflow-hidden group ${
						selectedMode
							? 'hover:scale-105 cursor-pointer'
							: 'opacity-50 cursor-not-allowed'
					} effect-hover`}
				>
					<div className="absolute inset-0 bg-linear-to-r from-amber-500 to-orange-600 opacity-0 group-hover:opacity-100 transition-opacity duration-300"></div>
					<span className="relative z-10 flex items-center gap-3">
						{selectedMode ? '▶ Start Game' : '↑ Select a Mode'}
					</span>
				</button>

				{/* Bottom Hint */}
				<p className="text-gray-500 text-sm animate-bounce">
					Press ESC to return
				</p>
			</div>

			{/* Inline Keyframe Animations */}
			<style>{`
				@keyframes slideUp {
					from {
						opacity: 0;
						transform: translateY(30px);
					}
					to {
						opacity: 1;
						transform: translateY(0);
					}
				}

				@keyframes pulse-slow {
					0%, 100% {
						opacity: 1;
					}
					50% {
						opacity: 0.8;
					}
				}

				.animate-pulse-slow {
					animation: pulse-slow 3s ease-in-out infinite;
				}

				.animate-fade-in {
					animation: slideUp 0.8s ease-out;
				}
			`}</style>
		</div>
	);
}
