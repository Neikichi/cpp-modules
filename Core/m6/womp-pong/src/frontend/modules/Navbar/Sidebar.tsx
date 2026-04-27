import React, { useState, useRef, useEffect } from 'react';
import Minibar from './Minibar.js';
import Fullbar from './Fullbar.js';
import { useAppView } from '../../contexts/ViewContext.js';

export default function Sidebar() {
	const [isExpanded, setIsExpanded] = useState(false);
	const [activeButton, setActiveButton] = useState<string | null>(null);
	const sidebarRef = useRef<HTMLDivElement>(null);
	const { view, setView } = useAppView();

	const toggleSidebar = (buttonName: string) => {
		setActiveButton((prev) => {
			const nextActiveButton = prev === buttonName ? null : buttonName;
			setIsExpanded(nextActiveButton !== null);
			return nextActiveButton;
		});

		// setActiveButton((prev) => (prev === buttonName ? null : buttonName));

		// if (activeButton !== buttonName && isExpanded) {
		// 	setIsExpanded(true);
		// } else {
		// 	setIsExpanded((prev) => !prev);
		// }
		// }
	};

	useEffect(() => {
		const handleClickOutside = (event: MouseEvent) => {
			if (
				sidebarRef.current &&
				!sidebarRef.current.contains(event.target as Node)
			) {
				setIsExpanded(false);
				setActiveButton(null);
				// console.log('Clicked outside sidebar', view);
				if (view === 'forgot' || view === 'register') {
					// console.log('Resetting view to login');
					setView('login');
				}
			}
		};
		document.addEventListener('mousedown', handleClickOutside);
		return () =>
			document.removeEventListener('mousedown', handleClickOutside);
	}, [view, setView]);

	return (
		<div
			ref={sidebarRef}
			className={`${isExpanded ? 'w-[25%]' : 'w-16'} absolute h-full bg-black/30 backdrop-blur-md flex transition-all duration-500 ease-in-out outline-none border-none bg-linear-to-b from-black/60 via-zinc-200/40 to-white/20 rounded-r-2xl`}
		>
			<Minibar
				isExpanded={isExpanded}
				activeButton={activeButton}
				onToggle={toggleSidebar}
			/>
			<Fullbar isExpanded={isExpanded} activeButton={activeButton} />
		</div>
	);
}
