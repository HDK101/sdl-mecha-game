#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdbool.h>
#include "grid.h"
#include "sprites.h"
#include "sourcePrint.h"
#include "eventChecker.h"
#include "astar.h"

typedef struct StructTile {
	GRID_NODE node;
	bool solid;
	bool occupied;
	bool damage;
	double damageToCause;
	unsigned int eventId;
} Tile;

typedef struct StructTilemap {
	Tile *tiles;
	int width;
	int height;
} Tilemap;

void tilemapCreate(int height, int width, int tileSizeValue);
Tile* tilemapAccess(int x, int y);
void tilemapSet(int x, int y, GRID_NODE value);
void tilemapSetSolid(int x, int y, bool isSolid);
void tilemapSetOccupied(int x, int y, bool isOccupied);
void tilemapRender(void);

#endif
