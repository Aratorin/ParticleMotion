#include <iostream>
#include <SDL.h>
using namespace std;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL_Init failed!" << endl;
		return 1;
	}

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	SDL_Window* window = SDL_CreateWindow("Particle Motion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Quit;
		return 2;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		SDL_Quit;
		return 3;
	}

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (texture == NULL) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit;
		return 4;
	}

	Uint32* buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	memset(buffer, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

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

	//sets all pixels to green
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		buffer[i] = 0x00FF00FF;
	}

		//sets the 4 center pixels to red
		int x = (SCREEN_WIDTH / 2) - 1, y = (SCREEN_HEIGHT / 2) * SCREEN_WIDTH;
		buffer[x + y] = 0xFF0000FF;
		buffer[x + y + 1] = 0xFF0000FF;
		buffer[x + y + SCREEN_WIDTH] = 0xFF0000FF;
		buffer[x + y + 1 + SCREEN_WIDTH] = 0xFF0000FF;

	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	bool quit = false;

	SDL_Event event;

	while (!quit) {
		//Update particles
		//Draw particles
		//Check for messages/events

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	delete[] buffer;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
