import React from 'react';
import Profile from './Profile.js';
import Guide from './Guide.js';
import Chat from './Chat.js';
import Menu from './Menu.js';

interface SidebarFullProps {
	isExpanded: boolean;
	activeButton: string | null;
}

export default function SidebarFull({
	isExpanded,
	activeButton,
}: SidebarFullProps) {
	return (
		<div
			id="sidebar-full"
			className={`outline-none rounded-r-2xl border-r-[3px] border-r-amber-500
			shadow-[2px_0_3px_rgba(0,0,0,0.4)] transition-all duration-500 ease-in-out overflow-hidden
			${isExpanded ? 'w-full opacity-100' : 'w-0 opacity-0'}`}
		>
			{activeButton === 'menu' && <Menu />}
			{activeButton === 'user' && <Profile />}
			{activeButton === 'chat' && <Chat />}
			{activeButton === 'guide' && <Guide />}
		</div>
	);
}
