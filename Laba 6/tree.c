#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "tree.h"

#pragma warning(disable:4996)

#define NotNull(ptr) notNull(ptr, __LINE__)
#define SafeMalloc(size) safeMalloc(size, __LINE__)

void* notNull(void* ptr, int line) {
	if (ptr == NULL) {
		printf("Null pointer at %i\n", line);
		exit(1);
	}
	return ptr;
}

void* safeMalloc(int size, int line) {
	return notNull(malloc(size), line);
}

Point* pointCreate(double x, double y, double z) {
	Point* point = SafeMalloc(sizeof(Point));
	point->x = x;
	point->y = y;
	point->z = z;
	return point;
}

void pointDestroy(Point* point) {
	free(point);
}

void pointPrint(Point* point) {
	printf("(%.1f; %.1f; %.1f)\n", point->x, point->y, point->z);
}

int pointEqual(Point* left, Point* right) {
	if (left->x == right->x && left->y == right->y && left->z == right->z) {
		return 1;
	}
	return 0;
}

Node* nodeCreate(Point* point, Point* bottom, Point* top, int depth) {
	Node* node = SafeMalloc(sizeof(Node));
	node->point = point;
	node->top = top;
	node->bottom = bottom;
	node->children = SafeMalloc(CHILDREN_COUNT * sizeof(Node*));
	for (int i = 0; i < CHILDREN_COUNT; i++) {
		node->children[i] = NULL;
	}
	node->isLeaf = 1;
	node->depth = depth;
	return node;
}

void nodeDestroy(Node* node) {
	if (node != NULL) {
		pointDestroy(node->top);
		pointDestroy(node->bottom);
		pointDestroy(node->point);
		for (int i = 0; i < CHILDREN_COUNT; i++) {
			if (node->children[i] != NULL) {
				nodeDestroy(node->children[i]);
			}
		}
	}
}

void nodePrint(Node* node, int octant) {
	if (node != NULL) {
		for (int i = 0; i < node->depth; i++) {
			printf("  ");
		}
		printf("In %i octant: ", octant);
		pointPrint(node->point);
		for (int i = 0; i < CHILDREN_COUNT; i++) {
			if (node->children[i] != NULL) {
				nodePrint(node->children[i], i + 1);
			}
		}
	}
}

int belongsToOctant(Node* node, Point* point) {
	int x = point->x >= (node->top->x + node->bottom->x) / 2;
	int y = point->y >= (node->top->y + node->bottom->y) / 2;
	int z = point->z >= (node->top->z + node->bottom->z) / 2;
	if (x && y && z) {
		return 1;
	}
	if (!x && y && z) {
		return 2;
	}
	if (!x && !y && z) {
		return 3;
	}
	if (x && !y && z) {
		return 4;
	}
	if (x && y && !z) {
		return 5;
	}
	if (!x && y && !z) {
		return 6;
	}
	if (!x && !y && !z) {
		return 7;
	}
	if (x && !y && !z) {
		return 8;
	}
}

Point* boundaryShift(Point* bottom, Point* top, int octant) {
	double x, y, z;
	if (octant == 1) {
		x = 0;
		y = 0;
		z = 0;
	}
	else if (octant == 2) {
		x = -(-bottom->x + top->x) / 2;
		y = 0;
		z = 0;
	}
	else if (octant == 3) {
		x = -(-bottom->x + top->x) / 2;
		y = -(-bottom->y + top->y) / 2;
		z = 0;
	}
	else if (octant == 4) {
		x = 0;
		y = -(-bottom->y + top->y) / 2;
		z = 0;
	}
	else if (octant == 5) {
		x = 0;
		y = 0;
		z = -(-bottom->z + top->z) / 2;
	}
	else if (octant == 6) {
		x = -(-bottom->x + top->x) / 2;
		y = 0;
		z = -(-bottom->z + top->z) / 2;
	}
	else if (octant == 7) {
		x = -(-bottom->x + top->x) / 2;
		y = -(-bottom->y + top->y) / 2;
		z = -(-bottom->z + top->z) / 2;
	}
	else if (octant == 8) {
		x = 0;
		y = -(-bottom->y + top->y) / 2;
		z = -(-bottom->z + top->z) / 2;
	}
	else {
		printf("Íåêîððåêòíîå çíà÷åíèå îêòàíòà\n");
		exit(1);
	}

	Point* pt = pointCreate(x, y, z);
	return pt;
}

Point* pointAdd(Point* left, Point* right) {
	return pointCreate(
		left->x + right->x,
		left->y + right->y,
		left->z + right->z
	);
}

Point** childBoundaries(Node* node, int octant) {
	Point* top = node->top;
	Point* bottom = pointCreate(
		(node->bottom->x + node->top->x) / 2,
		(node->bottom->y + node->top->y) / 2,
		(node->bottom->z + node->top->z) / 2
	);
	Point* shift = boundaryShift(node->bottom, node->top, octant);
	Point** boundaries = SafeMalloc(2 * sizeof(Point*));
	boundaries[0] = pointAdd(bottom, shift);
	boundaries[1] = pointAdd(top, shift);
	return boundaries;
}

void nodeAdd(Node* tree, Point* point) {
	int octant = belongsToOctant(tree, point);
	if (tree->isLeaf) {
		tree->isLeaf = 0;
		Point** boundaries = childBoundaries(tree, octant);
		tree->children[octant - 1] = nodeCreate(point, boundaries[0], boundaries[1], tree->depth + 1);
	}
	else {
		if (tree->children[octant - 1] == NULL) {
			Point** boundaries = childBoundaries(tree, octant);
			tree->children[octant - 1] = nodeCreate(point, boundaries[0], boundaries[1], tree->depth + 1);
		}
		else {
			nodeAdd(tree->children[octant - 1], point);
		}
	}
}

Node* nodeFind(Node* tree, Point* point) {
	if (pointEqual(tree->point, point)) {
		return tree;
	}
	int octant = belongsToOctant(tree, point);
	if (tree->children[octant - 1] == NULL) {
		return NULL;
	}
	return nodeFind(tree->children[octant - 1], point);
}

void nodeRemove(Node* tree, Point* point) {
	//Node* removed = nodeFind(tree, point);
	for (int i = 0; i < CHILDREN_COUNT; i++) {
		if (pointEqual(point, tree->children[i]->point)) {
			Node* remove = tree->children[i];
			tree->children[i] = NULL;
			nodeDestroy(remove);
			return;
		}
	}
	for (int i = 0; i < CHILDREN_COUNT; i++) {
		if (tree->children[i] != NULL) {
			nodeRemove(tree->children[i], point);
		}
	}
}