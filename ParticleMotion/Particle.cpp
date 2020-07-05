#define _USE_MATH_DEFINES
#include "Particle.h"
#include <cstdlib>

namespace Aratorin {

	Particle::Particle() :x(0), y(0), xforward(true), yforward(true) {
		direction = (2 * M_PI * rand()) / RAND_MAX;
		speed = (0.005 * rand() / RAND_MAX);
	}

	Particle::Particle(const char* const mode) : x(0), y(0), xforward(true), yforward(true) {
		direction = (2 * M_PI * rand()) / RAND_MAX;
		speed = (0.001 * rand() / RAND_MAX);

		if (mode == PARTICLE_MODE_RANDOM) {
			x = ((2.0 * rand() / RAND_MAX)) - 1;
			y = ((2.0 * rand() / RAND_MAX)) - 1;
		}

		//xspeed = (((2.0 * rand() / RAND_MAX)) - 1) * 0.001;
		//yspeed = (((2.0 * rand() / RAND_MAX)) - 1) * 0.001;
	}

	Particle::~Particle() {}

	/*void Particle::update() {
		x += xspeed;
		y += yspeed;

		if (x <= -1.0 || x >= 1.0) {
			xspeed = -xspeed;
		}

		if (y <= -1.0 || y >= 1.0) {
			yspeed = -yspeed;
		}
	}*/

	void Particle::update() {
		if (xforward) {
			double xspeed = speed * cos(direction);
			x += xspeed;
			
			if (x <= -1.0 || x >= 1.0) {
				xforward = !xforward;
			}
		} else {
			double xspeed = speed * cos(direction);
			xspeed = -xspeed;
			x += xspeed;

			if (x <= -1.0 || x >= 1.0) {
				xforward = !xforward;
			}
		}

		if (yforward) {
			double yspeed = speed * sin(direction);
			y += yspeed;

			if (y <= -0.75 || y >= 0.75) {
				yforward = !yforward;
			}
		} else {
			double yspeed = speed * sin(direction);
			yspeed = -yspeed;
			y += yspeed;

			if (y <= -0.75 || y >= 0.75) {
				yforward = !yforward;
			}
		}
	}

}
