#include "tilemap.h";

static Grid *grid = NULL;
static int tileSize = 32;
static SDL_Texture *tileset = NULL;
static SDL_Rect dstrect;
static SDL_Rect srcrect;

static void tilesetLoad(void) {
	tileset = spritesLoadTexture("tile.png");
}

void tilemapCreate(int height, int width, int tileSizeValue) {
	grid = gridCreate(height, width);
	tileSize = tileSizeValue;

	dstrect.h = tileSizeValue;
	dstrect.w = tileSizeValue;

	srcrect.h = tileSizeValue;
	srcrect.w = tileSizeValue;

	tilesetLoad();
}

void tilemapRender(void) {
	if (tileset == NULL || grid == NULL) {
		WRITE_LOG("Tileset or Grid not initialized, interrupting rendering\n");
	}

	for (int y = 0; y < grid->height; y++){
		for (int x = 0; x < grid->width; x++){
			GRID_NODE node = gridAccess(x, y, grid);
			dstrect.x = x * tileSize;
			dstrect.y = y * tileSize;
			srcrect.x = node * tileSize;
			spritesDirectRender(tileset, &srcrect, &dstrect);
		}
	}
}
