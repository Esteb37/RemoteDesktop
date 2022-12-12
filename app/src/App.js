import './App.css';

import * as React from 'react';
import * as Mui from '@material-ui/core';
import * as Secret from './secret';
import $ from 'jquery';

function run() {
	const url = `https://${Secret.ip}/START`;

	try {
		$.ajax({
			url: url,
			type: 'GET',
			dataType: 'text',
			success: function (data) {
				console.log(data);
			},
			error: function (error) {
				console.log('Error: ', error.responseText);
			},
		});
	} catch (error) {
		console.log('Error: ', error);
	}
}

function stop() {
	// Send http request to ip
	const url = `https://${Secret.ip}/STOP`;

	try {
		$.ajax({
			url: url,
			type: 'GET',
			dataType: 'text',
			success: function (data) {
				console.log(data);
			},
			error: function (error) {
				console.log('Error: ', error.responseText);
			},
		});
	} catch (error) {
		console.log('Error: ', error);
	}
}

function App() {
	React.useEffect(() => {
		// Call getStatus() every 1 second, only when the previous request was successful
		const interval = setInterval(() => {
			const url = `https://${Secret.ip}/STATUS`;

			try {
				$.ajax({
					url: url,
					type: 'GET',
					dataType: 'text',
					success: function (data) {
						setStat(data);
					},
					error: function (error) {
						console.log('Error: ', error.responseText);
					},
				});
			} catch (error) {
				console.log('Error: ', error);
			}
		}, 1000);
	}, []);

	const [stat, setStat] = React.useState('Waiting for status...');

	return (
		<div className='App'>
			{
				//A button that sends run() and another that sends stop(), centered to the screen, with a 1rem margin
			}
			<Mui.Container
				style={{
					display: 'flex',
					flexDirection: 'column',
					justifyContent: 'center',
					alignItems: 'center',
					height: '100vh',
					width: '100vw',
				}}>
				<Mui.Button
					style={{ margin: '1rem', width: '10rem' }}
					variant='contained'
					color='primary'
					onClick={run}>
					Run
				</Mui.Button>
				<Mui.Button
					style={{ margin: '1rem', width: '10rem' }}
					variant='contained'
					color='secondary'
					onClick={stop}>
					Stop
				</Mui.Button>
				<Mui.Typography variant='h6' style={{ margin: '1rem' }}>
					{stat}
				</Mui.Typography>
			</Mui.Container>
		</div>
	);
}

export default App;
