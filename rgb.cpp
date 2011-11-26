#include "rgb.h"

void setLed(const byte ledPin, const byte value) {
	analogWrite(ledPin, value);
}

void setRgbLed(const RGBLED rgbLed) {
	setLed(rgbLed.pinRed, rgbLed.color.r);
	setLed(rgbLed.pinGreen, rgbLed.color.g);
	setLed(rgbLed.pinBlue, rgbLed.color.b);
}

void fadeRgbLeds(RGBLED *leds[], const RGB targets[], const int count) {
	if (leds == 0 || targets == 0 || count == 0) {
		// Null pointer or empty array.
		return;
	}

	RGB start[count];
	int diffRGB[count][3];
	int maxDiff = 0;

	for (int i = 0; i < count; i++) {
		start[i] = (*leds)[i].color;

		// For each LED, calculate the difference between
		// the start color and target color for each channel
		diffRGB[i][0] = targets[i].r - start[i].r;
		diffRGB[i][1] = targets[i].g - start[i].g;
		diffRGB[i][2] = targets[i].b - start[i].b;

		// This is the number of steps it will take to get from
		// the start color to the target color for the channel
		// with the largest difference bettwen the two.
		maxDiff = max(maxDiff,
			max(diffRGB[i][0] < 0 ? -diffRGB[i][0] : diffRGB[i][0],
			max(diffRGB[i][1] < 0 ? -diffRGB[i][1] : diffRGB[i][1],
			diffRGB[i][2] < 0 ? -diffRGB[i][2] : diffRGB[i][2])));
	}

	// Now that we have the maxDiff value, we need to calculate our steps;
	float stepsRGB[count][3];

	// For each channel of each LED, calculate the frequency of each step.
	for (int i = 0; i < count; i++) {
		stepsRGB[i][0] = float(diffRGB[i][0]) / float(maxDiff);
		stepsRGB[i][1] = float(diffRGB[i][1]) / float(maxDiff);
		stepsRGB[i][2] = float(diffRGB[i][2]) / float(maxDiff);
	}

	// Start working. The channel with the largest difference will end up
	// making one step with each cycle through the loop.
	for (int i = 1; i <= maxDiff; i++) {
		for (int ledI = 0; ledI < count; ledI++) {
			(*leds)[ledI].color.r = start[ledI].r + stepsRGB[ledI][0] * i;
			(*leds)[ledI].color.g = start[ledI].g + stepsRGB[ledI][1] * i;
			(*leds)[ledI].color.b = start[ledI].b + stepsRGB[ledI][2] * i;

			setRgbLed(*leds[ledI]);
		}

		if (i < maxDiff) {
			// There will be no delay on the last loop
			delay(3);
		}
	}
}

void fadeRgbLed(RGBLED *rgbLed, const RGB target) {
	if (rgbLed == 0) {
		// The pointer is null
		return;
	}

	fadeRgbLeds(&rgbLed, &target, 1);
}
