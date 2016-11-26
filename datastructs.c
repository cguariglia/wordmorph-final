/* File with generic graph descriptions, implemented using adjacency lists.
 * */

#include <stdlib.h>
#include <stdio.h>
#include "datastructs.h"

struct _node {
    Item data;
    node *next;
};

struct graph {
    int vertices;
    int edges;
    node **adj;
};

struct edge {
    Item v;
    Item w;  
};

struct queue {
    int size;
    int first;
    Item *data;
};

/* Linked list definitions: */

node * initLinkedList() {
    return NULL;
}

node * newNode(Item data, node *next) {
    node *new;
    
    new = (node *)malloc(sizeof(node));
    if(new == NULL)
        exit(0);
    new->data = data;
    new->next = next;
    
    return new;
}

node * nextNode(node *cur) {
    return ((cur == NULL) ? NULL : cur->next);
}

node * getData(node *cur) {
    if(cur == NULL)
        return NULL;
    else
        return cur->data;
}

void freeLinkedList(node *head, void (* freeItem)(Item)) {
    node *next, *aux;
    
    for(aux = head; aux != NULL; aux = next) {
        next = aux->next;
        freeItem(aux->data);
        free(aux);
    }
    
    return;
}

/* Graph (using adjacency lists) definitions: */

graph * graphInit(int vert_num) {
    graph *g;
    int i;
    
    g = (graph *)malloc(sizeof(graph));
    if(g == NULL)
        exit(0);
        
    g->vertices = vert_num;
    g->edges = 0;
    g->adj = (node **)malloc(vert_num * sizeof(node *));
    if(g->adj == NULL)
        exit(0);
        
    for(i = 0; i < vert_num; i++)
        g->adj[i] = NULL;
        
    return g;
}

/* void graphInsert(graph *g, edge *e) {
    g->adj[e->v] = newNode()
    
    g->edges += 1;
} */

/* Heap definitions: */

queue * queueInit(int size) {
    queue *q;
    
    q = (queue *)malloc(size * sizeof(Item));
    q->size = size;
    q->first = 0;
    
    return q;
}

int queueIsEmpty(queue *q) {
    return q->first == 0;
}

void insertInQueue(queue *q, Item data) {
    int next;
    next = q->first + 1;
    
    if(q->first < q->size) {
        q->data[next] = data;
        q->first = next;
    }
    else
        exit(0);
        
    return;
}
