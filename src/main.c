#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "sprites.h";
#include "hash.h";

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window *window = NULL;

SDL_Surface *screenSurface = NULL;

SDL_Renderer *renderer = NULL;

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Failed to create renderer, SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags =  IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					success = false;
					printf("Could not initialize PNG module. PNG Error: %s\n", IMG_GetError());
				}
				else {
					screenSurface = SDL_GetWindowSurface(window);
				}
			}
		}
	}
	return success;
}

void terminate() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	spritesDestroy();

	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {
	if(!init()) {
		printf("Failed to initialize\n");    
	}
	else {
		bool quit = false;
		SDL_Event e;

		SDL_Texture *texture = spritesLoadTexture("preview.png", renderer);
		SDL_Texture *bigchungus = spritesLoadTexture("bigchungus.png", renderer);
		SDL_Rect rect;

		rect.x = 32;
		rect.y = 32;
		rect.h = 256;
		rect.w = 256;


		while (!quit) {
			double timeElapsed = (SDL_GetTicks()) / 1000.0;

			SDL_RenderClear(renderer);

			SDL_RenderCopyEx(renderer, texture, NULL, &rect, 50, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, bigchungus, NULL, &rect, 50, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(renderer);

			//printf("Ticks: %d\n", SDL_GetTicks());
			SDL_Delay(16);

			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN) {
					printf("KeyCode: %d\n", e.key.keysym.sym);
				}
			}
		}

		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	terminate();

	return 0;
}
