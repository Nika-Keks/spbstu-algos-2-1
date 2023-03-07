#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

#pragma warning(disable:4996)

int main() {

	int side = 4;
	printf("Partitioning space into 8 parts centred at (0; 0; 0), side is equal to %i\n", 2 * side);
	printf("Side is equal to 2^n so that it is easier to imagine the partitioned space.\n");
	printf("Example nodes are generated randomly.\n");
	time_t t;
	srand((unsigned)time(&t));
	Point* bottom = pointCreate(-side, -side, -side);
	Point* top = pointCreate(side, side, side);
	Node* node = nodeCreate(
		pointCreate(1, 2, 0),
		bottom,
		top,
		1
	);
	for (int i = 0; i < CHILDREN_COUNT * 3; i++) {
		double x = ((double)(rand() % 80) - 40) / 10;
		double y = ((double)(rand() % 80) - 40) / 10;
		double z = ((double)(rand() % 80) - 40) / 10;
		Point* point = pointCreate(x, y, z);
		nodeAdd(node, point);
	}
	double x, y, z;
	nodePrint(node, 0);
	printf("Point to find: ");
	scanf("%lf %lf %lf", &x, &y, &z);
	Point* pt = pointCreate(x, y, z);
	Node* found = nodeFind(node, pt);
	printf("Found node: \n");
	nodePrint(found, 0);
	printf("Point to add: ");
	scanf("%lf %lf %lf", &x, &y, &z);
	nodeAdd(
		node,
		pointCreate(x, y, z)
	);
	printf("New tree: \n");
	nodePrint(node, 0);
	printf("Attention: removing a non-existing node will crash your program.\n");
	printf("Point to remove: ");
	scanf("%lf %lf %lf", &x, &y, &z);
	nodeRemove(
		node,
		pointCreate(x, y, z)
	);
	printf("New tree: \n");
	if (node->children[1] != NULL) printf("Not NULL\n");
	nodePrint(node, 0);
	return 0;
}