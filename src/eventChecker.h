#ifndef EVENT_CHECKER_H
#define EVENT_CHECKER_H

#include <stdlib.h>
#include "grid.h";
#include "hash.h";

#define MAX_CUSTOM_EVENTS 300

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

CustomEvent* eventsCreateCustom(int dataListSize, void (*event)(CustomEvent*));

void eventsClearAll(void);

#endif
