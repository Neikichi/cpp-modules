import React from 'react';

export const IconMenu = ({ size = 24, color = '#000000' }) => (
	<svg
		xmlns="http://www.w3.org/2000/svg"
		width={size}
		height={size}
		viewBox="0 0 24 24"
		fill="none"
		stroke={color}
		strokeWidth="2"
		strokeLinecap="round"
		strokeLinejoin="round"
	>
		<line x1="3" y1="12" x2="21" y2="12"></line>
		<line x1="3" y1="6" x2="21" y2="6"></line>
		<line x1="3" y1="18" x2="21" y2="18"></line>
	</svg>
);

export const IconHome2 = ({ size = 24, color = '#000000' }) => (
	<svg
		xmlns="http://www.w3.org/2000/svg"
		width={size}
		height={size}
		viewBox="0 0 24 24"
		fill="none"
		stroke={color}
		strokeWidth="2"
		strokeLinecap="round"
		strokeLinejoin="round"
	>
		<path d="M20 9v11a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V9" />
		<path d="M9 22V12h6v10M2 10.6L12 2l10 8.6" />
	</svg>
);

export const IconChat = ({ size = 24, color = '#000000' }) => (
	<svg
		width={size}
		height={size}
		viewBox="0 0 24 24"
		fill="none"
		xmlns="http://www.w3.org/2000/svg"
	>
		<path
			d="M8 9.5H15M8 13.5H13M15.3 19.1L21 21L19.1 15.3C19.1 15.3 20 14 20 11.5C20 6.80558 16.1944 3 11.5 3C6.80558 3 3 6.80558 3 11.5C3 16.1944 6.80558 20 11.5 20C14.0847 20 15.3 19.1 15.3 19.1Z"
			stroke={color}
			strokeWidth="1.5"
			strokeLinecap="round"
			strokeLinejoin="round"
		/>
	</svg>
);

export const IconUser = ({ size = 24, color = '#000000' }) => (
	<svg
		xmlns="http://www.w3.org/2000/svg"
		width={size}
		height={size}
		viewBox="0 0 24 24"
		fill="none"
		stroke={color}
		strokeWidth="2"
		strokeLinecap="round"
		strokeLinejoin="round"
	>
		<path d="M5.52 19c.64-2.2 1.84-3 3.22-3h6.52c1.38 0 2.58.8 3.22 3" />
		<circle cx="12" cy="10" r="3" />
		<circle cx="12" cy="12" r="10" />
	</svg>
);

export const IconGuide = ({ size = 24, color = '#000000' }) => (
	<svg
		xmlns="http://www.w3.org/2000/svg"
		viewBox="0 0 1000 1000"
		width={size}
		height={size}
		fill={color}
	>
		<path d="M971 152L526 55q-20-5-41-2-29 6-49 28L73 471q-34 37-52.5 84.5T2 653v16q0 52 30 93.5t79 57.5l427 146q24 8 48.5 1t40.5-27l352-432q10-13 7-30-5-19-16-40-10-16-11-26.5t0-21.5q1-6 4-20l3-10q3-16-3.5-28T939 317q-13-3-23 5-8 6-19 22-8 14-10.5 39t3.5 47q4 11 10 30 4 11-4 20L583 864q-8 9-20.5 13t-24.5 0L143 753q-27-9-44-31.5T82 670v-32q-2-20 6-33t22-17.5 28-.5l392 118q7 2 14 2h1q21 0 36-17l408-478q9-10 9-23v-2q0-12-7.5-22T971 152zM424 493q-16 18-42 26.5t-47 4-24.5-20 12.5-33 42-26 47-3.5 24.5 20-12.5 32zm323-217q-24 26-56 41-36 17-106 31-44 9-64 19-14 7-43 35-8 8-19 5l-12-3q-3-1-4-4t1-5q22-24 37-35 17-14 57-34.5t59-34.5l12-8q26-17 36-28 16-17 22.5-29t4-21.5-13-17T636 178q-18-4-35 1-7 1-14.5 5t-11 8-5.5 14l-1 5q-3 11-4 15-3 8-8 13-15 16-29 20-18 6-34.5 2.5T474 245q-1-8 0-17 3-11 10-19 13-14 35-24 18-8 48-17 28-8 59.5-9t59.5 5q55 13 71 45 7 16 6 33-2 19-16 34z"></path>
	</svg>
);
