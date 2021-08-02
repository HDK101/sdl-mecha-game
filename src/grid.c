#include "grid.h";

static GRID grid;
static int gridWidth;
static int gridHeight;

void gridCreate(int height, int width) {
	grid = malloc(height * width * sizeof(GRID_NODE));
	gridWidth = width;
	gridHeight = height;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			grid[i * width + j] = 0;
		}
	}
}

GRID_NODE gridAccess(int x, int y) {
	return grid[y * gridWidth + x];
}

void gridSet(int x, int y, GRID_NODE value) {
	grid[y * gridWidth + x] = value;
}

void gridDestroy(void) {
	if (grid != NULL) {
		free(grid);
	}
}
