import React from 'react';
import { IconMenu, IconChat, IconUser, IconGuide } from './Icon.js';

interface SidebarMiniProps {
	isExpanded: boolean;
	activeButton: string | null;
	onToggle: (buttonName: string) => void;
}

export default function SidebarMini({
	isExpanded,
	activeButton,
	onToggle,
}: SidebarMiniProps) {
	return (
		<div
			id="sidebar-mini"
			className="w-16 overflow-hidden flex flex-col justify-start items-center p-1
			rounded-r-2xl border-r-[3px] border-r-zinc-500
			shadow-[2px_0_3px_rgba(0,0,0,0.4)]"
		>
			<nav
				id="mini-nav"
				className="flex flex-col justify-center items-center gap-4"
			>
				{/* Menu Button */}
				<button
					onClick={() => onToggle('menu')}
					className={`sidebar-icon-btn
						${activeButton === 'menu' ? 'sidebar-icon-btn-active' : ''}`}
				>
					<IconMenu size={32} color="currentColor" />
				</button>
				<button
					onClick={() => onToggle('guide')}
					className={`sidebar-icon-btn
						${activeButton === 'guide' ? 'sidebar-icon-btn-active' : ''}`}
				>
					<IconGuide size={32} color="currentColor" />
				</button>

				{/* User Button */}
				<button
					onClick={() => onToggle('user')}
					className={`sidebar-icon-btn
						${activeButton === 'user' ? 'sidebar-icon-btn-active' : ''}`}
				>
					<IconUser size={32} color="currentColor" />
				</button>

				{/* Chat Button */}
				<button
					onClick={() => onToggle('chat')}
					className={`sidebar-icon-btn
						${activeButton === 'chat' ? 'sidebar-icon-btn-active' : ''}`}
				>
					<IconChat size={32} color="currentColor" />
				</button>
			</nav>
		</div>
	);
}
