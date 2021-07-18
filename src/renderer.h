#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

SDL_Renderer* rendererCreate(SDL_Window *window);
SDL_Renderer* rendererGet();
void rendererDestroy();

#endif
