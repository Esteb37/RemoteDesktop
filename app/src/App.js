import './App.css';

import * as React from 'react';
import * as Mui from '@material-ui/core';
import * as Secret from './secret';
import LoadingButton from '@mui/lab/LoadingButton';
import $ from 'jquery';

function App() {
	const [url] = React.useState(`https://${Secret.ip}/`);

	const [loading, setLoading] = React.useState({ run: false, stop: false });

	function call(path) {
		setLoading({ ...loading, [path.toLowerCase()]: true });

		$.ajax({
			url: url + path,
			type: 'GET',
			dataType: 'text',
			success: function (data) {
				console.log(data);
			},
			error: function (error) {
				alert('Error: ', error);
				console.log('Error: ', error.responseText);
			},
			complete: function () {
				setLoading({ ...loading, [path.toLowerCase()]: false });
			},
		});
	}

	function getIt() {
		$.ajax({
			url: url + 'GETSTAT',
			type: 'GET',
			dataType: 'text',
			success: function (data) {
				setStat(data);
				setTimeout(getIt, 2000);
			},
			error: function (error) {
				alert('Error: ', error);
				console.log('Error: ', error.responseText);
			},
		});
	}

	React.useEffect(() => {
		getIt();
	}, [getIt]);

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
				<LoadingButton
					disabled={stat != 'IDLE'}
					loading={loading.start}
					style={{ margin: '1rem', width: '10rem' }}
					variant='contained'
					color='primary'
					onClick={() => call('START')}>
					Start
				</LoadingButton>
				<LoadingButton
					disabled={stat == 'IDLE'}
					loading={loading.stop}
					style={{ margin: '1rem', width: '10rem' }}
					variant='contained'
					color='secondary'
					onClick={() => call('STOP')}>
					Stop
				</LoadingButton>
				<Mui.Typography variant='h6' style={{ margin: '1rem' }}>
					{stat}
				</Mui.Typography>
			</Mui.Container>
		</div>
	);
}

export default App;
