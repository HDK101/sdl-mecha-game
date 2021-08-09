#include "game.h";

void losTestes(CustomEvent *event) {
	printf("Hellow\n");
}

void renderEnemy(Enemy *enemy) {
	WRITE_LOG("RENDER!\n");
}

void gameStart(void) {
	playerInitialize();
	tilemapCreate(25, 25 , 32);

	CustomEvent *customEvent = eventsCreateCustom(4, losTestes);
	customEvent->event(customEvent);

	Enemy *enemy = enemyCreate(renderEnemy, renderEnemy, 4, 10.0);
	Enemy *enemyTwo = enemyCreate(renderEnemy, renderEnemy, 4, 10.0);
	Enemy *enemyThree = enemyCreate(renderEnemy, renderEnemy, 4, 10.0);

	enemyMove(enemy, 5, 5);
	enemyMove(enemyTwo, 6, 5);
	enemyMove(enemyThree, 5, 4);
}

void gameEvent(SDL_Event *event) {
	playerEvent(event);
}

void gameLoop(void) {
	playerLoop();
}

void gameDestroy(void) {
	eventsClearAll();
	enemyDestroy();
}
