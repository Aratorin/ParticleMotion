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
		Uint32* buffer;
		SDL_Event event;

	public:
		Screen();
		bool init();
		void close();
		bool processEvents();
		~Screen();
	};

}
