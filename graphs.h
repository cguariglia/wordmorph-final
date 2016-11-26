#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _node node;
typedef void * Item;

node * initLinkedList();
node * newNode(Item data, node *next);
void freeLinkedList(node *head, void (* freeItem)(Item));
node * nextNode(node *cur);

#endif
