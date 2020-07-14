#include "Screen.h"

namespace Aratorin {

	Screen::Screen() :window(NULL), renderer(NULL), texture(NULL), buffer1(NULL), buffer2(NULL) {}

	int Screen::SCREEN_WIDTH = 800;
	int Screen::SCREEN_HEIGHT = 600;

	bool Screen::init(SDL_WindowFlags flags) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}

		/*HD Mode*/
		//SDL_DisplayMode md;
		//SDL_GetDesktopDisplayMode(0, &md);
		//SCREEN_WIDTH = md.w;
		//SCREEN_HEIGHT = md.h;
		//window = SDL_CreateWindow("Particle Motion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5, flags);

		/*Original Mode*/
		window = SDL_CreateWindow("Particle Motion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

		if (window == NULL) {
			SDL_Quit();
			return false;
		}

		//SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
		cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << endl;
		cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << endl;

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

		if (renderer == NULL) {
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}

		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (texture == NULL) {
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}

		/*
			Each row has SCREEN_WIDTH - 1 pixels and there are SCREEN_HEIGHT rows
			So the x position of a given pixel is between 0 and SCREEN_WIDTH-1(because arrays run 0 to length - 1)
			The y position of a given pixel is SCREEN_WIDTH * Desired y position because each row contains SCREEN_WIDTH - 1 pixels
			To set the x,y of the pixel you are editing, you add the x and y coordinates together to get the pixel you are setting
			A screen with an even number of pixels has no center pixel, so the "center" of the screen is the 4 pixel square:
			((SCREEN_WIDTH / 2) - 1) + ((SCREEN_HEIGHT / 2) * SCREEN_WIDTH) //top left
			(SCREEN_WIDTH / 2) + ((SCREEN_HEIGHT / 2) * SCREEN_WIDTH) //top right
			((SCREEN_WIDTH / 2) - 1) + ((SCREEN_HEIGHT / 2) * SCREEN_WIDTH) + SCREEN_WIDTH //bottom left
			(SCREEN_WIDTH / 2) + ((SCREEN_HEIGHT / 2) * SCREEN_WIDTH) + SCREEN_WIDTH //bottom right
		*/
		buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		//sets all bytes in buffer to 0, making the screen black
		//memset(buffer, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		clear();

		return true;
	}

	void Screen::close() {
		delete[] buffer1;
		delete[] buffer2;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_Event event;
	bool Screen::processEvents() {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	void Screen::setPixel(Uint32 x, Uint32 y, Uint8 red, Uint8 green, Uint8 blue) {
		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
			return;
		}

		Uint32 color = red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;
		buffer1[x + (y * SCREEN_WIDTH)] = color;
	}

	void Screen::update() {
		SDL_UpdateTexture(texture, NULL, buffer1, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	void Screen::clear() {
		//sets all bytes in buffer to 0, making the screen black
		memset(buffer1, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		memset(buffer2, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	}

	void Screen::boxBlur() {
		swap(buffer1, buffer2);

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						if (currentX < 0 || currentX >= SCREEN_WIDTH || currentY < 0 || currentY >= SCREEN_HEIGHT) {
							continue;
						}

						Uint32 color = buffer2[currentX + (currentY * SCREEN_WIDTH)];
						Uint32 red = color >> 24;
						Uint32 green = (color & 0x00FF0000) >> 16;
						Uint32 blue = (color & 0x0000FF00) >> 8;
						redTotal += red;
						greenTotal += green;
						blueTotal += blue;

					}
				}

				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}

		}
	}

	Screen::~Screen() {}

}
