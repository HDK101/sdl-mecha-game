#include "sprites.h"

const unsigned int MAX_SPRITES = 5000;

typedef struct SpriteListNodeStruct {
	SDL_Texture *texture;
	char *file;
} Sprite;

static char *spritesPath = "assets/sprites/";

static Sprite *sprites;
unsigned int spritesCount = 0;

void spritesLazyStart() {
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
		printf("Could not cache sprites, max sprites count reached\n");
		return;
	}

	unsigned int index = hash(id) % MAX_SPRITES;
	printf("%i\n", index);

	spritesCount += 1;
	sprites[index].texture = texture;
	sprites[index].file = id;
}

void spritesDestroy() {
	for (int i = 0; i < MAX_SPRITES; i++) {
		if (sprites[i].texture != NULL) {
			SDL_DestroyTexture(sprites[i].texture);
		}
	}

	free(sprites);
}

SDL_Texture* spritesLoadTexture(char *filename, SDL_Renderer *renderer) {
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

	printf("%s\n", path);

	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL) {
		printf("Unable to load image. SDL Image Error: %s", IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture, SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	spritesAdd(newTexture, filename);

	free(path);

	return newTexture;
}
