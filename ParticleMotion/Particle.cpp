#define _USE_MATH_DEFINES
#include "Particle.h"
#include <cstdlib>

namespace Aratorin {

	ParticleMode Particle::PARTICLE_MODE = ParticleMode::CENTERED;

	ParticleOffScreenAction Particle::PARTICLE_OFFSCREEN_ACTION = ParticleOffScreenAction::RESPAWN;

	double Particle::YBOUNDS = 1;

	Particle::Particle(ParticleMode mode, ParticleOffScreenAction action) :mode(mode), action(action) {
		init();
	}

	Particle::~Particle() {}

	void Particle::init() {
		switch (mode) {
		case ParticleMode::CENTERED:
			x = 0;
			y = 0;
			break;
		case ParticleMode::RANDOM:
			x = ((2.0 * rand() / RAND_MAX)) - 1;
			y = ((2.0 * rand() / RAND_MAX)) - 1;
			break;
		default:
			break;
		}

		direction = (2 * M_PI * rand()) / RAND_MAX;
		speed = (0.04 * rand() / RAND_MAX);

		speed *= speed;

		xreverse = false;
		yreverse = false;
	}

	void Particle::update(int interval) {
		double xspeed;
		double yspeed;

		switch (action) {
		case Aratorin::ParticleOffScreenAction::BOUNCE:
			if (!xreverse) {
				//cout << "x forward" << endl;
				xspeed = speed * cos(direction) * interval;
			} else {
				xspeed = -(speed * cos(direction) * interval);
			}

			if (!yreverse) {
				//cout << "y forward" << endl;
				yspeed = speed * sin(direction) * interval;
			} else {
				yspeed = -(speed * sin(direction) * interval);
			}

			x += xspeed;
			y += yspeed;
			//cout << "x: " << x << " ,y: " << y << endl;

			if (x <= -1) {
				x = -1;
				xreverse = !xreverse;
			}

			if (x >= 1) {
				x = 1;
				xreverse = !xreverse;
			}

			if (y <= -YBOUNDS) {
				y = -YBOUNDS;
				yreverse = !yreverse;
			}
			
			if(y >= YBOUNDS) {
				y = YBOUNDS;
				yreverse = !yreverse;
			}

			break;
		case Aratorin::ParticleOffScreenAction::RESPAWN:
			direction += interval * .0003;

			xspeed = speed * cos(direction) * interval;
			yspeed = speed * sin(direction) * interval;

			x += xspeed;
			y += yspeed;

			if (x < -1 || x > 1 || y < -1 || y > 1) {
				init();
			}

			if (rand() < RAND_MAX / 100) {
				init();
			}

			break;
		default:
			xspeed = speed * cos(direction) * interval;
			yspeed = speed * sin(direction) * interval;

			x += xspeed;
			y += yspeed;

			break;
		}
	}

}
