#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include "ColorMixer.h"

using namespace std;
using namespace Aratorin;

int main(int argc, char* argv[]) {

	Screen screen;
	if (screen.init() == false) {
		cout << "Error initializing SLD." << endl;
	}

	//sets all pixels to green
	for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
		for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
			screen.setPixel(x, y, 0, 0XFF, 0);
		}
	}

	unsigned char red = 0, green = 127, blue = 254;

	screen.update();

	ColorMixer mixer(red, green, blue, SINWAVE);

	while (true) {
		//Update particles
		//Draw particles
		//Check for messages/events
		for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x, y, red, green, blue);

			}
		}

		mixer.cycleColors();

		screen.update();


		if (screen.processEvents() == false) {
			break;
		}

	}

	screen.close();

	return 0;
}
