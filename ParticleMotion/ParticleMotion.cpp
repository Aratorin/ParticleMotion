#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <string>
#include "Screen.h"
#include "ColorMixer.h"
#include "Swarm.h"

using namespace std;
using namespace Aratorin;

SDL_WindowFlags screenFlags = SDL_WINDOW_RESIZABLE;
ColorMixerMode mixerMode = ColorMixerMode::SINWAVE;
int transitionMethod = 3;

int main(int argc, char* argv[]) {
	/*User input----------------------------------------------------------------------------------------------------------------------*/
	cout << "Enter 1 to customize settings, or just hit Enter to use default settings." << endl;
	string userchoice;
	getline(cin, userchoice);

	if (userchoice == "1") {

		cout << endl;
		cout << "Enter an integer between 0 and " << 50000 << " for the number of desired particles (recommended 5000)" << endl;
		cin >> Swarm::NPARTICLES;
		while (Swarm::NPARTICLES < 0 || Swarm::NPARTICLES > 50000) {
			cout << Swarm::NPARTICLES << " is not between 0 and " << 50000 << "!" << endl;
			cout << "Enter an integer between 0 and " << 50000 << " for the number of desired particles (recommended 5000)" << endl;
			cin >> Swarm::NPARTICLES;
		}
		cin.ignore(INT_MAX, '\n');

		cout << endl;

		cout << "Should the particles start in random positions, or at the center of the screen?" << endl;
		cout << "1 = Center of the screen." << endl;
		cout << "2 = Random Positions." << endl;
		userchoice = "";
		while (userchoice.empty()) {
			getline(cin, userchoice);
		}
		while (userchoice != "1" && userchoice != "2") {
			cout << userchoice << " is not a valid selection!" << endl;
			cout << "1 = Center of the screen." << endl;
			cout << "2 = Random Positions." << endl;
			userchoice = "";
			while (userchoice.empty()) {
				getline(cin, userchoice);
			}
		}
		if (userchoice == "1") {
			Particle::PARTICLE_MODE = ParticleMode::CENTERED;
		} else if (userchoice == "2") {
			Particle::PARTICLE_MODE = ParticleMode::RANDOM;
		}

		cout << endl;

		cout << "If a particle moves off the screen, should it bounce back, or respawn?" << endl;
		cout << "1 = Bounce back." << endl;
		cout << "2 = Respawn." << endl;
		userchoice = "";
		while (userchoice.empty()) {
			getline(cin, userchoice);
		}
		while (userchoice != "1" && userchoice != "2") {
			cout << userchoice << " is not a valid selection!" << endl;
			cout << "1 = Bounce back." << endl;
			cout << "2 = Respawn." << endl;
			userchoice = "";
			while (userchoice.empty()) {
				getline(cin, userchoice);
			}
		}
		if (userchoice == "1") {
			Particle::PARTICLE_OFFSCREEN_ACTION = ParticleOffScreenAction::BOUNCE;
		} else if (userchoice == "2") {
			Particle::PARTICLE_OFFSCREEN_ACTION = ParticleOffScreenAction::RESPAWN;
		}

		cout << endl;

		cout << "Fullscreen or Windowed?" << endl;
		cout << "1 = Fullscreen" << endl;
		cout << "2 = Windowed." << endl;
		userchoice = "";
		while (userchoice.empty()) {
			getline(cin, userchoice);
		}
		while (userchoice != "1" && userchoice != "2") {
			cout << userchoice << " is not a valid selection!" << endl;
			cout << "1 = Fullscreen" << endl;
			cout << "2 = Windowed." << endl;
			userchoice = "";
			while (userchoice.empty()) {
				getline(cin, userchoice);
			}
		}

		if (userchoice == "1") {
			screenFlags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		} else if (userchoice == "2") {
			screenFlags = SDL_WINDOW_RESIZABLE;
		}

		cout << endl;

		cout << "What algorith should be used to mix the colors?" << endl;
		cout << "1 = Cosine wave." << endl;
		cout << "2 = Sine wave." << endl;
		cout << "3 = Incremental." << endl;
		userchoice = "";
		while (userchoice.empty()) {
			getline(cin, userchoice);
		}
		while (userchoice != "1" && userchoice != "2" && userchoice != "3") {
			cout << userchoice << " is not a valid selection!" << endl;
			cout << "1 = Cosine wave." << endl;
			cout << "2 = Sine wave." << endl;
			cout << "3 = Incremental." << endl;
			userchoice = "";
			while (userchoice.empty()) {
				getline(cin, userchoice);
			}
		}

		if (userchoice == "1") {
			mixerMode = ColorMixerMode::COSWAVE;
		} else if (userchoice == "2") {
			mixerMode = ColorMixerMode::SINWAVE;
		} else if (userchoice == "3") {
			mixerMode = ColorMixerMode::INCREMENTAL;
		}

		cout << endl;

		cout << "What blur method should be used?" << endl;
		cout << "1 = No blur." << endl;
		cout << "2 = Sharp pixels with blur." << endl;
		cout << "3 = Soft pixels with blur." << endl;
		cout << "4 = Draw lines instead." << endl;
		userchoice = "";
		while (userchoice.empty()) {
			getline(cin, userchoice);
		}
		while (userchoice != "1" && userchoice != "2" && userchoice != "3" && userchoice != "4") {
			cout << userchoice << " is not a valid selection!" << endl;
			cout << "1 = No blur." << endl;
			cout << "2 = Sharp pixels with blur." << endl;
			cout << "3 = Soft pixels with blur." << endl;
			cout << "4 = Draw lines instead." << endl;
			userchoice = "";
			while (userchoice.empty()) {
				getline(cin, userchoice);
			}
		}

		if (userchoice == "1") {
			transitionMethod = 1;
		} else if (userchoice == "2") {
			transitionMethod = 2;
		} else if (userchoice == "3") {
			transitionMethod = 3;
		} else if (userchoice == "4") {
			transitionMethod = 4;
		}

		cout << endl;

	}

	/*Use the current system time to seed the rand() function.*/
	srand(time(NULL));

	/*I've noticed that the first 2 numbers generated by rand() after calling srand(time(NULL))
	  are always fairly similar on any given run of the program, so this is just getting those
	  out of the way for future calls.*/
	rand();
	rand();

	/*The Screen class contains pointers to the SDL_Window, SDL_Renderer,
	  SDL_Texture, and buffer used to display pixels on the screen.*/
	Screen screen;
	/*screen.init() runs SDL_Init(SDL_INIT_VIDEO), and then creates the SDL_Window,
	  SDL_Renderer, SDL_Texture, and buffer, returns true on success, and false if
	  any portion fails. This is used in place of a constructor, as constructors are
	  not able to return values. If screen.init() fails, the program returns 1 and exits.*/
	if (!screen.init(screenFlags)) {
		cout << "Error initializing SDL." << endl;
		return 1;
	}

	/*Sets the maximum and minimum values for particle.y This is necessary for determining
	what the particles do when they get to the edge of the Screen.*/
	Particle::YBOUNDS = Screen::SCREEN_RATIO;

	/*Initial values for red, green, and blue, to be passed to the ColorMixer
	  unsigned char type ensures that each value is between 0 and 255.*/
	unsigned char red = 256 * rand() / RAND_MAX;
	unsigned char green = 256 * rand() / RAND_MAX;
	unsigned char blue = 256 * rand() / RAND_MAX;

	/*The ColorMixer class contains various methods of shifting the red, green, and blue
	  values, that can be called with the cycleColors method.*/
	ColorMixer mixer(red, green, blue);

	/*The Swarm class contains a pointer to an array of Particles. It also tracks
	  the interval, and passes that to each Particle when calling its update funtion.*/
	Swarm swarm;

	/*The "game loop". This is the loop that actually updates and draws the particles.*/
	while (true) {
		/*Update particles------------------------------------------------------------------------------------------------------------*/

		/*Number of milliseconds since SDL Initialization.*/
		int elapsed = SDL_GetTicks();

		/*Uses elapsed to calculate the interval since the last swarm.update, and then calls
		  the update method of each particle passing the interval.*/
		swarm.update(elapsed);

		/*Changes the red, green, and blue values that will be used to draw the particles,
		  using the ColorMixerMode passed to the first parameter and the seed passed to the
		  second parameter, if applicable.*/
		mixer.cycleColors(mixerMode, elapsed);

		/*Draw particles--------------------------------------------------------------------------------------------------------------*/

		/*Sets all pixels in the buffer back to black.*/
		if (transitionMethod == 1) {
			screen.clear();
		}

		/*Blurs the screen using a box blur. Applying blur at this point blurs the screen
		  before drawing the new pixels, which results in sharper pixels, that look like
		  comets. NOT RECOMMENDED FOR HD MODE*/
		if (transitionMethod == 2) {
			screen.boxBlur();
		}

		/*Creates a const pointer to the array of particles in the swarm and treats them as
		  const to avoid accidently modifying any of them, or pointing the pointer to something
		  else. All modifications to the particles should be handeled by the swarm and the
		  particles themselves.*/
		const Particle* const particles = swarm.getParticles();

		/*Cycles through each particle in particles, creating a temporary variable for each
		  particle, and using the x and y coordinates of that particle to draw its
		  corrisponding pixel on the screen.*/
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = particles[i];
			/*The x coordinate of the particle is a double ranging from -1 to +1. The x
			  value of pixels in the screen ranges from 0 to SCREEN_WIDTH. So we add 1 to the
			  x coordinate of the particle to change its range to 0 to 2. Then we multiply that
			  times half SCREEN_WIDTH to get a result that ranges from 0 to SCREEN_WIDTH*/
			int x = (particle.x + 1) * Screen::SCREEN_WIDTH / 2;
			/*The y coordinate of the particle is a double ranging from -1 to +1. The y
			  value of pixels in the screen ranges from 0 to SCREEN_HEIGHT. But, if we add 1
			  to the x coordinate of the particle to change its range to 0 to 2 and then we multiply that
			  times half SCREEN_HEIGHT, we end up with rectangular, or oblong, movement, because
			  the screen is not a 1:1 ratio.
			  To fix that, we have to make sure that we are multiplying both the x and y coordinates
			  by SCREEN_WIDTH. Screen.setPixel multiplies y * SCREEN_WIDTH when it is called (see the
			  comments in Screen.cpp for more detail on that), so if particle.y is 0, which should be
			  half way down the screen, (0 + 1) * SCREEN_WIDTH / 2 ends up being SCREEN_HEIGHT / SCREEN_WIDTH
			  down the screen, rather than SCREEN_HEIGHT / 2 down the screen. So, instead we use
			  p.y * (SCREEN_WIDTH / 2), meaning that if p.y = 0, we are at the top of the screen, and if
			  p.y = (SCREEN_HEIGHT-1) / SCREEN_WIDTH, we are at the bottom of the screen. To get p.y = 0 to the
			  middle of the screen, we then add SCREEN_HEIGHT / 2.
			  This means that p.y values of -1 and +1 are actually off of the screen, but that's not a problem, as
			  the screen.setPixel method checks the coordinates, and if they are off the screen, does not attempt
			  to draw them.
			  All of this is assuming a screen that is wider than it is tall. If the screen is taller than it is
			  wide, the maximum values of p.y actually extend beyond -1 and 1, which is an issue I'll deal with
			  later, when I implement resizing.*/
			/*y = (p.y) * (Screen::SCREEN_WIDTH / 2); <--if p.y=0 this is the top center so adding half the screen height moves it to the center*/
			int y = (particle.y * Screen::SCREEN_WIDTH / 2) + (Screen::SCREEN_HEIGHT / 2);
			/*Sets the value of the pixel at x,y in the buffer to RGBA.*/
			screen.setPixel(x, y, red, green, blue);
		}

		/*Blurs the screen using a box blur. Applying blur at this point blurs the screen
		  after drawing the new pixels, which results in blurier pixels, that look like
		  embers.*/
		if (transitionMethod == 3) {
			screen.boxBlur();
		}

		/*Draw the screen-------------------------------------------------------------------------------------------------------------*/

		/*Updates the screen with the contents of the buffer.*/
		screen.update();

		/*Check for messages/events---------------------------------------------------------------------------------------------------*/

		/*Exits the game loop if the window is closed.*/
		if (screen.processEvents() == false) {
			break;
		}

	}

	/*Calls all of the SDL Cleanup functions.*/
	screen.close();

	return 0;
}
