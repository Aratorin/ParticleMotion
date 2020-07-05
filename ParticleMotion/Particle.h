#pragma once

namespace Aratorin {

	const char* const PARTICLE_MODE_RANDOM = "RANDOM";
	const char* const PARTICLE_MODE_CENTERED = "CENTERED";

	struct Particle {
	public:
		double x, y;

	public:
		Particle();
		Particle(const char* const mode);
		~Particle();
		void update();

	private:
		double direction, speed;
	};

}
