#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include"struct.h"

struct node* Create_Binary_Tree_Node()
{
    struct node* n;
    n = (node*)malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;
    return n;
}
//a function that creates a binary tree node

struct node* Set_Value(struct node* n, int value)
{
    n->value = value;
    return n;
}
//a function that sets a value in a node

void Print_Tree(struct node* root)
{
    if (root != NULL)
    {
        Print_Tree(root->left);
        printf("%d ", root->value);
        Print_Tree(root->right);
    }
}
//a function that prints a binary tree

void Insert_Node(struct node* root, int value)
{
    struct node* prev_node = NULL;
    while (root != NULL)
    {
        prev_node = root;

        if (root->right >= root->left) //we go along the binary tree along the path of the least number of nodes 
            root = root->left;
        else
            root = root->right;

    }
    struct node* new_node = Create_Binary_Tree_Node();
    new_node = Set_Value(new_node, value);

    /*  this is the last node, it needs to be placed in the branch
    *   (according to the condition, it is not said which one to place,
    *   so I put it on the left)
    */
    prev_node->left = new_node;

}
//a function that inserts a node into a binary tree


/* When we delete a binary tree node, we need to replace it with its ancestor.
*  The Find_Predecessor function looks for the predecessor for the node we are deleting,
*  it is the rightmost node of its left subtree.
*/

struct node* Find_Predecessor(struct node* root)
{
    root = root->left;
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
//a function that looks for the predecessor of a binary tree node

struct node* Delete_Node(struct node* root, int value)
{

    struct node* prev_node; //a pointer to the predecessor of the node we are deleting

    if (root == NULL)
        return NULL;

    if (root->left == NULL && root->right == NULL)
    {
        free(root);
        return NULL;
    }

    //recursively search for the node in the binary tree to be removed
    if (value < root->value)
        root->left = Delete_Node(root->left, value);

    if (value > root->value)
    {
        root->right = Delete_Node(root->right, value);
    }

    /* if we have found the desired node, then using the Find Predecessor function we are looking for a predecessor,
    *  then copy its value to the root node, call the Delete_Node function recursively to
    *  left subtree, to remove the predecessor (its value is already in the root node)
    */
    if (value == root->value)
    {
        prev_node = Find_Predecessor(root);
        root->value = prev_node->value;
        root->left = Delete_Node(root->left, prev_node->value);
    }
    return root;
}
//a function that removes a binary tree node

int Number_of_Nodes(node* root)
{
    if (root == NULL)
        return 0;

    int right_height = 0;
    int left_height = 0;
    node* node1 = root;
    node* node2 = root;
    while (node1 != NULL)  //calculate the height of the right subtree
    {
        right_height++;
        node1 = node1->right;
    }

    while (node2 != NULL)  //calculate the height of the left subtree
    {
        left_height++;
        node2 = node2->left;
    }

    if (left_height == right_height) //if the heights of the left and right subtrees are equal, then this is a complete tree, return its height
        return (pow(2, left_height) - 1);
    return 1 + Number_of_Nodes(root->left) + Number_of_Nodes(root->right); //add one to count the root from which we count number of nodes
}
//a function that calculates the total height of a binary tree