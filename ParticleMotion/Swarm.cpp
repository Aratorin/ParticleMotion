#include "Swarm.h"

namespace Aratorin {

	Swarm::Swarm() {}

	Swarm::~Swarm() {
		delete[] particles;
	}

}
