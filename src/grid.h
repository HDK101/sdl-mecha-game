#ifndef GRID_H
#define GRID_H

#include <stdlib.h>

#define GRID int*
#define GRID_NODE int

void gridCreate(int height, int width);
GRID_NODE gridAccess(int x, int y);
void gridSet(int x, int y, GRID_NODE value);
void gridDestroy(void);

#endif
