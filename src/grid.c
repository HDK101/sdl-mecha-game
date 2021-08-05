#include "grid.h";

Grid* gridCreate(int height, int width) {
	Grid *grid = malloc(sizeof(Grid));
	grid->grid = malloc(height * width * sizeof(GRID_NODE));
	grid->width = width;
	grid->height = height;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			gridSet(j, i, (i + j) % 6, grid);
		}
	}

	return grid;
}

GRID_NODE gridAccess(int x, int y, Grid *grid) {
	return grid->grid[y * grid->width + x];
}

void gridSet(int x, int y, GRID_NODE value, Grid *grid) {
	grid->grid[y * grid->width + x] = value;
}

void gridDestroy(Grid *grid) {
	if (grid != NULL) {
		free(grid->grid);
		free(grid);
	}
}
