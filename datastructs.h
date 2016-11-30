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
} g_data;

typedef void * Item;

node * initLinkedList();
node * newNode(Item data, node *next);
Item getData(node *cur);
void freeLinkedList(node *head, void (* freeItem)(Item));
node * nextNode(node *cur);
node * insertSortedList(node *first, Item item, int (* compFunc)(Item item1, Item item2));

graph * graphInit(int vert_num);
int graphGetVert(graph *g);
node ** graphGetAdj(graph *g);
void insertVertex(graph *g, int index, Item data);
void freeGraph(graph *g, void (* freeItem)(Item));

queue * queueInit(int size);
int queueIsEmpty(queue *q);
void insertInQueue(queue *q, Item data);
void fixUp(queue *q, int idx, int (* compItem)(Item item1, Item item2));
void fixDown(queue *q, int idx, int n, int (* compItem)(Item item1, Item item2));
Item *emptyHeap(queue *q);
Item removeHeap();
void Dijkstra(graph *g, int s, int *st, double *wt);

#endif
