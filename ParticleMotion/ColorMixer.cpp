#include "ColorMixer.h"
namespace Aratorin {

	ColorMixer::ColorMixer(unsigned char& red, unsigned char& green, unsigned char& blue) :red(red), green(green), blue(blue), rpp(true), gpp(true), bpp(true) {};

	void ColorMixer::cycleColors(ColorMixerMode mode, int seed) {
		switch (mode) {
		case ColorMixerMode::INCREMENTAL:
			incremental();
			break;
		case ColorMixerMode::COSINWAVE:
			break;
		case ColorMixerMode::SINWAVE:
			sinWave(seed);
			break;
		default:
			break;
		}
	}

	void ColorMixer::incremental() {
		if (rpp) {
			int increment = 3 * rand() / RAND_MAX;
			if (red + increment >= 255) {
				red = 255;
				rpp = !rpp;
			} else {
				red += increment;
			}
		} else {
			int increment = 3 * rand() / RAND_MAX;
			if (red - increment <= 0) {
				red = 0;
				rpp = !rpp;
			} else {
				red -= increment;
			}
		}

		if (gpp) {
			int increment = 4 * rand() / RAND_MAX;
			if (green + increment >= 255) {
				green = 255;
				gpp = !gpp;
			} else {
				green += increment;
			}
		} else {
			int increment = 4 * rand() / RAND_MAX;
			if (green - increment <= 0) {
				green = 0;
				gpp = !gpp;
			} else {
				green -= increment;
			}
		}

		if (bpp) {
			int increment = 2 * rand() / RAND_MAX;
			if (blue + increment >= 255) {
				blue = 255;
				bpp = !bpp;
			} else {
				blue += increment;
			}
		} else {
			int increment = 2 * rand() / RAND_MAX;
			if (blue - increment <= 0) {
				blue = 0;
				bpp = !bpp;
			} else {
				blue -= increment;
			}
		}
	}

	void ColorMixer::sinWave(int seed) {
		red = (1 + sin(seed * 0.0002)) * 128;
		green = (1 + sin(seed * 0.0001)) * 128;
		blue = (1 + sin(seed * 0.0003)) * 128;
	}

}
