#include "astar.h"

static AstarNode *nodes;
static int16_t nodesSize = 0;

static int16_t openNode;
static bool successfulUpdate = true;
static int16_t *openNodesQueue;
static int16_t openNodesQueueSize = 0;

static int16_t startX = 0;
static int16_t startY = 0;

static int16_t targetX = 0;
static int16_t targetY = 0;

static int16_t gridHeight = 0;
static int16_t gridWidth = 0;

static int16_t startIndex = 0;
static int16_t targetIndex = 0;

static double calculateDistance(int16_t fromX, int16_t fromY, int16_t toX, int16_t toY) {
	return sqrt(pow(toX - fromX, 2) + pow(toY - fromY, 2));
}

static bool validX(int16_t x) {
	return x >= 0 && x <= gridWidth;
}

static bool validY(int16_t y) {
	return y >= 0 && y <= gridWidth;
}

static bool validIndex(int16_t index) {
	return index >= 0 && index < nodesSize;
}

static AstarNode *getNodeInIndex(int16_t index) {
	if (validIndex(index)) {
		return &nodes[index];
	}
	return NULL;
}

static int getIndexByPosition(int16_t x, int16_t y) {
	if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
		return y * gridWidth + x;
	}
	return -1;
}

static AstarNode *getNodeInPosition(int16_t x, int16_t y) {
	if (y >= 0 && y < gridHeight && x >= 0 && x < gridWidth) {
		return &nodes[getIndexByPosition(x, y)];
	}
	return NULL;
}

static void addNodeToQueue(int16_t nodeIndex) {
	if (validIndex(nodeIndex)) {
		AstarNode *node = getNodeInIndex(nodeIndex);
		if (node != NULL && ((!node->closed && !node->obstacle) || (node->occupied && nodeIndex == targetIndex))) {
			openNodesQueue[openNodesQueueSize] = nodeIndex;
			openNodesQueueSize++;
			node->closed = true;
		}
	}
}

static void updateOpenNodes(void) {
	bool started = false;
	double f = 0.0;
	double h = 0.0;
	int16_t selectedNodeIndex = 0;

	if (openNodesQueueSize == 0) {
		return;
	}

	double fCalc = 0.0;
	double gCalc = 0.0;
	double hCalc = 0.0;
	AstarNode *node;

	for (int16_t i = 0; i < openNodesQueueSize; i++) {
		node = getNodeInIndex(openNodesQueue[i]);
		hCalc = calculateDistance(node->x, node->y, targetX - node->x, targetY - node->y);
		gCalc  = calculateDistance(node->x, node->y, startX - node->x, startY - node->y);
		fCalc = hCalc + gCalc;
		if (fCalc < f || !started || (fCalc == f && hCalc < h)) {
			started = true;
			f = fCalc;
			h = hCalc;
			selectedNodeIndex = i;
			openNode = openNodesQueue[i];
		}
	}

	openNodesQueue[selectedNodeIndex] = openNodesQueue[openNodesQueueSize - 1];
	openNodesQueue[openNodesQueueSize - 1] = -1;
	openNodesQueueSize--;
}

static void linkNode(int16_t target, int16_t node) {
	if (validIndex(target) && validIndex(node)) {
		AstarNode *targetNode = getNodeInIndex(target);
		if ((!targetNode->linked && !targetNode->obstacle) || (targetNode->occupied && target == targetIndex)) {
			targetNode->linked = true;
			targetNode->linkedNode = node;
		}
	}
}

static void processNode(int16_t nodeIndex) {
	getNodeInIndex(nodeIndex)->closed = true;

	linkNode(nodeIndex - gridWidth, nodeIndex);
	linkNode(nodeIndex - gridWidth - 1, nodeIndex);
	linkNode(nodeIndex - gridWidth + 1, nodeIndex);
	linkNode(nodeIndex + gridWidth, nodeIndex);
	linkNode(nodeIndex + gridWidth - 1, nodeIndex);
	linkNode(nodeIndex + gridWidth + 1, nodeIndex);
	linkNode(nodeIndex - 1, nodeIndex);
	linkNode(nodeIndex + 1, nodeIndex);
	
	addNodeToQueue(nodeIndex - gridWidth);
	addNodeToQueue(nodeIndex - gridWidth - 1);
	addNodeToQueue(nodeIndex - gridWidth + 1);
	addNodeToQueue(nodeIndex + 1);
	addNodeToQueue(nodeIndex + gridWidth);
	addNodeToQueue(nodeIndex + gridWidth - 1);
	addNodeToQueue(nodeIndex + gridWidth + 1);
	addNodeToQueue(nodeIndex - 1);
}

void astarCreateGrid(int16_t width, int16_t height) {
	nodes = malloc(sizeof(AstarNode) * width * height);
	
	gridWidth = width;
	gridHeight = height;

	nodesSize = width * height;

	astarClear();

	openNodesQueue = malloc(sizeof(int16_t) * width * height);

	openNodesQueueSize = 0;

	WRITE_LOG("Astar grid created\n");
}

Path* astarSearch(int16_t _startX, int16_t _startY, int16_t _targetX, int16_t _targetY) {
	astarClearGrid();

	startIndex = getIndexByPosition(_startX, _startY);
	targetIndex = getIndexByPosition(_targetX, _targetY);

	startX = _startX;
	startY = _startY;

	targetX = _targetX;
	targetY = _targetY;

	processNode(getIndexByPosition(_startX, _startY));

	bool found = false;
	while(!found || !successfulUpdate) {
		if (openNode == targetIndex) {
			found = true;
			WRITE_LOG("Node found\n");
		}
		else {
			processNode(openNode);
			updateOpenNodes();
		}
	}

	if (found) {
		AstarNode *node = NULL;
		int16_t nodeIndex = targetIndex;
		// We need to include the start node, therefore, start with 1
		int16_t positionsListSize = 1;

		do {
			node = getNodeInIndex(nodeIndex);
			nodeIndex = node->linkedNode;
			positionsListSize++;
			WRITE_LOG("Current %d\n", nodeIndex);
			WRITE_LOG("Start %d\n", startIndex);
		} while (nodeIndex != startIndex);

		Vector2 *positions = malloc(sizeof(Vector2) * positionsListSize);

		nodeIndex = targetIndex;
		int16_t positionsIteration= 0;
		do {
			node = getNodeInIndex(nodeIndex);
			nodeIndex = node->linkedNode;
			positions[positionsListSize - positionsIteration - 1].x = node->x;
			positions[positionsListSize - positionsIteration - 1].y = node->y;
			positionsIteration++;
		} while (nodeIndex != startIndex);
		//Start position
		positions[0].x = _startX;
		positions[0].y = _startY;

		Path *path = malloc(sizeof(Path));
		path->positions = positions;
		path->size = positionsListSize;
		return path;
	}
	return NULL;
}

void astarSetObstacle(int16_t x, int16_t y, bool isObstacle) {
	getNodeInPosition(x, y)->obstacle = isObstacle;
	WRITE_LOG("%d\n", isObstacle);
}

void astarSetOccupied(int16_t x, int16_t y, bool isOccupied) {
	getNodeInPosition(x, y)->occupied= isOccupied;
}

void astarClearGrid(void) {
	AstarNode *node = NULL;
	for (int16_t y = 0; y < gridHeight; y++) {
		for (int16_t x = 0; x < gridWidth; x++) {
			node = getNodeInPosition(x, y);
			node->closed = false;
			node->linked = false;
			node->linkedNode = -1;
		}
	}
}

void astarClear(void) {
	AstarNode *node = NULL;
	for (int16_t y = 0; y < gridHeight; y++) {
		for (int16_t x = 0; x < gridWidth; x++) {
			node = getNodeInPosition(x, y);
			node->x = x;
			node->y = y;
			node->closed = false;
			node->linked = false;
			node->obstacle = false;
			node->occupied = false;
			node->linkedNode = -1;
		}
	}
}

void astarSearchClear(void) {
	AstarNode *node = NULL;
	for (int16_t y = 0; y < gridHeight; y++) {
		for (int16_t x = 0; x < gridWidth; x++) {
			node = getNodeInPosition(x, y);
			node->closed = false;
			node->linked = false;
			node->linkedNode = -1;
		}
	}
}

void astarDestroyGrid(void) {
	free(nodes);
	free(openNodesQueue);
}

void astarDestroy(void) {
	astarDestroyGrid();
}
