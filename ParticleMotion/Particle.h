#pragma once

namespace Aratorin {

	enum class ParticleMode { CENTERED, RANDOM };
	enum class ParticleOffScreenAction { BOUNCE, RESPAWN };

	struct Particle {
	public:
		static ParticleMode PARTICLE_MODE;
		static ParticleOffScreenAction PARTICLE_OFFSCREEN_ACTION;
		static double YBOUNDS;
		double x, y;

	private:
		double direction, speed;
		ParticleMode mode;
		ParticleOffScreenAction action;
		bool xreverse, yreverse;

	public:
		Particle(ParticleMode mode = PARTICLE_MODE, ParticleOffScreenAction action = PARTICLE_OFFSCREEN_ACTION);
		~Particle();
		void update(int interval);

	private:
		void init();
	};

}
