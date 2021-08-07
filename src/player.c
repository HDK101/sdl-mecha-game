#include "player.h"

static Player player;
static bool playerInitialized = false;
static SpriteNode *spriteNode = NULL;
static Vector2 positionCalcs;
static bool moveKeys[MOVE_KEYS_NUM];
static Keystate moveKeysOnce[MOVE_KEYS_NUM];


void playerInitialize(void) {
	player.entity = entityCreate(PLAYER, 10.0);
	playerInitialized = true;

	spriteNode = spritesCreateNode("bigchungus.png");
	spriteNode->position.x = 0;
	spriteNode->position.y = 0;
	spriteNode->size.x = 32;
	spriteNode->size.y = 32;

	moveKeysOnce[PLAYER_MOVE_UP] = IDLE;
	moveKeysOnce[PLAYER_MOVE_LEFT] = IDLE;
	moveKeysOnce[PLAYER_MOVE_RIGHT] = IDLE;
	moveKeysOnce[PLAYER_MOVE_DOWN] = IDLE;
}

void playerEvent(SDL_Event *event) {
	moveKeys[PLAYER_MOVE_UP] = false;
	moveKeys[PLAYER_MOVE_DOWN] = false;
	moveKeys[PLAYER_MOVE_LEFT] = false;
	moveKeys[PLAYER_MOVE_RIGHT] = false;

	if (event->type == SDL_KEYDOWN) {
		moveKeys[PLAYER_MOVE_UP] = event->key.keysym.sym == SDLK_UP;
		moveKeys[PLAYER_MOVE_DOWN] = event->key.keysym.sym == SDLK_DOWN;
		moveKeys[PLAYER_MOVE_LEFT] = event->key.keysym.sym == SDLK_LEFT;
		moveKeys[PLAYER_MOVE_RIGHT] = event->key.keysym.sym == SDLK_RIGHT;
		

		keysKeyPressOnce(event, SDLK_UP, &moveKeysOnce[PLAYER_MOVE_UP]);
		keysKeyPressOnce(event, SDLK_LEFT, &moveKeysOnce[PLAYER_MOVE_LEFT]);
		keysKeyPressOnce(event, SDLK_DOWN, &moveKeysOnce[PLAYER_MOVE_DOWN]);
		keysKeyPressOnce(event, SDLK_RIGHT, &moveKeysOnce[PLAYER_MOVE_RIGHT]);
	}
	keysKeyClear(event, SDLK_UP, &moveKeysOnce[PLAYER_MOVE_UP]);
	keysKeyClear(event, SDLK_LEFT, &moveKeysOnce[PLAYER_MOVE_LEFT]);
	keysKeyClear(event, SDLK_RIGHT, &moveKeysOnce[PLAYER_MOVE_RIGHT]);
	keysKeyClear(event, SDLK_DOWN, &moveKeysOnce[PLAYER_MOVE_DOWN]);
}

void playerLoop(void) {
	positionCalcs = player.entity->position;
	if (moveKeysOnce[PLAYER_MOVE_DOWN] == PRESS) {
		positionCalcs.y += 1;
	}
	if (moveKeysOnce[PLAYER_MOVE_UP] == PRESS) {
		positionCalcs.y -= 1;
	}
	if (moveKeysOnce[PLAYER_MOVE_LEFT] == PRESS) {
		positionCalcs.x -= 1;
	}
	if (moveKeysOnce[PLAYER_MOVE_RIGHT] == PRESS) {
		positionCalcs.x += 1;
	}

	Tile *tile = tilemapAccess(positionCalcs.x, positionCalcs.y);

	if (!tile->solid) {
		player.entity->position = positionCalcs;
		spriteNode->position = positionCalcs;
		spriteNode->position.x *= 32;
		spriteNode->position.y *= 32;
	}

	keysKeyWaitForRelease(&moveKeysOnce[PLAYER_MOVE_UP]);
	keysKeyWaitForRelease(&moveKeysOnce[PLAYER_MOVE_DOWN]);
	keysKeyWaitForRelease(&moveKeysOnce[PLAYER_MOVE_LEFT]);
	keysKeyWaitForRelease(&moveKeysOnce[PLAYER_MOVE_RIGHT]);
}
