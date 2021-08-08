#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "sprites.h";
#include "hash.h";
#include "renderer.h";
#include "game.h";
#include "tilemap.h";
#include "eventChecker.h";
#include "player.h";

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window *window = NULL;

SDL_Surface *screenSurface = NULL;

static SDL_Renderer *renderer = NULL;

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
			renderer = rendererCreate(window);
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
	rendererDestroy();

	spritesDestroy();
	spritesActiveDestroy();

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

		SpriteNode *spriteNode = spritesCreateNode("bigchungus.png");
		spriteNode->position.x = 20;
		spriteNode->size.x = 20;
		spriteNode->size.y = 20;
		spriteNode->angle = 20;

		gameStart();

		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				gameEvent(&e);

				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}

			gameLoop();

			spritesClearRender();
			tilemapRender();
			spritesRender();
			spritesDirectDrawUpdate();
			
			SDL_Delay(16);
		}
	}

	terminate();

	return 0;
}
