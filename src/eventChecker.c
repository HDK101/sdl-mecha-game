#include "eventChecker.h";

static CustomEvent customEvents[MAX_CUSTOM_EVENTS];

CustomEvent* eventsCreateCustom(char *name, int dataListSize, void (*event)(CustomEvent*)) {
	unsigned long hashIndex = hash(name) % MAX_CUSTOM_EVENTS;

	printf("%lu", hashIndex);

	CustomEvent *customEvent = &customEvents[hashIndex];

	customEvent->data = malloc(sizeof(CustomEventData) * dataListSize);
	customEvent->event = event;

	return customEvent;
}

void eventsClearAll(void) {
	for (unsigned long i = 0; i < MAX_CUSTOM_EVENTS; i++) {
		free(customEvents[i].data);
	}
}
