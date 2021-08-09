#include "dataBlock.h";

DataBlock *dataBlockCreate(unsigned int listSize) {
	return malloc(sizeof(DataBlock) * listSize);
}

void dataBlockFree(DataBlock *dataBlock) {
	if (dataBlock != NULL) {
		free(dataBlock);
	}
}
