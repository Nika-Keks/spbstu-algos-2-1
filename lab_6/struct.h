#pragma once

typedef struct node 
{
    int value;
    struct node* left;
    struct node* right;
}node;

struct node* Create_Binary_Tree_Node();
struct node* Set_Value(struct node* n, int value);
void Print_Tree(struct node* root);
void Insert_Node(struct node* root, int value);
struct node* Find_Predecessor(struct node* root);
struct node* Delete_Node(struct node* root, int value);
int Number_of_Nodes(node* root);
