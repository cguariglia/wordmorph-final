#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_WT 100

typedef struct _node node;
typedef struct graph graph;
typedef struct edge edge;
typedef struct queue queue;

typedef struct {
    int vertex; 
    int weight;
} Item;

node * initLinkedList();
node * newNode(Item data, node *next);
Item getData(node *cur);
void freeLinkedList(node *head, void (* freeItem)(Item));
node * nextNode(node *cur);

graph * graphInit(int vert_num);

queue * queueInit(int size);
int queueIsEmpty(queue *q);
void insertInQueue(queue *q, Item data);
void fixUp(queue *q, int idx);
void fixDown(queue *q, int idx, int n);
Item *emptyHeap(queue *q);
Item removeHeap();
void Dijkstra(graph *g, int s, int *st, double *wt);

#endif
