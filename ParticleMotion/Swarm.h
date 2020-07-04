#pragma once
#include "Particle.h"

namespace Aratorin {
	class Swarm {
	public:
		static const int NPARTICLES = 1000;

	private:
		Particle* const particles = new Particle[NPARTICLES];

	public:
		Swarm();
		~Swarm();
		const Particle* const getParticles() {
			return particles;
		}
		void update();
	};

}
