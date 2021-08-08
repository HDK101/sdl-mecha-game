#include "tilemap.h";

static Tilemap tilemap;
static int tileSize = 32;
static SDL_Texture *tileset = NULL;
static SDL_Rect dstrect;
static SDL_Rect srcrect;

static void tilesetLoad(void) {
	tileset = spritesLoadTexture("tile.png");
}

void tilemapCreate(int height, int width, int tileSizeValue) {
	if (tilemap.tiles != NULL) {
		free(tilemap.tiles);
	}

	tilemap.tiles = malloc(sizeof(Tile) * height * width);
	tilemap.width = width;
	tilemap.height = height;

	for (int y = 0; y < tilemap.height; y++){
		for (int x = 0; x < tilemap.width; x++){
			tilemapSet(x, y, x * y % 6);
			Tile *tile = tilemapAccess(x, y);
			tile->solid = (x * y % 6) > 4;
			tile->occupied = false;
		}
	}

	tileSize = tileSizeValue;

	dstrect.h = tileSizeValue;
	dstrect.w = tileSizeValue;

	srcrect.h = tileSizeValue;
	srcrect.w = tileSizeValue;

	tilesetLoad();
}

Tile* tilemapAccess(int x, int y) {
	if (tilemap.tiles != NULL) {
		return &tilemap.tiles[y * tilemap.width + x];
	}
	return NULL;
};

void tilemapSet(int x, int y, GRID_NODE value) {
	Tile *tile = tilemapAccess(x, y);
	tile->node = value;
}

void tilemapRender(void) {
	if (tileset == NULL || tilemap.tiles == NULL) {
		WRITE_LOG("Tileset or tiles not initialized, interrupting rendering\n");
	}

	for (int y = 0; y < tilemap.height; y++){
		for (int x = 0; x < tilemap.width; x++){
			Tile *tile = tilemapAccess(x, y);
			dstrect.x = x * tileSize;
			dstrect.y = y * tileSize;
			srcrect.x = tile->node * tileSize;
			spritesDirectRender(tileset, &srcrect, &dstrect);
		}
	}
}
