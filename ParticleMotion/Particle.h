#pragma once

namespace Aratorin {

	const char* const PARTICLE_MODE_RANDOM = "RANDOM";
	const char* const PARTICLE_MODE_CENTERED = "CENTERED";

	struct Particle {
	public:
		double x, y;

	private:
		double direction, speed;
		const char* const mode;

	public:
		Particle(const char* const mode = PARTICLE_MODE_CENTERED);
		~Particle();
		void update(int interval);

	private:
		void init();
	};

}
