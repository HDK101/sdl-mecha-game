#ifndef KEYS_H
#define KEYS_H

#include <SDL2/SDL.h>
#include "sourcePrint.h"

typedef enum EnumKeystate {
	IDLE,
	PRESS,
	WAITING_FOR_RELEASE,
} Keystate;

void keysKeyPressOnce(SDL_Event *event, SDL_Keycode keycode, Keystate *key);
void keysKeyWaitForRelease(Keystate *key);
void keysKeyClear(SDL_Event *event, SDL_Keycode keycode, Keystate *key);

#endif

