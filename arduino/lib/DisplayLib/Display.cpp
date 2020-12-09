#include "Display.h"
#include "images/1.cpp"
#include "images/1_sick.cpp"
#include "images/2.cpp"
#include "images/2_sick.cpp"
#include "images/3.cpp"
#include "images/3_sick.cpp"
#include "images/4.cpp"
#include "images/4_sick.cpp"
#include "images/5.cpp"
#include "images/5_2.cpp"
#include "images/5_sick.cpp"
#include "images/tomb.cpp"


I2C_LCD LCD;

/// Device address configuration, the default value is 0x51.
uint8_t I2C_LCD_ADDRESS = 0x51;

/// Get image data depending on state
GUI_Bitmap_t* requestImage(const Plant& plant, const PlantSpec& spec, const FullMeasurements& measurements) {
    double size = plant.size(spec);

	if (plant.health <= 0) {
		return &bmtomb;
	} else if (size <= spec.maxSize / 5) {
		if (plant.health <= 80)
			return &bm1_sick;
		else
			return &bm1;
	} else if (size <= 2 * spec.maxSize / 5) {
		if (plant.health <= 80)
			return &bm2_sick;
		else
			return &bm2;
	} else if (size <= 3 * spec.maxSize / 5) {
		if (plant.health <= 80)
			return &bm3_sick;
		else
			return &bm3;
	} else if (size <= 4 * spec.maxSize / 5) {
		if (plant.health <= 80)
			return &bm4_sick;
		else
			return &bm4;
	} else {
		if (plant.health <= 80)
			return &bm5_sick;
		else if (measurements.light.value >= 800)
			return &bm5_2;
		else
			return &bm5;
	} 

	return nullptr;
}

Display::Display() : currentImage(nullptr), currentlyConnected(false) {}

void Display::setup() {
	// Display BootLogo, turn on Backlight, set display to bitmap display mode
    LCD.WorkingModeConf(ON, ON, WM_BitmapMode);
}

void Display::draw(const Plant& plant, const PlantSpec& spec, const FullMeasurements& measurements, bool connected) {
	clear();
	GUI_Bitmap_t* image = requestImage(plant, spec, measurements);
	drawPlantImage(image);
	drawConnection(connected);
}

void Display::drawPlantImage(GUI_Bitmap_t* image) {
	if (image != nullptr) {
		LCD.DrawScreenAreaAt(image, 0, 64 - image->YSize);
		this->currentImage = image;
	}
}

void Display::drawConnection(bool connected) {
	LCD_DrawMode mode;
	if (connected) {
		mode = BLACK_FILL;
	} else {
		mode = BLACK_NO_FILL;
	}

	LCD.DrawCircleAt(122, 58, 3, mode);
	this->currentlyConnected = connected;
}

void Display::clear() {
	LCD.CleanAll(WHITE);
}
