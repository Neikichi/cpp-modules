import { createContext, useContext, useState, ReactNode } from 'react';

// Define your possible app views
export type AppView = 'guest' | 'login' | 'register' | 'logged' | 'forgot';

// Define what the context provides
type AppViewContextType = {
	view: AppView;
	setView: (view: AppView) => void;
};

// Create the context (with a null default for safety)
const AppViewContext = createContext<AppViewContextType | null>(null);

// ✅ Provider component
export function AppViewProvider({ children }: { children: ReactNode }) {
	const [view, setView] = useState<AppView>('guest');

	return (
		<AppViewContext.Provider value={{ view, setView }}>
			{children}
		</AppViewContext.Provider>
	);
}

// ✅ Custom hook for convenience
export function useAppView() {
	const ctx = useContext(AppViewContext);
	if (!ctx) throw new Error('useAppView must be used within AppViewProvider');
	return ctx;
}
