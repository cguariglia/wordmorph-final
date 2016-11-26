#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _node node;
typedef void * Item;
typedef struct graph graph;
typedef struct edge edge;
typedef struct queue queue;

node * initLinkedList();
node * newNode(Item data, node *next);
node * getData(node *cur);
void freeLinkedList(node *head, void (* freeItem)(Item));
node * nextNode(node *cur);

graph * graphInit(int vert_num);

queue * queueInit(int size);
int queueIsEmpty(queue *q);
void insertInQueue(queue *q, Item data);

#endif
