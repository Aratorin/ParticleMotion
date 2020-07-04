#include "Swarm.h"

namespace Aratorin {

	Swarm::Swarm() {}

	Swarm::~Swarm() {
		delete[] particles;
	}

	void Swarm::update() {
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			particles[i].update();
		}
	}
	
}
