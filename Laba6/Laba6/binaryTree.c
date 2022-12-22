#include <stdlib.h>

#define MAX_RANDOM_TREE_DEPTH 4
#define MIN_RANDOM_TREE_VALUE 0
#define MAX_RANDOM_TREE_VALUE 100000
#define DEPTH_SPACE_COUNT 10

typedef struct Node {
    int value;
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

int randomInt(int min, int max) {
    return min + ((double)rand() / (double)RAND_MAX) * (max - min + 1);
}

// size is either left (0) or right (1)
Node* generateRandomNode(int depth, int minValue, int maxValue) {
    if (depth > MAX_RANDOM_TREE_DEPTH) {
        return NULL;
    }

    Node* node = malloc(sizeof(Node));
    node->value = randomInt(minValue, maxValue);

    node->leftChild = generateRandomNode(depth + 1, minValue, node->value - 1);
    node->rightChild = generateRandomNode(depth + 1, node->value, maxValue);

    return node;
}

Node* generateRandomBinarySearchTree() {
    srand(time(NULL));

    return generateRandomNode(0, MIN_RANDOM_TREE_VALUE, MAX_RANDOM_TREE_VALUE);
}

void printBinaryTreeUtil(Node* root, int space) {
    if (root == NULL) {
        return;
    }

    space += DEPTH_SPACE_COUNT;

    printBinaryTreeUtil(root->rightChild, space);

    printf("\n");
    for (int i = DEPTH_SPACE_COUNT; i < space; i += 1) {
        printf(" ");
    }

    printf("%d\n", root->value);

    printBinaryTreeUtil(root->leftChild, space);
}

void printBinaryTree(Node* root) {
    printBinaryTreeUtil(root, 0);
}

int getNumberLength(int number) {
    if (number == 0)
        return 1;
    return log10(abs(number)) + 1;
}