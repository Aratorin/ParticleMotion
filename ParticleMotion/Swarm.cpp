#include "Swarm.h"

namespace Aratorin {

	Swarm::Swarm() :lastTime(0) {}

	Swarm::~Swarm() {
		delete[] particles;
	}

	void Swarm::update(int elapsed) {
		int interval = elapsed - lastTime;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			particles[i].update(interval);
		}

		lastTime = elapsed;
	}

}
