#include "entity.h";

static Entity entities[MAX_ENTITIES_SIZE];
static unsigned int entitiesLength = 0;

Entity* entityCreate(EntityType type, double maxHealth) {
	if (entitiesLength == 0) {
		for (int i = 0; i < entitiesLength; i++) {
			entities[i].initialized = false;
		}
	}

	Entity *entity = &entities[entitiesLength];
	entity->type = type;
	entity->health = maxHealth;
	entity->maxHealth = maxHealth;
	entity->position.x = 0;
	entity->position.y = 0;
	entity->initialized = true;

	entitiesLength++;
	return entity;
}

Entity* entityFindInPosition(Vector2 position) {
	
}
