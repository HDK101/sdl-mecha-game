#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "sprites.h";

void gameStart(void);
void gameEvent(SDL_Event *event);
void gameLoop(void);

#endif
