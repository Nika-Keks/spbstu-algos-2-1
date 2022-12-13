#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/**
 * Структура узла дерева
 * @param key - значение в узле
 * @param left - указатель на левую ветку
 * @param right - указатель на правую ветку
 * @param parent - указатель на родителя
 */
typedef struct tree {
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node;
/**
 * Функция создания корня
 * @param root - ссылка на корень
 * @param key - значение в корне
 * @return - ссылка на корень
 */
node *create(node *root, int key) {
    node *tmp = malloc(sizeof(node));
    tmp->key = key;
    tmp->parent = NULL;
    tmp->left = tmp->right = NULL;
    root = tmp;
    return root;
}
/**
 * Функция добавления элемента в дерево
 * @param root -ссылка на корень
 * @param key - какое значение добавить
 * @return - ссылка на корень
 */
node *Dobavlenie(node *root, int key) {
    node *root2 = root; // бегунок
    node *root3 = NULL;  // будущая ссылка на родителя
    node *tmp = malloc(sizeof(node));
    tmp->key = key; // новый листок дерева
    while (root2 != NULL) { 
        root3 = root2;
        if (key < root2->key)
            root2 = root2->left;
        else
            root2 = root2->right;
    }
    tmp->parent = root3;
    tmp->left = NULL;
    tmp->right = NULL;
    if (key < root3->key) root3->left = tmp;
    else root3->right = tmp;
    return root;
}
/**
 * Функция поиска подкорня с заданным ключом
 * @param root - ссылка на корень
 * @param key - заданный ключ
 * @return - ссылка на подкорень
 */
node *Poisk_key(node *root, int key) {
    if (root->key == key)
        return root;
    if (root->right == NULL && (root->left == NULL)){
        if (root->key == key){
            return root;
        }
        else{
            printf("\nNot found with the key = %d  :(\n", key);
            exit(0);
        }
    }
    if (key < root->key)
        return Poisk_key(root->left, key);
    else return Poisk_key(root->right, key);
}
/**
 *  * Рекурсивная функция удаления подветки от подкорня
 * @param root - ссылка на корень
 * @return - очищение ветки
 */
void *Delete(node *root) {
    if (root->left != NULL){
        Delete(root->left);
    }
    if (root->right != NULL){
        Delete(root->right);
    }
    if ((root->left == NULL) && (root->right == NULL)){
        free(root);
    }
}
/**
 * Функция поиска и удаления подветки от подкорня с заданным ключом
 * @param root - ссылка на корень
 * @param key - заданный ключ
 * @return - ссылка на корень с удаленной подветкой
 */
node *Poisk_delete(node *root, int key) {
    node *l = NULL, *m = NULL;
    if (root->key == key){
        printf("Oh no. You have deleted the entire tree\n");
        exit(0);
    }
    l = Poisk_key(root, key);
    m = l -> parent;
    if (l == m -> right) m -> right = NULL;
    else m -> left = NULL;
    Delete(l);
    return root;
}
/**
 * Горизонтальный (несовершенный, но это уже другое задание) вывод дерева (для самопроверки и демонстарции работы кода)
 * @param root - ссылка на корень
 * @param p -
 */
void printTree(node* root, int p)
{
    int i;
    if(root != NULL){
        printTree(root->right,p+3);
        for(i=0;i<p;i++)
        {
            printf(" ");
        }
        printf("%d\n", root->key);
        printTree(root->left,p+3);
    }
}
int main() {
    printf("\nDmitriev Mikhail, 5030102/10002, <5.8 laba> \n");

    //Заполнение дерева псевдаслучайными числами от 0 до 100
    double x = rand() % 100;
    node *tree = create(tree, (int)x);
    for (int i = 0; i < 15; i++) {
        x = rand() % 100;
        Dobavlenie(tree, (int)x);
    }
    printf("\nMade a tree (horizontal output):\n");
    printTree(tree, 0);

    int key = 58;
    //printf("Enter the key="); // Для возможности ввода ключа пользователем
    //scanf("%d", &key);

    Poisk_delete(tree, key);
    printf("---------------------------\nDeleted a subtree with the root (key value = %d)\n", key);
    printTree(tree, 0);
    printf("\nWork completed :)\n");
    return 0;
}
