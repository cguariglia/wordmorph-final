/* File with generic graph descriptions, implemented using adjacency lists.
 * */

#include <stdlib.h>
#include <stdio.h>
#include "datastructs-test.h"

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

Item  getData(node *cur) {
  /*  if(cur == NULL)
        return NULL;
    else */
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


void insertVertex(graph *g, int index, Item data) {
	
	node *aux, *ptr;
	
	if(g->adj[index]==NULL) g->adj[index] = newNode(data, NULL);
	else{

		aux = newNode(data, NULL);
		
		ptr=g->adj[index];
		while(ptr->next!=NULL) ptr=ptr->next;
		
		ptr->next=aux;
	}
    return;
}

/* Heap definitions: */

queue * queueInit(int size) {
    queue *q;
    
    q = (queue *)malloc(size * sizeof(queue));
    if(q == NULL)
        exit(0);
     
    q->data=(Item *)malloc(size * sizeof(Item));
    q->size = 0;
    q->first = 0;
    
    return q;
}

int queueIsEmpty(queue *q) {
    return q->first == 0;
}

void insertInHeap(queue *q, Item data) {
    int next;
    next = q->size;
    
   /* if(next < q->size) {*/

        q->data[next] = data; 
        fixUp(q, q->size);
        q->size=1+q->size;
        
    /*}*/
  /*  else If somenody tries to insert something in an already full queue */
     
     /*   exit(0);*/
        
    return;
}

void fixUp(queue *q, int idx) {
	Item aux;
	
	while (idx > 0 && (q->data[(idx-1)/2].weight > q->data[idx].weight)){		
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
		
		if(child < (n - 1) && (q->data[child].weight > q->data[child+1].weight))
            child++;
		
		if((q->data[idx].weight < q->data[child].weight))
            break;
		
		aux = q->data[idx];
		q->data[idx] = q->data[child];
		q->data[child] = aux;
		
		idx = child;
	}
	
    return;
}


Item *emptyHeap(queue *q) {	
    if (q->size == 0) return NULL;
}

/* retira o elemento de mais baixa prioridade*/
int removeHeap(queue *q) {
	Item aux;
	
	aux = q->data[q->first];
	++(q->first);	
	--(q->size);	

	return aux.vertex;
}



/* Aqui so mesmo para testar o alg*/

void readMatrix(FILE *input, graph *output) {
	int v1, v2,  edges_num;
	int weight;
	
	Item info;
	
	fscanf(input, "%d", &edges_num);
	output->edges = edges_num;
				
	
	while(fscanf(input, "%d %d %d", &v1, &v2, &weight) == 3) {
				
	   
		info.vertex=v2;
		info.weight=weight;
		
		insertVertex(output,v1,info); /* Ele cria bem o grafo e gera as listas certas e de acordo com o exemplo do prof*/
 	}
	
	return;
	
}






void Dijkstra(graph *g, int s, int *st, int *wt) {
	int  w, i;
	Item v;
    queue *q;
	node *t;
	
	
	q = queueInit(1000); /* TODO: definir tamanho máximo do heap */

	for(v.vertex = (g->vertices)-1; v.vertex >=0; v.vertex--) {
		
		st[v.vertex] = -1;		
		wt[v.vertex] = MAX_WT;
		v.weight=MAX_WT;	
		insertInHeap(q,v);	
	}
		
	wt[s] = 0;
	
	q->data[g->vertices -1 -s].weight=0; /* Coloca a pos correspondente ao vertice s com peso a 0*/
	fixUp(q, g->vertices -1 -s); /* altera a posicao do elemento por ter baixado prioridade for(v.vertex = 0; v.vertex < (g->vertices); v.vertex++)*/
 

	while(emptyHeap(q)!=NULL){ 
		if(wt[v.vertex = removeHeap(q)] != MAX_WT){
			for(t = g->adj[v.vertex]; t!= NULL; t=t->next){

				if(wt[w=t->data.vertex] > (wt[v.vertex] + t->data.weight)){

					wt[w]= (wt[v.vertex] + t->data.weight) ;
					q->data[g->vertices -1 -w].weight=wt[w];
					
					fixUp(q,g->vertices -1 -w);
					st[w]=v.vertex;
				}
			}
		}
	}		
	for(i=0; i < g->vertices;i++) printf("\n O vetor st:%d", st[i]); /* Confirmar spt*/
	for(i=0; i < g->vertices;i++) printf("\n \tO vetor WT:%d", wt[i]); /* Confirmar spt*/
}
