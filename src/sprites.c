#include "sprites.h"

#define MAX_SPRITES 5000

typedef struct SpriteListNodeStruct {
	SDL_Texture *texture;
	char *file;
} Sprite;

static char *spritesPath = "assets/sprites/";

static Sprite *sprites;
unsigned int spritesCount = 0;

static SpriteNode *spritesActive;
unsigned int spritesActiveCount = 0;

void spritesLazyStart(void) {
	if (spritesCount == 0) {
		sprites = malloc(sizeof(Sprite) * MAX_SPRITES);

		for (int i = 0; i < MAX_SPRITES; i++) {
			sprites[i].texture = NULL;
			sprites[i].file = NULL;
		}
	}
}

void spritesAdd(SDL_Texture *texture, char *id) {
	if (spritesCount >= MAX_SPRITES) {
		WRITE_LOG("Could not cache sprites, max sprites count reached\n");
		return;
	}

	unsigned int index = hash(id) % MAX_SPRITES;

	spritesCount += 1;
	sprites[index].texture = texture;
	sprites[index].file = id;
}

void spritesDestroy(void) {
	if (spritesCount == 0) return;

	for (int i = 0; i < MAX_SPRITES; i++) {
		if (sprites[i].texture != NULL) {
			SDL_DestroyTexture(sprites[i].texture);
		}
	}

	free(sprites);
}

SDL_Texture* spritesLoadTexture(char *filename) {
	spritesLazyStart();
	
	unsigned int index = hash(filename) % MAX_SPRITES;

	if (sprites[index].file != NULL && strcmp(sprites[index].file, filename) == 0) {
		return sprites[index].texture;
	}

	int filenameSize = strlen(filename);
	int spritesPathSize = strlen(spritesPath);
	int pathSize = filenameSize + spritesPathSize;
	char *path = malloc(sizeof(char) * (pathSize + 1));

	memset(path, '\0', pathSize);

	strncat(path, spritesPath, strlen(spritesPath));
	strncat(path, filename, strlen(filename));

	WRITE_LOG("Path to load: %s\n", path);

	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL) {
		WRITE_LOG("Unable to load image. SDL Image Error: %s", IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(rendererGet(), loadedSurface);
		if (newTexture == NULL) {
			WRITE_LOG("Unable to create texture, SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	spritesAdd(newTexture, filename);

	free(path);

	return newTexture;
}

void spritesRender(void) {
	SDL_Renderer *renderer = rendererGet();

	SDL_RenderClear(renderer);

	SDL_Rect rect;
	for (unsigned int i = 0; i < spritesActiveCount; i++) {
		SpriteNode *currentSpriteNode = &spritesActive[i];
		if (!currentSpriteNode->visible) continue;
		rect.x = currentSpriteNode->position.x;
		rect.y = currentSpriteNode->position.y;
		rect.w = currentSpriteNode->size.x;
		rect.h = currentSpriteNode->size.y;
		SDL_RenderCopyEx(renderer, currentSpriteNode->texture, NULL, &rect, currentSpriteNode->angle, NULL, SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

SpriteNode* spritesCreateNode(char *textureName) {
	if (spritesActiveCount == 0) {
		spritesActive = malloc(sizeof(SpriteNode));
	}
	else {
		spritesActive = realloc(spritesActive, sizeof(SpriteNode) * (spritesActiveCount + 1));
	}

	SpriteNode *spriteNode = &spritesActive[spritesActiveCount];
	spriteNode->position.x = 0;
	spriteNode->position.y = 0;
	spriteNode->size.x = 0;
	spriteNode->size.y = 0;
	spriteNode->texture = spritesLoadTexture(textureName);
	spriteNode->flip = false;
	spriteNode->visible = true;
	spriteNode->queueToDestroy = false;
	spriteNode->angle = 0;
	
	spritesActiveCount++;

	return spriteNode;
}

void spritesActiveDestroy(void) {
	free(spritesActive);
}
