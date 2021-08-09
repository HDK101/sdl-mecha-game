#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "dataBlock.h"
#include "sprites.h"
#include "tilemap.h"

#define MAX_ENEMIES_SIZE 150

typedef struct StructEnemy Enemy;

struct StructEnemy {
	Entity *entity;
	void (*render)(Enemy*);
	void (*action)(Enemy*);
	DataBlock *data;
	SpriteNode *spriteNode;
};

Enemy* enemyCreate(void (*render)(Enemy*), void (*action)(Enemy*), unsigned int dataListSize, double maxHealth);
void enemyDestroy(void);
void enemySetPosition(Enemy *enemy, int x, int y);
void enemyMove(Enemy *enemy, int x, int y);

#endif
