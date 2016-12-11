#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_WT 1000

typedef struct _node node;
typedef struct graph graph;
typedef struct edge edge;
typedef struct queue queue;

typedef struct {
    int weight;
    int vertex; 
} g_data;

typedef void * Item;

int getvertice_adjstr(Item data);
node * initLinkedList();
node * newNode(Item data, node *next);
Item getData(node *cur);
void freeLinkedList(node *head, void (* freeItem)(Item));
node * nextNode(node *cur);
node * insertList(node *first, Item item);

g_data * newGData(int weight, int vertex);

graph * graphInit(int vert_num);
int graphGetVert(graph *g);
node ** graphGetAdj(graph *g);
int getGraphVertex(Item info);
int getGraphWeight(Item info);
void freeGraph(graph *g, void (* freeItem)(Item));

queue * queueInit(int size);
int queueIsEmpty(queue *q);
Item * queueGetData(queue *q);
void changeQueueData(queue *q, int idx, Item new_value);
void insertInHeap(queue *q, Item data, int (* compItem)(Item item1, Item item2));
void fixUp(queue *q, int idx, int (* compItem)(Item item1, Item item2));
void fixDown(queue *q, int idx, int n, int (* compItem)(Item item1, Item item2));
int emptyHeap(queue *q);
Item removeHeap(queue *q, int (* compItem)(Item item1, Item item2));
int findQueueV(queue *q, int vertex);
int getQSize(queue *q);
void freeHeap(queue *q);

#endif

