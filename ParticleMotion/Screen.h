#pragma once
#include <iostream>
#include <SDL.h>
using namespace std;

namespace Aratorin {

	class Screen {
	public:
		static int SCREEN_WIDTH;
		static int SCREEN_HEIGHT;
		static double SCREEN_RATIO;

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		Uint32* buffer1;
		Uint32* buffer2;
		SDL_WindowFlags windowFlags;

	public:
		Screen();
		bool init(SDL_WindowFlags flags);
		void close();
		bool processEvents();
		void setPixel(Uint32 x, Uint32 y, Uint8 red, Uint8 green, Uint8 blue);
		void update();
		void clear();
		void boxBlur();
		~Screen();
	};

}
