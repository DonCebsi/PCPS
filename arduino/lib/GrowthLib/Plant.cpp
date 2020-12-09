#include "Plant.h"


/// Calculate a bell function value for the boost params
template <class T>
double calculateMultiplicator(T value, const BoostParameters<T>& params) {
	return 1 + (params.amount * 6.25 * ((1 / (2 * PI)) * pow(EULER, (-1 / params.range)*pow(value - params.optimum, 2))));
}

/// Check if value is in range
template <class T>
bool valueInRange(T val, const Range<T>& r) {
	return val >= r.min && val <= r.max;
}

/// Return the limit of the range to which the value is closer
template <class T>
T closerLimit(T val, const Range<T>& r) {
	T min_dist = abs(val - r.min);
	T max_dist = abs(val - r.max);
	if (min_dist > max_dist) return r.max;
	return r.min;
}


Plant::Plant() : health(100), progress(0), struggleStarted(0), lightStarted(0), darkStarted(0) {}

double Plant::size(const PlantSpec& spec) const {
	return spec.maxSize - spec.maxSize * pow(EULER, - spec.growSpeed * this->progress);
}

void Plant::evolve(const PlantSpec& spec, const FullMeasurements& sensors, uint32_t time) {
	bool suffered = false;
	bool grown = false;

	// Check if the plant already died
	if (this->health <= 0)
		return;

	double multipliers[4] = {};

	// Check if temperature is in range
	if (valueInRange(sensors.temperature.value, spec.temperatureRange)) {
		// Yes: Calculate multiplier. Push to list. Continue.
		multipliers[0] = calculateMultiplicator(sensors.temperature.value, spec.temperatureBoost);
	} else {
		// No: Immediately decline health by using decline step calculation -x*Abs(tempout)*resistancy
		suffered = true;
		this->health = this->health -
			abs(closerLimit(sensors.temperature.value, spec.temperatureRange)- sensors.temperature.value) * spec.temperatureBoost.susceptibility;
	}

	// Check if moisture is above threshold
	if (sensors.moisture.value > spec.moistureThreshold) {
		// Growing allowed
		multipliers[1] = 1;
		this->struggleStarted = 0;
	} else {
		// No: Check if struggle period is over threshold and plant is dry
		if (spec.waterCanGetAboveGround && sensors.water.value) {
			this->struggleStarted = 0;
		} else if (this->struggleStarted == 0) {
			// Start struggle for life
			this->struggleStarted = time;
		} else if (time - this->struggleStarted >= spec.moistureStruggleSeconds) {
			// Yes: Decline health linearely
			this->health -= spec.moistureLackSusceptibility;
			suffered = true;
		} else {
			// No: Continue to struggle.
			suffered = true;
		}
	}

	// Check if humidity is in range
	if (valueInRange(sensors.humidity.value, spec.humidityRange)) {
		// Yes: Calculate multiplier. Push to list. Continue.
		multipliers[2] = calculateMultiplicator(sensors.humidity.value, spec.humidityBoost);
	} else {
		// No: Immediately decline health by using decline step calculation -x*Abs(humout)*resistancy
		suffered = true;
		this->health = this->health -
			abs(closerLimit(sensors.humidity.value, spec.humidityRange) - sensors.humidity.value) * spec.humidityBoost.susceptibility;
	}

	// Check if light is above dawn threshold
	if (sensors.light.value > spec.darkLightThreshold) {
		this->darkStarted = 0;
		// Yes: Check if maximum lightspan has been exeeded.
		if (this->lightStarted == 0) {
			this->lightStarted = time;
		} else if (time - this->lightStarted > spec.lightMaxSeconds) {
			// Yes: Immediately decline health by using decline step calculation -x*resistancy
			this->health = this->health - spec.lightBoost.susceptibility;
			suffered = true;
		} else {
			// No: Check if health has been declining in this step
			if (!suffered) {
				// No: Get multiplicator, Grow by avg(multiplicators)
				multipliers[3] = calculateMultiplicator(sensors.light.value, spec.lightBoost);
				double avg = 0;
				for (size_t i = 0; i < (sizeof(multipliers) / sizeof(*multipliers)); i++)
				{
					avg += multipliers[i];
				}
				avg /= 4;
				this->progress = this->progress + avg;
				grown = true;
			}
		}

	} else {
		this->lightStarted = 0;
		// No: Check if maximum nightspan has been exeeded.
		if (this->darkStarted == 0) {
			this->darkStarted = time;
		} else if (time - this->lightStarted > spec.lightMaxSeconds) {
			// Yes: Decline using decline step calculation -x*resistancy
			this->health = this->health - spec.darkSusceptibility;
			suffered = true;
		}
		// No: Do nothing
	}

	// If we have grown and health has not declined, regenerate by regenerationStep
	if (grown && this->health < 100)
		this->health += spec.regenerationSpeed;
}


PlantSpec::PlantSpec() {}

PlantSpec::PlantSpec(PlantType type) {
	if (type == ROSE) {
		maxSize = 1.2f;
		growSpeed = 0.01f;
		regenerationSpeed = 2.0f;

		temperatureRange = Range<float>();
		temperatureRange.min = 18.0f;
		temperatureRange.max = 29.0f;
		temperatureBoost = BoostParameters<float>();
		temperatureBoost.optimum = 24.0f;
		temperatureBoost.range = 3.0f;
		temperatureBoost.amount = 1.0f;
		temperatureBoost.susceptibility = 1.0f;

		moistureThreshold = 80;
		moistureStruggleSeconds = 2;
		moistureLackSusceptibility = 1.0f;
		waterCanGetAboveGround = false;

		humidityRange = Range<float>();
		humidityRange.min = 32.0f;
		humidityRange.max = 70.0f;
		humidityBoost = BoostParameters<float>();
		humidityBoost.optimum = 50.0f;
		humidityBoost.amount = 1.2f;
		humidityBoost.range = 10.0f;
		humidityBoost.susceptibility = 5.0f;

		darkMaxSeconds = 10;
		lightMaxSeconds = (uint32_t)60 * (uint32_t)60 * (uint32_t)20;

		darkLightThreshold = 60;
		darkSusceptibility = 0.001f;
		lightBoost = BoostParameters<uint16_t>();
		lightBoost.optimum = 700;
		lightBoost.amount = 0.7f;
		lightBoost.range = 200.0f;
		lightBoost.susceptibility = 0.00001f;
	}
}


template <class T>
bool checkRange(Range<T> r, T min, T max) {
	if (r.min > r.max) return false;
	if (r.min < min || r.min > max) return false;
	if (r.min < min || r.min > max) return false;
	return true;
}

template <class T>
bool checkBoostParams(BoostParameters<T> b, T min, T max) {
	if (b.optimum > max) return false;
	if (b.optimum < min) return false;

	if (b.amount <= 0) return false;
	if (b.range <= 0) return false;
	if (b.susceptibility <= 0 || b.susceptibility >= 100) return false;

	return true;
}

bool PlantSpec::valid() {
	if (maxSize <= 0) return false;
	if (growSpeed <= 0 || growSpeed >= 1) return false;
	if (regenerationSpeed <= 0) return false;

	if (!checkRange(temperatureRange, (float)-40., (float)80.)) return false;
	if (!checkRange(humidityRange, (float)0.05, (float)0.99)) return false;

	if (!checkBoostParams(temperatureBoost, (float)-40, (float)80)) return false;
	if (!checkBoostParams(humidityBoost, (float)0.05, (float)0.99)) return false;
	if (!checkBoostParams(lightBoost, (uint16_t)0, (uint16_t)40000)) return false;

	if (moistureStruggleSeconds < 0) return false;
	if (darkMaxSeconds < 0) return false;
	if (moistureThreshold < 0 || moistureThreshold > 950) return false;
	if (lightMaxSeconds <= 0) return false;
	if (lightMaxSeconds <= 0 || lightMaxSeconds >= 100) return false;
	if (moistureLackSusceptibility <= 0 || moistureLackSusceptibility >= 100) return false;
	if (darkLightThreshold < 0 || darkLightThreshold > 40000) return false;

	return true;
}
