#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include "vector2.h"

#define MAX_ENTITIES_SIZE 200

typedef enum EnumEntityType {
	PLAYER,
	ENEMY
} EntityType;

typedef struct StructEntity {
	Vector2 position;
	double health;
	double maxHealth;
	EntityType type;
	bool initialized;
} Entity;

Entity* entityCreate(EntityType type, double maxHealth);
Entity* entityFindInPosition(Vector2 position);

#endif
