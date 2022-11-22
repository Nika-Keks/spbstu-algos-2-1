#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include"struct.h"

int main()
{
    //create a binary tree by nodes using the Create_Binary_Tree_Node() function
    struct node* n0  = Create_Binary_Tree_Node();
    struct node* n1 = Create_Binary_Tree_Node();
    struct node* n2 = Create_Binary_Tree_Node();
    struct node* n3 = Create_Binary_Tree_Node();
    struct node* n4 = Create_Binary_Tree_Node();     

    //make links in nodes
    n0->left = n1;
    n0->right = n2;
    n2->left = n3;
    n2->right = n4;

    /* The tree will look like this:
    //       n     
    //     /  \
    //    n1   n2    
    //        /  \
    //       n3   n4  
    */

    /*  we count the number of nodes in each node (according to the condition, you need to set the values in the nodes
     * equal to the number of nodes)
    */
    int n0_value = Number_of_Nodes(n0);   
    int n1_value = Number_of_Nodes(n1);
    int n2_value = Number_of_Nodes(n2);
    int n3_value = Number_of_Nodes(n3);
    int n4_value = Number_of_Nodes(n4);

    //set values to nodes
    n0 = Set_Value(n0, n0_value);
    n1 = Set_Value(n1, n1_value);
    n2 = Set_Value(n2, n2_value);
    n3 = Set_Value(n3, n3_value);
    n4 = Set_Value(n4, n4_value);

    printf("Initial binary tree:         ");
    Print_Tree(n0); //print a binary tree
    printf("\n");

    printf("Tree after adding node 1:    ");
    
    Insert_Node(n0, 1); //insert into the binary tree a node that will have a value in the node equal to 1
    Print_Tree(n0); //print a binary tree
    printf("\n");

    printf("Tree after deleting node n1: ");
    Delete_Node(n0, n1_value); //remove the node n1 from the binary tree
    Print_Tree(n0); //print a binary tree
    printf("\n");
   
    return 0;
}