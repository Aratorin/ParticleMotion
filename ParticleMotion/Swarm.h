#pragma once
#include "Particle.h"

namespace Aratorin {
	class Swarm {
	public:
		static int NPARTICLES;

	private:
		Particle* const particles = new Particle[NPARTICLES];
		int lastTime;

	public:
		Swarm();
		~Swarm();
		const Particle* const getParticles() {
			return particles;
		}
		void update(int elapsed);
	};

}
