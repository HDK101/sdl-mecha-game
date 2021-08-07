#include "player.h"

static Player player;
static bool playerInitialized = false;
static SpriteNode *spriteNode;

void playerInitialize(void) {
	player.position.x = 0;
	player.position.y = 0;
	player.health = 10;
	player.maxHealth = 10;
	playerInitialized = true;

	spriteNode = spritesCreateNode("bigchungus.png");
	spriteNode->position.x = 0;
	spriteNode->position.y = 0;
	spriteNode->size.x = 32;
	spriteNode->size.y = 32;
}

void playerEvent(SDL_Event *event) {
	if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_DOWN) {
			player.position.y += 1;
		}
		if (event->key.keysym.sym == SDLK_UP) {
			player.position.y -= 1;
		}
		if (event->key.keysym.sym == SDLK_LEFT) {
			player.position.x -= 1;
		}
		if (event->key.keysym.sym == SDLK_RIGHT) {
			player.position.x += 1;
		}
	}

	spriteNode->position = player.position;
	spriteNode->position.x *= 32;
	spriteNode->position.y *= 32;
}
