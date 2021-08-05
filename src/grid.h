#ifndef GRID_H
#define GRID_H

#include <stdlib.h>

#define GRID_NODES int*
#define GRID_NODE int

typedef struct StructGrid {
	GRID_NODES grid;
	int width;
	int height;
} Grid;


Grid* gridCreate(int height, int width);
GRID_NODE gridAccess(int x, int y, Grid *grid);
void gridSet(int x, int y, GRID_NODE value, Grid *grid);
void gridDestroy(Grid *grid);

#endif
