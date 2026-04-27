import Login from './Login.js';
import Logged from './Logged.js';
import Register from './Register.js';
import Forgot from './Forgot.js';
import React, { useState } from 'react';
import { useAuth } from '../../contexts/AuthContext.js';
import { useAppView } from '../../contexts/ViewContext.js';

export default function Profile() {
	const { view } = useAppView();

	return (
		<div className="flex flex-col justify-center items-center outline-none gap-4">
			<h2 className="text-white text-4xl py-4 font-bold effect-hover hover:text-amber-500 hover:scale-110 hover:-translate-y-0.5">
				Profile
			</h2>
			<div className="w-11/12 h-px bg-amber-500 mb-4"></div>
			<p className="text-white text-[14px] mb-2 text-center w-3/4 text-wrap font-light">
				Please select a login method or continue as Guest with limited
				access
			</p>
			<div className="w-11/12 h-px bg-amber-500 mb-4"></div>
			{(view === 'login' || view === 'guest') && <Login />}
			{view === 'logged' && <Logged />}
			{view === 'register' && <Register />}
			{view === 'forgot' && <Forgot />}
		</div>
	);
}
