#include "eventChecker.h"

static CustomEvent customEvents[MAX_CUSTOM_EVENTS];
static unsigned int customEventsLength = 0; 

CustomEvent* eventsCreateCustom(int dataListSize, void (*event)(CustomEvent*)) {
	CustomEvent *customEvent = &customEvents[customEventsLength];

	customEvent->data = dataBlockCreate(dataListSize);
	customEvent->event = event;

	return customEvent;
}

void eventsClearAll(void) {
	for (unsigned int i = 0; i < MAX_CUSTOM_EVENTS; i++) {
		CustomEvent *customEvent = &customEvents[i];
		dataBlockFree(customEvent->data);
		customEvents->event = NULL;
	}
}
