#include "game.h";

static SpriteNode *spriteNode = NULL;

void gameStart() {
	spriteNode = spritesCreateNode("bigchungus.png");
	spriteNode->position.x = 0;
	spriteNode->position.y = 0;
	spriteNode->size.x = 32;
	spriteNode->size.y = 32;

	tilemapCreate(25, 25 , 32);
}

void gameEvent(SDL_Event *event) {
	if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_DOWN) {
			spriteNode->position.y += 32;
		}
		if (event->key.keysym.sym == SDLK_UP) {
			spriteNode->position.y -= 32;
		}
		if (event->key.keysym.sym == SDLK_LEFT) {
			spriteNode->position.x -= 32;
		}
		if (event->key.keysym.sym == SDLK_RIGHT) {
			spriteNode->position.x += 32;
		}
	}
}

void gameLoop(void) {
}
