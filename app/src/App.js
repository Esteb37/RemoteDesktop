import './App.css';

import * as React from 'react';
import * as Mui from '@material-ui/core';
import Alert from '@mui/material/Alert';
import * as Secret from './secret';
import LoadingButton from '@mui/lab/LoadingButton';
import $ from 'jquery';

function App() {
	const [url] = React.useState(`https://${Secret.ip}/`);

	const [loading, setLoading] = React.useState({ run: false, stop: false });

	const [error, setError] = React.useState(null);

	function call(path) {
		setLoading({ ...loading, [path.toLowerCase()]: true });
		setError(null);
		$.ajax({
			url: url + path,
			type: 'GET',
			dataType: 'text',
			error: function (error) {
				// IF error status is 0, it means the server is not reachable
				if (error?.status === 0) {
					setError(`Server is not reachable.`);
					return;
				}

				setError(
					error?.responseText +
						'<br>' +
						error?.statusText +
						'<br>' +
						error?.status +
						'<br>' +
						error?.responseJSON?.error
				);
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
				setStat(data.trim().replaceAll('+', ''));
				setTimeout(getIt, 1000);
			},
			error: function (error) {
				if (error?.status === 0) {
					setError(`Server is not reachable.`);
					return;
				}
				setError(error?.responseText.trim().replaceAll('-', ''));
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
					loading={loading.start}
					style={{ margin: '1rem', width: '10rem' }}
					variant='contained'
					color='primary'
					onClick={() => call('START')}>
					Start
				</LoadingButton>
				<LoadingButton
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

				{error && error !== 'NONE' && (
					<Alert
						severity='error'
						style={{ margin: '1rem', width: '10rem' }}>
						<Mui.Typography
							variant='body2'
							dangerouslySetInnerHTML={{ __html: error }}
						/>
					</Alert>
				)}
			</Mui.Container>
		</div>
	);
}

export default App;
