#include "Particle.h"
#include <cstdlib>

namespace Aratorin {

	Particle::Particle() {
		x = ((2.0 * rand() / RAND_MAX)) - 1;
		y = ((2.0 * rand() / RAND_MAX)) - 1;
		xspeed = (((2.0 * rand() / RAND_MAX)) - 1) * 0.001;
		yspeed = (((2.0 * rand() / RAND_MAX)) - 1) * 0.001;
	}

	Particle::~Particle() {}

	void Particle::update() {
		x += xspeed;
		y += yspeed;

		if (x <= -1.0 || x >= 1.0) {
			xspeed = -xspeed;
		}

		if (y <= -1.0 || y >= 1.0) {
			yspeed = -yspeed;
		}
	}

}
