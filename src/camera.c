#include "camera.h"

static Vector2 cameraPosition;

void cameraSetPosition(Vector2 position) {
	cameraPosition = position;
}

Vector2 cameraGetPosition(void) {
	return cameraPosition;
}
