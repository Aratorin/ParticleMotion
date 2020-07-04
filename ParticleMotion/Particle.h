#pragma once

namespace Aratorin {

	struct Particle {
	public:
		double x, y;

	public:
		Particle();
		~Particle();
		void update();

	private:
		double xspeed, yspeed;
	};

}
