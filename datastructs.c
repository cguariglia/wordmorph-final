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

struct queue {
    int size;
    int first; /* as in first empty spot in the queue */
    Item *data;
};

/* Linked list definitions: */

node * initLinkedList() {
    return NULL;
}

/* Given data and the next node, makes a new node */
node * newNode(Item data, node *next) {
    node *new;
    
    new = (node *)malloc(sizeof(node));
    if(new == NULL)
        exit(0);
    new->data = data;
    new->next = next;
    
    return new;
}

/* Returns a node because it's easier than passing a double pointer. */
node * changeNodeData(node *old, Item new_data) {
    old->data = new_data;
    return old;
}

/* Returns the node following cur */
node * nextNode(node *cur) {
    return ((cur == NULL) ? NULL : cur->next);
}

/* Returns cur's data */
Item getData(node *cur) {
    if(cur == NULL)
        exit(0);
    else
        return cur->data;
}

/* Inserts node in such a way as to make a sorted list.
 * compFunc must return < 0 if the first item is smaller than the next, = 0 if it's the same and > 0 if it's bigger */
node * insertSortedList(node *first, Item item, int (* compFunc)(Item item1, Item item2)) {
	node *aux, *new_node, *new_first;
    
    new_first = first;

	if(first == NULL) {
        first = newNode(item, NULL);
        new_first = first;
    }
    else {
        for(aux = first; aux != NULL; aux = aux->next) {
            /* If the next node is null, then we can't access aux->next->data.
             * So we insert the node at the end. */
            if(aux->next == NULL) {
                new_node = newNode(item, NULL);
                aux->next = new_node;
                
                /* Sometimes the end is the very first node, though. */
                if(aux == first)
                    new_first = new_node;
                
                break;
            }
            else if(compFunc(item, aux->next->data) > 0) {
                new_node = newNode(item, aux->next);
                aux->next = new_node;
            }
            
        }
    }
    
	return new_first;
}

/* Iterates through the linked list, freeing every node in the meantime */
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

/* Initializes graph, given the number of vertices on it. The graph starts with no edges, obviously. */
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

int graphGetVert(graph *g) {
    return g->vertices;
}

node ** graphGetAdj(graph *g) {
    return g->adj;
}

void insertVertex(graph *g, int index, Item data) {
	g->adj[index] = newNode(data, NULL);
	g->vertices += 1;
    
    return;
}

/* Frees the graph (including it's adjacency list */
void freeGraph(graph *g, void (* freeItem)(Item)) {
    int i;
    
    for (i = 0; i < g->vertices; i++)
        freeLinkedList(g->adj[i], freeItem);
        
    free(g->adj);
    free(g);
    
    return;
}


/* Heap definitions: */

/* Initializes a queue given its size */
queue * queueInit(int size) {
    queue *q;
    
    q = (queue *)malloc(size * sizeof(queue));
    if(q == NULL)
        exit(0);
           
    q->data=(Item *)malloc(size * sizeof(Item)); 
    if(q->data == NULL)
        exit(0);
         
    q->size = size;
    q->first = 0;
    
    return q;
}

Item * queueGetData(queue *q) {
    return q->data;
}

/* Gives the user an opportunity to change the queue data */
void changeQueueData(queue **q, int idx, Item new_value) {
    (*q)->data[idx] = new_value;
    return;
}

/* Checks if the heap is empty or not */
int emptyHeap(queue *q) {	
    return (q->size == 0);
}

void insertInHeap(queue *q, Item data, int (* compItem)(Item item1, Item item2)) {
    if(q->first + 1 < q->size) {
        q->data[q->first] = data;
        fixUp(q, q->first, compItem);
        q->first += 1;
    }
    else /* If somenody tries to insert something in an already full queue */
        exit(0);
        
    return;
}

void fixUp(queue *q, int idx, int (* compItem)(Item item1, Item item2)) {
	Item aux;
    
	while (idx > 0 && compItem(q->data[(idx-1)/2], q->data[idx]) > 0) {
        aux = q->data[idx];
        q->data[idx] = q->data[(idx-1)/2];
        q->data[(idx - 1)/2] = aux;
        idx = (idx - 1) / 2;
	}
    
    return;
}


void fixDown(queue *q, int idx, int n, int (* compItem)(Item item1, Item item2)) {
	Item aux;
    int child;
	
	while (2 * idx < n - 1){
		child = 2 * idx + 1;
		
		if(child < (n - 1) && compItem(q->data[child], q->data[child + 1]) > 0)
            child++;
		
		if(compItem(q->data[idx], q->data[child]) < 0)
            break;
		
		aux = q->data[idx];
		q->data[idx] = q->data[child];
		q->data[child] = aux;
		
		idx = child;
	}
	
    return;
}

/* This is a terrible function name.
 * It lowers something's priority and then fixes the heap afterwards. */
void fixLowerPriority(queue *q, int idx, Item n_p, void (* lowerPriority)(queue *q, int idx, Item new_priority), int (* compItem)(Item item1, Item item2)) {
    lowerPriority(q, idx, n_p);
    fixUp(q, idx, compItem);
    return;
}

Item removeHeap(queue *q, Item n_p, void (* lowerPriority)(queue *q, int idx, Item new_priority), int (* compItem)(Item item1, Item item2)) {
	Item aux;
    
    fixLowerPriority(q, 0, n_p, lowerPriority, compItem);
    printf("hi\n");
    
	aux = q->data[q->first];
	--(q->first);

	return aux;
}

void freeHeap() {
    
}
