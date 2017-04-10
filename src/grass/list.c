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
Node *make_node(float val[8], Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
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
    Node *new_head = make_node(val, head);

    // Reset list to new head
    *list = new_head;
}
