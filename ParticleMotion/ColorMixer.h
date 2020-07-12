#pragma once
#include <cmath>
#include <SDL.h>
using namespace std;

namespace Aratorin {

	enum class ColorMixerMode { INCREMENTAL, COSWAVE, SINWAVE };

	class ColorMixer {
	private:
		unsigned char& red, & green, & blue;
		bool rpp, gpp, bpp;

	public:
		ColorMixer(unsigned char& red, unsigned char& green, unsigned char& blue);
		void cycleColors(ColorMixerMode mode, int seed = 0);

	private:
		void incremental();
		void cosWave(int seed);
		void sinWave(int seed);
	};

}
