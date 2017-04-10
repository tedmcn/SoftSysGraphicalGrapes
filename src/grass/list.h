#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    float * val;
} Node;

Node *make_node(float val[8], Node *next);
float* pop(Node **list);
void push(Node **list, float val[8]);