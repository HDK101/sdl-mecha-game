#include "game.h";

void losTestes(CustomEvent *event) {
	printf("Hellow");
}

void gameStart(void) {
	playerInitialize();
	tilemapCreate(25, 25 , 32);

	CustomEvent *customEvent = eventsCreateCustom(4, losTestes);
	customEvent->event(customEvent);
}

void gameEvent(SDL_Event *event) {
	playerEvent(event);
}

void gameLoop(void) {
	playerLoop();
}
