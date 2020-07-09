#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "Screen.h"
#include "ColorMixer.h"
#include "Swarm.h"

using namespace std;
using namespace Aratorin;

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Screen screen;
	if (screen.init() == false) {
		cout << "Error initializing SDL." << endl;
	}

	unsigned char red = 0, green = 0, blue = 0;

	Swarm swarm;

	while (true) {
		//Update particles
		int elapsed = SDL_GetTicks();
		ColorMixer mixer(red, green, blue, SINWAVE, elapsed);
		swarm.update(elapsed);
		//screen.clear();
		mixer.cycleColors();
		const Particle* const particles = swarm.getParticles();

		//Draw particles
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = particles[i];
			int x = (particle.x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = (particle.y * Screen::SCREEN_WIDTH / 2) + (Screen::SCREEN_HEIGHT / 2);
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();
		//Draw the screen
		screen.update();

		//Check for messages/events
		if (screen.processEvents() == false) {
			break;
		}

	}

	screen.close();

	return 0;
}
