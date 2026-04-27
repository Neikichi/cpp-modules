import { Routes, Route, Link } from 'react-router-dom';
import Layout from './modules/Layout/Layout.js';
// import Play from "./pages/Play";
// import Profile from "./pages/Profile";
import { AuthProvider } from './contexts/AuthContext.js';
import { AppViewProvider } from './contexts/ViewContext.js';

export default function App() {
	return (
		<AppViewProvider>
			<AuthProvider>
				<Layout />
			</AuthProvider>
		</AppViewProvider>
	);
}
