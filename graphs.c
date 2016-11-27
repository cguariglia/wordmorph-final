

/* Header Inclusions                                              */
#include <stdio.h>
#include <stdlib.h>



/* Include Header File with Data Type and Function Prototypes     */
#include "graphs.h"



Graph *initGraph(int vertices_num) {
	
	int i;
	
	Graph *g = (Graph *)malloc(sizeof(Graph));
	
	g->info_graph->this1=0;
	g->info_graph->this2=vertices_num;

	g->adj = (LinkedList **)malloc(vertices_num * sizeof(LinkedList *));

	for(i = 0; i < vertices_num; i++) {
		g->adj[i] = NULL;
	}
	
	return g; 
}

void insertVertex(Graph *g, int index, char *word )
{
	g->adj[index]= insertLinkedList(NULL, word);
	g->info_graph->this1 +=1;
}





/*
 * 
 * Free Graph
 *  
 * 
 * 
 * 
 *  */
