#include "game.h";

static SpriteNode *spriteNode = NULL;

void gameStart() {
	spriteNode = spritesCreateNode("bigchungus.png");
	spriteNode->position.x = 10;
	spriteNode->position.y = 10;
	spriteNode->size.x = 10;
	spriteNode->size.y = 10;
}

void gameEvent(SDL_Event *event) {
	if (event->type == SDL_KEYDOWN) {
	}
}

void gameLoop(void) {
	spriteNode->visible = !spriteNode->visible;
}
