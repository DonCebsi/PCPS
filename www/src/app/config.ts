export const CHART_CONFIG = {
	type: 'line',
	data: {
		labels: [],
		datasets: [
			{
				label: 'size',
				data: [],
				borderColor: "rgb(0,0,0)",
				borderWidth: 2,
				fill: false,
				pointRadius: 0,
				yAxisID: 'less'
			},
			{
				label: 'health',
				data: [],
				borderColor: "rgb(0,255,0)",
				borderWidth: 1,
				fill: false,
				pointRadius: 0,
				yAxisID: 'hundred'
			},
			{
				label: 'temperature',
				data: [],
				borderColor: "rgb(225,0,0)",
				borderWidth: 1,
				fill: false,
				pointRadius: 0,
				yAxisID: 'hundred'
			},
			{
				label: 'moisture',
				data: [],
				borderColor: "rgb(0,0,255)",
				borderWidth: 1,
				fill: false,
				pointRadius: 0,
				yAxisID: 'five-thousand'
			},
			{
				label: 'humidity',
				data: [],
				borderColor: "rgb(0,225,255)",
				borderWidth: 1,
				fill: false,
				pointRadius: 0,
				yAxisID: 'hundred'
			},
			{
				label: 'brightness',
				data: [],
				borderColor: "rgb(225,225,0)",
				borderWidth: 1,
				fill: false,
				pointRadius: 0,
				yAxisID: 'five-thousand'
			},
			{
				label: 'waterAboveGround',
				data: [],
				borderColor: "rgb(150,0,255)",
				borderWidth: 1,
				fill: false,
				pointRadius: 0,
				yAxisID: 'less'
			}
		]
	},
	options: {
		scales: {
			yAxes: [{
				id: 'hundred',
				flip: true,
				ticks: {
					beginAtZero:true
				}
			},{
				id: 'five-thousand',
				ticks: {
					beginAtZero:true
				}
			},{
				id: 'less',
				position: 'right',
				flip: true,
				ticks: {
					beginAtZero:true
				}
			}]
		}
	}
};
