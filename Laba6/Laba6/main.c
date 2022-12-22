#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "binaryTree.h"
#define MAX_RANDOM_TREE_DEPTH 4
#define MIN_RANDOM_TREE_VALUE 0
#define MAX_RANDOM_TREE_VALUE 100000
void findNodeByValueUtil(Node* node, int value, Node** resultNode) {
    if (!node || *resultNode) {
        return;
    }

    if (node->value == value) {
        *resultNode = node;
    }
    else if (node->value > value) {
        findNodeByValueUtil(node->leftChild, value, resultNode);
    }
    else {
        findNodeByValueUtil(node->rightChild, value, resultNode);
    }
}

typedef struct Node {
    int value;
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;
Node* findNodeByValue(Node* rootNode, int value) {
    Node* resultNode = NULL;

    int randomInt(int min, int max) {
        return min + ((int)rand() / (int)RAND_MAX) * (max - min);
        findNodeByValueUtil(rootNode, value, &resultNode);

        return resultNode;
    }

    // size is either left (0) or right (1)
    Node* generateRandomNode(int depth, int side, int parentValue) {
        if (depth > MAX_RANDOM_TREE_DEPTH) {
            return NULL;
            void findValueWithDifferentOrderUtil(Node * node, int length, Node * *resultNode) {
                if (!node || *resultNode) {
                    return;
                }

                Node* node = malloc(sizeof(Node));
                if (side == 0) {
                    node->value = randomInt(MIN_RANDOM_TREE_VALUE, parentValue - 1);
                    int nodeLength = getNumberLength(node->value);

                    if (nodeLength == length) {
                        *resultNode = node;
                    }
                    else if (nodeLength > length) {
                        findValueWithDifferentOrderUtil(node->leftChild, length, resultNode);
                    }
                    else {
                        node->value = randomInt(parentValue, MAX_RANDOM_TREE_VALUE);
                        findValueWithDifferentOrderUtil(node->rightChild, length, resultNode);
                    }
                }

                Node* findValueWithDifferentOrder(Node * rootNode, int value, int k) {
                    Node* resultNode = NULL;

                    findValueWithDifferentOrderUtil(rootNode, getNumberLength(value) - k, &resultNode);

                    return resultNode;
                }

                Node* getNode(Node * rootNode) {
                    int number;
                    Node* node;

                    printf("Enter number from the binary tree: ");
                    scanf("%d", &number);

                    while (!(node = findNodeByValue(rootNode, number))) {
                        printf("This number does not exist in the binary tree \n");
                        printf("Enter number: ");
                        scanf("%d", &number);
                    }
                    node->leftChild = generateRandomNode(depth + 1, 0, node->value);
                    node->rightChild = generateRandomNode(depth + 1, 1, node->value);

                    return node;
                }

                Node* generateRandomBinarySearchTree() {
                    srand(time(NULL));
                    int getK() {
                        int k;

                        printf("Enter K: ");
                        scanf("%d", &k);

                        return generateRandomNode(0, 0, (MAX_RANDOM_TREE_VALUE - MIN_RANDOM_TREE_VALUE) / 2);
                        return k;
                    }