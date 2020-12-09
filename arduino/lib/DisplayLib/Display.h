#pragma once

#include <inttypes.h>
#include "I2C_LCD.h"

#include "Plant.h"


class Display {
private:
    GUI_Bitmap_t* currentImage;
    bool currentlyConnected;
    
    /// Draws the current plant image.
    void drawPlantImage(GUI_Bitmap_t* image);

    /// Draws an indicator whether the rasbpi is connected.
    void drawConnection(bool connected);

public:
    /// Creates display handle.
    Display();

    /// Initializes everything needed to use the display.
    void setup();

    /// Draws plant and status info.
    void draw(const Plant& plant, const PlantSpec& spec, const FullMeasurements& measurements, bool connected);

    /// Clears the screen.
    void clear();
};
