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
node * insertSortedList(node *first, Item item, int (* compFunc)(Item item1, Item item2));

g_data * newGData(int weight, int vertex);

graph * graphInit(int vert_num);
int graphGetVert(graph *g);
node ** graphGetAdj(graph *g);
void insertVertex(graph *g, int index, Item data);
void printGraph(graph *g);
void freeGraph(graph *g, void (* freeItem)(Item));

queue * queueInit(int size);
int queueIsEmpty(queue *q);
Item * queueGetData(queue *q);
void changeQueueData(queue **q, int idx, Item new_value);
void insertInHeap(queue *q, Item data, int (* compItem)(Item item1, Item item2));
void fixUp(queue *q, int idx, int (* compItem)(Item item1, Item item2));
void fixDown(queue *q, int idx, int n, int (* compItem)(Item item1, Item item2));
int emptyHeap(queue *q);
void fixLowerPriority(queue *q, int idx, Item n_p, void (* lowerPriority)(queue *q, int idx, Item new_priority), int (* compItem)(Item item1, Item item2));
Item removeHeap(queue *q, int (* compItem)(Item item1, Item item2));
int getGraphVertex(Item info);
int getGraphWeight(Item info);
Item removeMinHeap(queue *q, int (* compItem)(Item item1, Item item2));
int find_Queuev(queue *q, int original_qsize, int vertex);
int get_qsize(queue *q);
#endif

