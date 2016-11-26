/* File with generic graph descriptions, implemented using adjacency lists.
 * */

#include <stdlib.h>
#include <stdio.h>

struct _node {
    Item data;
    node *next;
};

/* Linked list definitions: */

node * initLinkedList() {
  return NULL;
}

node * newNode(Item data, node *next) {
    node *new;
    
    new = (node *)allocate(sizeof(node));
    new->data = data;
    new->next = next;
    
    return new;
}

node * nextNode(node *cur) {
    return ((cur == NULL) ? NULL : cur->next);
}

void freeLinkedList(node *head, void (* freeItem)(Item)) {
    node *next, *aux;
    
    for(aux = head; aux != NULL; aux = aux->next) {
        next = aux->next;
        freeItem(aux->data);
        free(aux);
    }
    
    return;
}

/* Graph (using adjacency lists) definitions: */

/* Heap definitions: */
