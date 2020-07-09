#pragma once
#include <iostream>
#include <SDL.h>
using namespace std;

namespace Aratorin {

	class Screen {
	public:
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		Uint32* buffer1;
		Uint32* buffer2;

	public:
		Screen();
		bool init();
		void close();
		bool processEvents();
		void setPixel(Uint32 x, Uint32 y, Uint8 red, Uint8 green, Uint8 blue);
		void update();
		void clear();
		void boxBlur();
		~Screen();
	};

}
