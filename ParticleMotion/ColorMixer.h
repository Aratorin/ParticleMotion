#pragma once
#include <math.h>
#include <SDL.h>
using namespace std;

namespace Aratorin {

	const int SINWAVE = 0;
	const int INCREMENTAL = 1;

	class ColorMixer {
	private:
		unsigned char& red, & green, & blue;
		bool rpp, gpp, bpp;
		int mode, elapsed;

	public:
		ColorMixer(unsigned char& red, unsigned char& green, unsigned char& blue, const int mode);
		void cycleColors();

	private:
		void incremental();
		void sinWave();
	};

}
