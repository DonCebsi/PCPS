#pragma once

#define _USE_MATH_DEFINES
#include <Arduino.h>

#include "Sensors.h"

/// A range from minimum to maximum.
template <class T>
struct Range {
	T min;
	T max;
};

/// Defines a sector in which a plant grows better.
template <class T>
struct BoostParameters {
	T     optimum;
	float amount;                               /* ]0;+Inf[ */
	float range;                                /* ]0;+Inf[ */
	float susceptibility;                       /* ]0;100[  */
};

enum PlantType {
	ROSE
};

/// Defines the growth behaviour of a plant.
struct PlantSpec {
	float maxSize;                   			/* ]0;+Inf[ */
	float growSpeed;                 			/*   ]0;1[  */
	float regenerationSpeed;         			/* ]0;+Inf[ */

	Range<float> temperatureRange;   			/* [-40;80] */
	BoostParameters<float> temperatureBoost;

	uint16_t   moistureThreshold;         		/* [0;950]  */
	uint32_t   moistureStruggleSeconds;   		/* [0;+Inf[ */
	float moistureLackSusceptibility;			/* ]0;100[  */
	bool  waterCanGetAboveGround;

	Range<float> humidityRange;      			/* ]0.05;0.99[ */
	BoostParameters<float> humidityBoost;

	uint64_t   darkMaxSeconds;            		/* ]0;+Inf[ */
	uint64_t   lightMaxSeconds;           		/* [0;+Inf[ */
	uint32_t   darkLightThreshold;        		/* [0;40000] */
	float darkSusceptibility;        			/* ]0;100[  */
	BoostParameters<uint16_t> lightBoost;

	/// Creates an undefined specification
	PlantSpec();

	/// Creates a predefined specification
	PlantSpec(PlantType type);

	/// Checks if this specification is valid.
	bool valid();
};

/// Stores information about a plant and simulates it.
class Plant {
public:
	float health;
	float progress;
	uint32_t struggleStarted;
	uint32_t lightStarted;
	uint32_t darkStarted;

	/// Creates a plant with defaults.
	Plant();

	/// Calculates how big this plant is based on it's progress.
	double size(const PlantSpec& spec) const;

	/// Evolves the plant by one step.
	void evolve(const PlantSpec& spec, const FullMeasurements& sensors, uint32_t time);
};
