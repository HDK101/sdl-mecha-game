#include "enemy.h"

static Enemy enemies[MAX_ENEMIES_SIZE];
static unsigned int enemiesLength = 0; 

Enemy* enemyCreate(void (*render)(Enemy*), void (*action)(Enemy*), unsigned int dataListSize,double maxHealth) {
	Enemy *enemy = &enemies[enemiesLength];

	enemy->entity = entityCreate(ENEMY, maxHealth);
	enemy->data = dataBlockCreate(dataListSize);

	enemy->render = render;
	enemy->action = action;
	
	enemy->spriteNode = spritesCreateNode("bigchungus.png");
	enemy->spriteNode->size.x = 32;
	enemy->spriteNode->size.y = 32;
	
	enemiesLength++;
	return enemy;
}

void enemyDestroy(void) {
	for (unsigned int i = 0; i < MAX_ENEMIES_SIZE; i++) {
		Enemy *enemy = &enemies[i];
		if (enemy->data != NULL) {
			dataBlockFree(enemy->data);
		}
	}
}

void enemySetPosition(Enemy *enemy, int x, int y) {
	enemy->spriteNode->position.x = x * 32;
	enemy->spriteNode->position.y = y * 32;
	enemy->entity->position.x = x;
	enemy->entity->position.y = y;
}

void enemyMove(Enemy *enemy, int x, int y) {
	Tile *tile = tilemapAccess(enemy->entity->position.x, enemy->entity->position.y);
	tile->occupied = false;
	enemySetPosition(enemy, x, y);
	tile = tilemapAccess(x, y);
	tile->occupied = true;
}
