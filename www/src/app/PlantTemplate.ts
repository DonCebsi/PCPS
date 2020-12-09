export interface PlantTemplate {
	name: string;
	/* General */
	maxSize: number;
	growSpeed: number;
	regenerationSpeed: number;
	/* Temperature */
	tempRange: {
		min: number;
		max: number;
	};
	tempBoost: {
		susceptibility: number;
		range: number;
		amount: number;
		optimum: number;
	};
	/* Moisture */
	moistureThreshold: number;
	moistureStruggleSeconds: number;
	moistureLackSusceptibility: number;
	waterCanGetAboveGround: boolean;
	/* Humidity */
	humidityRange: {
		min: number;
		max: number;
	};
	humidityBoost: {
		susceptibility: number;
		range: number;
		amount: number;
		optimum: number;
	};
	/* Light */
	darkMaxSeconds: number;
	lightMaxSeconds: number;
	darkLightThreshold: number;
	lightBoost: {
		susceptibility: number;
		range: number;
		amount: number;
		optimum: number;
	};
	darkSusceptibility: number;
}