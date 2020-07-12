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

	//Use the current system time to seed the rand() function.
	srand(time(NULL));

	//The Screen class contains pointers to the SDL_Window, SDL_Renderer, 
	//SDL_Texture, and buffer used to display pixels on the screen.
	Screen screen;

	/*
	screen.init() runs SDL_Init(SDL_INIT_VIDEO), and then creates the SDL_Window,
	SDL_Renderer, SDL_Texture, and buffer, returns true on success, and false if
	any portion fails. This is used in place of a constructor, as constructors are
	not able to return values.

	If screen.init() fails, the program returns 1 and exits.
	*/
	if (!screen.init()) {
		cout << "Error initializing SDL." << endl;
		return 1;
	}

	//Initial values for red, green, and blue, to be passed to the ColorMixer
	//unsigned char type ensures that each value is between 0 and 255.
	unsigned char red = 256 * rand() / RAND_MAX;
	unsigned char green = 256 * rand() / RAND_MAX;
	unsigned char blue = 256 * rand() / RAND_MAX;

	ColorMixer mixer(red, green, blue);

	//The Swarm class contains a pointer to an array of Particles. It also tracks
	//the interval, and passes that to each Particle when calling its update funtion.
	Swarm swarm;

	//"Game loop" this is the loop that actual updates and draws the particles.
	while (true) {
		//Update particles

		//Number of milliseconds since SDL Initialization.
		int elapsed = SDL_GetTicks();
		swarm.update(elapsed);
		//screen.clear();
		mixer.cycleColors(ColorMixerMode::SINWAVE, elapsed);
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
