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
	
	for(aux = first; aux != NULL; aux = aux->next) {
		if(compFunc(item, aux->next->data) > 0) {
			new_node = newNode(item, aux->next);
			aux->next = new_node;
            
			if(aux == first)
				new_first = new_node;
			else
				new_first = first;
		}
	}

	return new_first;
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


void insertVertex(graph *g, int index, Item data) {
	g->adj[index] = newNode(data, NULL);
	g->vertices += 1;
    
    return;
}

void freeGraph(graph *g, void (* freeItem)(Item)) {
    int i;
    
    for (i = 0; i < g->vertices; i++)
        freeLinkedList(g->adj[i], freeItem);
        
    free(g->adj);
    free(g);
    
    return;
}

/* Heap definitions: */

queue * queueInit(int size) {
    queue *q;
    
    q = (queue *)malloc(size * sizeof(Item));
    if(q == NULL)
        exit(0);
    q->size = size;
    q->first = 0;
    
    return q;
}

int queueIsEmpty(queue *q) {
    return q->first == 0;
}

void insertInHeap(queue *q, Item data) {
    int next;
    next = q->first + 1;
    
    if(next < q->size) {
        q->data[next] = data;
        fixUp(q, q->first);
        q->first = next;
    }
    else /* If somenody tries to insert something in an already full queue */
        exit(0);
        
    return;
}

void fixUp(queue *q, int idx) {
	Item aux;
	
	while (idx > 0 && compItem(q->data[(idx-1)/2], q->data[idx]) > 0) {		
        aux = q->data[idx];
        q->data[idx] = q->data[(idx-1)/2];
        q->data[(idx-1)/2] = aux;
        
        idx = (idx-1)/2;
	}
    
    return;
}


void fixDown(queue *q, int idx, int n) {
	Item aux;
    int child;
	
	while (2 * idx < n - 1){
		child = 2 * idx + 1;
		
		if(child < (n - 1) && compItem(q->data[child], q->data[child+1]) > 0)
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


/* retira o elemento de mais baixa prioridade*/
Item removeHeap(queue *q) {
	Item aux;
	
	--(q->first);	
	aux = q->data[0];

	return aux;
}

void Dijkstra(graph *g, int s, int *st, double *wt) {
	int v, w;
    queue *q;
	node *t;
	
	q = queueInit(1000); /* TODO: definir tamanho máximo do heap */
	
	for(v = 0; v < g->vertices; v++) {
		st[v] = -1;
		wt[v] = MAX_WT;
		insertInHeap(q, v);
	}
		
	wt[s] = 0.0;
	fixDown(s); /* altera a posicao do elemento por ter baixado prioridade */
	while(!queueIsEmpty)
		if(wt[v = RemoveHeap] != MAX_WT)
			for(t= g->adj[v]; t!= NULL; t=t->next)
				if(wt[w=t->this1] > (wt[v] + t->wt)){
					
					wt[w]= (wt[v] + t->wt) ;
					DecHeap(w);
					st[w]=v;
				}
}
