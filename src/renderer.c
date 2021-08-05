#include "renderer.h"

static SDL_Renderer *renderer = NULL;

SDL_Renderer* rendererCreate(SDL_Window *window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return renderer;
}

SDL_Renderer* rendererGet() {
	return renderer;
}

void rendererDestroy() {
	SDL_DestroyRenderer(renderer);
}
