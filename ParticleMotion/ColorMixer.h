#pragma once
#include <cmath>
#include <SDL.h>
using namespace std;

namespace Aratorin {

	enum class ColorMixerMode { INCREMENTAL, COSINWAVE, SINWAVE };
	//const int SINWAVE = 0;
	//const int INCREMENTAL = 1;

	class ColorMixer {
	private:
		unsigned char& red, & green, & blue;
		bool rpp, gpp, bpp;

	public:
		ColorMixer(unsigned char& red, unsigned char& green, unsigned char& blue);
		void cycleColors(ColorMixerMode mode, int seed = 0);

	private:
		void incremental();
		void sinWave(int seed);
	};

}
