#define _USE_MATH_DEFINES
#include "Particle.h"
#include <cstdlib>
#include <iostream>

namespace Aratorin {

	Particle::Particle(const char* const mode) : mode(mode) {
		init();
	}

	Particle::~Particle() {}

	void Particle::init() {
		x = 0;
		y = 0;

		if (mode == PARTICLE_MODE_RANDOM) {
			x = ((2.0 * rand() / RAND_MAX)) - 1;
			y = ((2.0 * rand() / RAND_MAX)) - 1;
		}

		direction = (2 * M_PI * rand()) / RAND_MAX;
		speed = (0.04 * rand() / RAND_MAX);

		speed *= speed;
	}

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

	void Particle::update(int interval) {
		direction += interval * .0003;

		double xspeed = speed * cos(direction) * interval;
		double yspeed = speed * sin(direction) * interval;

		x += xspeed;
		y += yspeed;

		if (x < -1 || x > 1 || y < -1 || y > 1) {
			init();
		}

		if (rand() < RAND_MAX / 100) {
			init();
		}

	}

}
