#ifndef GRAPHS
#define GRAPHS



#include "LinkedList.h"


typedef struct _Graph
{
	Item info_graph;
	struct LinkedList **adj;
	
}Graph;


Graph *initGraph(int vertices_num);
void insertVertex(Graph *g, int index, char *word );



#endif
