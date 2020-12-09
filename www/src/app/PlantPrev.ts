export interface PlantPrev {
	name: string;
	size: number;
	deployed: boolean;
	temperature: {
		value: number,
		unit: string
	}
	humidity: {
		value: number,
		unit: string
	};
	moisture: {
		value: number,
		unit: string
	};
	brightness: {
		value: number,
		unit: string
	};
}