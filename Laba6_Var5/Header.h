#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _tree {
	int val;
	struct _tree* left;
	struct _tree* right; //here's a dad!
	struct _tree* dad;
} tree;

void Add(tree** Tree);

//I decided to delete the deepest leaf
void Delete(tree** Tree);

//function of print can be recursive cause it don't relate to the task
void Print(tree* Tree);
