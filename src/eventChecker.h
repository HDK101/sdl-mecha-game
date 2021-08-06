#ifndef EVENT_CHECKER_H
#define EVENT_CHECKER_H

#include <stdlib.h>
#include "grid.h";
#include "hash.h";

#define MAX_CUSTOM_EVENTS 5000

typedef enum EnumCommonEvents {
	EVENT_SOLID,
	EVENT_DAMAGE,
} CommonEvents;

typedef struct StructCommonEventChecker {
	CommonEvents event;
	Grid *grid;
} CommonEventChecker;

typedef union UnionCustomEventData {
	int integerValue;
	double doubleValue;
	char charValue;
	char *stringValue;
} CustomEventData;

typedef struct StructCustomEvent CustomEvent;

struct StructCustomEvent {
	CustomEventData *data;
	char *name;
	void (*event)(CustomEvent*);
};

typedef struct StructCustomEventChecker {
	CustomEvent *customEvents;
} CustomEventChecker;

CustomEvent* eventsCreateCustom(char *name, int dataListSize, void (*event)(CustomEvent*));

void eventsClearAll(void);

#endif
