#include <WProgram.h>

struct RGB {
	byte r;
	byte g;
	byte b;
};

const struct RGB RGB_BLACK = {0, 0, 0};
const struct RGB RGB_WHITE = {255, 255, 255};
const struct RGB RGB_RED   = {255, 0, 0};
const struct RGB RGB_GREEN = {0, 255, 0};
const struct RGB RGB_BLUE  = {0, 0, 255};

struct RGBLED {
	const byte pinRed;
	const byte pinGreen;
	const byte pinBlue;
	RGB color;
};

void setRgbLed(const RGBLED rgbLed);

// The number of leds and targets must be the same number as passed in count.
void fadeRgbLeds(RGBLED *leds[], const RGB targets[], const int count);

void fadeRgbLed(RGBLED *rgbLed, const RGB target);