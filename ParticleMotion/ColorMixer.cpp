#include "ColorMixer.h"
namespace Aratorin {

	ColorMixer::ColorMixer(unsigned char& red, unsigned char& green, unsigned char& blue, const int mode, int seed) :red(red), green(green), blue(blue), mode(mode), rpp(true), gpp(true), bpp(true), seed(seed) {};

	void ColorMixer::cycleColors() {
		switch (mode) {
		case 0:
			sinWave();
			break;
		case 1:
			incremental();
			break;
		default:
			break;
		}
	}

	void ColorMixer::incremental() {
		if (rpp) {
			red++;
			if (red == 255) { rpp = !rpp; }
		} else {
			red--;
			if (red == 0) { rpp = !rpp; }
		}

		if (gpp) {
			green++;
			if (green == 255) { gpp = !gpp; }
		} else {
			green--;
			if (green == 0) { gpp = !gpp; }
		}

		if (bpp) {
			blue++;
			if (blue == 255) { bpp = !bpp; }
		} else {
			blue--;
			if (blue == 0) { bpp = !bpp; }
		}
	}

	void ColorMixer::sinWave() {
		red = (1 + sin(seed * 0.0002)) * 128;
		green = (1 + sin(seed * 0.0001)) * 128;
		blue = (1 + sin(seed * 0.0003)) * 128;
	}

}
