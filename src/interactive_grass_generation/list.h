/* 
 * List - Provide a simple limked list interface, nodes store float arrays
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    float val[8];
} Node;

Node *makeNode(float val[8], Node *next);
float* pop(Node **list);
void push(Node **list, float val[8]);
int numNodes(Node **list);