#include "keys.h";

void keysKeyPressOnce(SDL_Event *event, SDL_Keycode keycode, Keystate *key) {
	if (event->key.keysym.sym == keycode && *key == IDLE) {
		(*key) = PRESS;
	}
}

void keysKeyWaitForRelease(Keystate *key) {
	if (*key == PRESS) {
		(*key) = WAITING_FOR_RELEASE;
	}
}

void keysKeyClear(SDL_Event *event, SDL_Keycode keycode, Keystate *key) {
	if (event->type == SDL_KEYUP && event->key.keysym.sym == keycode) {
		(*key) = IDLE;
	}
}
