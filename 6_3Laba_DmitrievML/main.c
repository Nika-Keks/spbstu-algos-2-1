#include <stdio.h>
#include <stdlib.h>
/**
 * Структура узла дерева
 * @param key - значение в узле
 * @param left - указатель на левую ветку
 * @param right - указатель на правую ветку
 */
typedef struct tree {
    int key;
    struct tree *left;
    struct tree *right;
} Node;
/**
 * Функция создания корня
 * (в корень изначально я положил 1)
 * @return - ссылка на корень
 */
Node *create() {
    Node *tmp = malloc(sizeof(Node));
    Node *tmp2 = malloc(sizeof(Node));
    Node *tmp3 = malloc(sizeof(Node));

    tmp->left = tmp2;
    tmp->right = tmp3;

    tmp->left->key = 0;
    tmp->right->key = 0;

    tmp->left->left = NULL;
    tmp->left->right = NULL;

    tmp->right->left = NULL;
    tmp->right->right = NULL;
    tmp->key = 1;
    return tmp;
}
/**
 * Добывление нового элемента в поддерево с меньшим чилом узлов
 * @param root - ссылка на корень
 * @param flag - флаг для выхода из рекурсии после добавление элемента
 */
void New(Node *root, int *flag) {
    root->key++;
    if (root->left->key <= root->right->key) {
        if (root->left->left != NULL) {
            New(root->left, flag);
            if (*flag == 1) {
                return;
            }
        } else {
            root->left = create();
            *flag = 1;
        }
    } else {
        if (root->right->left != NULL) {
            New(root->right, flag);
            if (*flag == 1) {
                return;
            }
        } else {
            root->right = create();
            *flag = 1;
        }
    }
}
/**
 * Увеличение количества узлов в дереве на заданное число
 * @param node - ссылка на корень
 * @param positive_delta - заданное число увеличения
 * @return - увеличенное дерево
 */
Node *Add(Node *node, int positive_delta) {
    int flag = 0;
    for (int i = 0; i < positive_delta; i++) {
        New(node, &flag);
        flag = 0;
    }
    return node;
}
/**
 * Дополнительная функция отчищение дерева без утечки памяти
 * @param root - ссылка на корень
 * @return - дерево состоящее исключительно из корня
 */
void *Clear(Node *root) {
    if (root->left != NULL) {
        Clear(root->left);
    }
    if (root->right != NULL) {
        Clear(root->right);
    }
    if ((root->left == NULL) && (root->right == NULL)) {
        free(root);
    }
}
/**
 * Функция удаления заданного количества элементов
 * @param node - ссылка на корень
 * @param negative_delta - заданное количетсво удаляемых элементов
 * @return - уменьшенное дерево
 */
Node *Delete(Node *node, int negative_delta) {
    int count = node->key;
    if (count - negative_delta < 2) {   //провекра возможности уменшения дерева
        printf("Oops, you can't reduce it anymore!\n");
        return node;
    }
    Clear(node);
    Node *tree = create();
    int flag = 0;
    for (int i = 0; i < count - negative_delta - 1; i++) {
        New(tree, &flag);
        flag = 0;
    }
    node = tree;
    return node;
}
/**
 * Горизонтальный (несовершенный, но это уже другое задание) вывод дерева (для самопроверки и демонстарции работы кода)
 * @param root - ссылка на корень
 * @param p - смещение по пробелам
 */
void printTree(Node *root, int p) {
    int i;
    if (root != NULL) {
        if (root->key > 0) {
            printTree(root->right, p + 3);
            for (i = 0; i < p; i++) {
                printf(" ");
            }
            printf("%d\n", root->key - 1);
            printTree(root->left, p + 3);
        }

    }
}

int main(void) {
    printf("\nDmitriev Mikhail, 5030102/10002, <6.3 laba> \n");
    Node *tree = create(); //создание корня
    int size = 6;   //размер будущего дерева
    tree = Add(tree, size); //добывление узлов к корню по заданному условию. Будем считать получившееся дерево - исходным.
    printf("-----------Initial-----------\n");
    printTree(tree, 1);

    int positive_delta = 4;
    printf("-----------Addition(%d)-----------\n", positive_delta);
    tree = Add(tree, positive_delta);
    printTree(tree, 1);

    int negative_delta = 5;
    printf("-----------Delete(%d)-----------\n", negative_delta);
    tree = Delete(tree, negative_delta);
    printTree(tree, 1);

    printf("\nWork completed :)\n");
}