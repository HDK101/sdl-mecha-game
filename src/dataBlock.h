#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <stdlib.h>

typedef union UnionDataBlock {
	int integerValue;
	double doubleValue;
	char charValue;
	char *stringValue;
} DataBlock;

DataBlock *dataBlockCreate(unsigned int listSize);
void dataBlockFree(DataBlock *dataBlock);

#endif
