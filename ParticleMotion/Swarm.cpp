#include "Swarm.h"

namespace Aratorin {

	int Swarm::NPARTICLES = 5000;// *1.35;

	Swarm::Swarm() :lastTime(0) {}

	Swarm::~Swarm() {
		delete[] particles;
	}

	void Swarm::update(int elapsed) {
		int interval = elapsed - lastTime;

		for (int i = 0; i < NPARTICLES; i++) {
			particles[i].update(interval);
		}

		lastTime = elapsed;
	}

}
