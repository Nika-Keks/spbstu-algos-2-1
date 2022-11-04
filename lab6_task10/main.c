#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_RANDOM_TREE_DEPTH 4
#define MIN_RANDOM_TREE_VALUE 0
#define MAX_RANDOM_TREE_VALUE 100000

typedef struct Node {
  int value;
  struct Node* parent;
  struct Node* leftChild;
  struct Node* rightChild;
} Node;

int random(int min, int max) {
  return min + ((int)rand() / (int)RAND_MAX) * (max - min);
}

// size is either left (0) or right (1)
Node* generateRandomNode(int depth, int side, int parentValue) {
  if (depth > MAX_RANDOM_TREE_DEPTH) {
    return NULL;
  }

  Node* node = malloc(sizeof(Node));
  if (side == 0) {
    node->value = random(MIN_RANDOM_TREE_VALUE, parentValue - 1);
  } else {
    node->value = random(parentValue, MAX_RANDOM_TREE_VALUE);
  }
  node->leftChild = generateRandomNode(depth + 1, 0, node->value);
  node->rightChild = generateRandomNode(depth + 1, 1, node->value);

  return node;
}

Node* generateRandomBinarySearchTree() {
  srand(time(NULL));

  return generateRandomNode(0, 0, (MAX_RANDOM_TREE_VALUE - MIN_RANDOM_TREE_VALUE) / 2);
}
