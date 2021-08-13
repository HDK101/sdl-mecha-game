#ifndef ASTAR_H
#define ASTAR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include "sourcePrint.h"
#include "vector2.h"

typedef struct StructAstarNode AstarNode;

struct StructAstarNode {
	int16_t linkedNode;
	bool linked;
	bool closed;
	bool obstacle;
	bool occupied;
	int16_t x;
	int16_t y;
};

typedef struct StructPath {
	Vector2 *positions;
	int size;
} Path;

void astarCreateGrid(int16_t width, int16_t height);
Path* astarSearch(int16_t startX, int16_t startY, int16_t targetX, int16_t targetY);
void astarSetObstacle(int16_t x, int16_t y, bool isObstacle);
void astarSetOccupied(int16_t x, int16_t y, bool isOccupied);
void astarClear(void);
void astarClearGrid(void);
void astarDestroy(void);

#endif
