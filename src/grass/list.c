/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include "list.h"


/* Makes a new node structure.
 * 
 * val: value to store in the node.
 * next: pointer to the next node
 *
 * returns: pointer to a new node
 */
Node *makeNode(float val[8], Node *next) {
  Node *node = malloc(sizeof(Node));

  node->val[0] = val[0];
  node->val[1] = val[1];
  node->val[2] = val[2];
  node->val[3] = val[3];
  node->val[4] = val[4];
  node->val[5] = val[5];
  node->val[6] = val[6];
  node->val[7] = val[7];
  node->next = next;
  return node;
}


/* Removes and returns the first element of a list.
 * 
 * list: pointer to pointer to Node
 *
 * returns: int or -1 if the list is empty
 */
float* pop(Node **list) {
  // Save the head value
  Node *head = *list;
  float * temp = head->val;

  // Check for null
  if (&head->next != NULL) {
    **list = *head->next;
  }
  
  return temp;
}


/* Adds a new element to the beginning of the list.
 * 
 * list: pointer to pointer to Node
 * val: value to add
 */
void push(Node **list, float val[8]) {
    // Get the head value
    Node *head = *list;

    // Create new node with head as next
    Node *new_head = makeNode(val, head);

    *list = new_head;
}

int numNodes(Node **list) {
    Node *dummy = *list;
    int i = 0;

    while (dummy->next != NULL) {
        dummy = dummy->next;
        i++;
    }
    return i;
}
