#include <iostream>
#include <SDL.h>
#include "Screen.h"
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

	//sets the 4 center pixels to red
	int x = (Screen::SCREEN_WIDTH / 2) - 1, y = (Screen::SCREEN_HEIGHT / 2);
	screen.setPixel(x, y, 0xFF, 0, 0);
	screen.setPixel(x + 1, y++, 0xFF, 0, 0);
	screen.setPixel(x, y, 0xFF, 0, 0);
	screen.setPixel(x + 1, y, 0xFF, 0, 0);

	screen.update();

	while (true) {
		//Update particles
		//Draw particles
		//Check for messages/events
		if (screen.processEvents() == false) {
			break;
		}

	}

	screen.close();

	return 0;
}
