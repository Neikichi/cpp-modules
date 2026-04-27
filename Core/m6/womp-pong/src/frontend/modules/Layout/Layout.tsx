import React from 'react';
import Sidebar from '../Navbar/Sidebar.js';
import Intro from '../Play/Intro.js';
import Introtest from '../Play/Introtest.js';

interface LayoutProps {
	children?: React.ReactNode;
}

function Layout({ children }: LayoutProps) {
	return (
		<div className="relative h-screen flex flex-row bg-[url('assets/gptblackhole.png')] bg-cover bg-center m-0 p-0 outline-none">
			<div className="w-full h-full absolute top-0 left-0 bg-black opacity-70 z-0 pointer-events-none"></div>
			<Intro />
			<Sidebar />
		</div>
	);
}
export default Layout;
