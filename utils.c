#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "datastructs.h"

/* In this file:
 * Functions that wouldn't fit in any other file, mostly related to dealing with the files themselves. */

/*
 *  Function:
 *   Allocate
 *
 *  Description:
 *    Wrapper function around malloc, including check for memory allocation failure.
 * 
 *  Arguments:
 *    Size of block to allocate:
 * 		  size_t size
 * 
 *  Return value:
 *    Void pointer to block of allocated memory
 */
void * allocate(size_t size) {
	void *ptr;
	
	ptr = malloc(size);
	
	if(ptr == NULL) 
		exit(0);
	
	return ptr;
}

/*
 *  Function:
 *   initArray
 *
 *  Description:
 *    Initializes an 1D array of integers. 
 * 
 *  Arguments:
 *    Array of integers:
 * 		  int * array
 *    Size of array:
 *        int size
 *
 *  Return value:
 *    None
 */
void initArray(int *array, int size) {
	int i;
	
	for( i = 0; i < size; i++)
		array[i] = 0;
			
	return;
}

/*
 *  Function:
 *   fcheck
 *
 *  Description:
 *    Checks if the file has the correct extension and opens file.
 * 
 *  Arguments:
 *    File name:
 * 		  char * name
 *    Extension to compare to:
 *        char * ext
 *
 *  Return value:
 *    Pointer to the file stream of opened file
 *      FILE * f
 */
FILE * fcheck(char *fname, char *ext) {
	FILE *f;
	
	if(strcmp(strrchr(fname, '.'), ext) != 0)
		exit(0);
	
	f = fopen(fname, "r");
	if(f == NULL)
		exit(0);
	
	return f;
}

/*
 *  Function:
 *   compInts
 *
 *  Description:
 *    
 * 
 *  Arguments:
 *    File name:
 * 		  Item i1
 *    Extension to compare to:
 *        Item i2
 *
 *  Return value:
 *    Pointer to the file stream of opened file
 *        int 
 */
int compInts(Item i1, Item i2) {
    int *num1 = i1;
    int *num2 = i2;
    
    if(*num1 > *num2)
        return 1;
    else if(*num1 == *num2)
        return 0;
    else if(*num1 < *num2)
        return -1;
        
    return 0;
}

/*
 *  Function:
 *   compInts
 *
 *  Description:
 *    
 * 
 *  Arguments:
 *    File name:
 * 		  Item i1
 *    Extension to compare to:
 *        Item i2
 *
 *  Return value:
 *    Pointer to the file stream of opened file
 *        int 
 */
int compWeight(Item i1, Item i2) {
    g_data *item1 = i1;
    g_data *item2 = i2;

    /* if in need of cycles use substraction for this e.g weight1 - weight2 or vice-versa */
    if(item1->weight > item2->weight)
        return 1;
    else if(item1->weight == item2->weight)
        return 0;
    else if(item1->weight < item2->weight)
        return -1;
        
    return 0;
}


void lowerWeight(queue *q, int idx, Item new_weight) {
    g_data _data = {0, 0};
    g_data *data = &_data;
    
    changeQueueData(q, idx, data);
    return;
}


/*
 *  Function:
 *   calculateDifferentLetters
 *
 *  Description:
 *    Calculates number of different characters between two strings.
 * 
 *  Arguments:
 *    String to compare:
 * 		  char * word1
 *    String to compare:
 * 		  char * word2
 * 
 * 
 *  Return value:
 *    Number of different letters between different words
 *        int different_letters
 */
/* Returns how many different letters there are in different words */
int calculateDifferentLetters(char *word1, char *word2) {
    int i, different_letters = 0;
    
    for(i = 0; i < strlen(word1); i++)
        if(word1[i] != word2[i])
            different_letters += 1;
    
    return different_letters;
}



/*
 *  Function:
 *    dijkstra
 *
 *  Description:
 *    Determinates shortest path from origin vertice to all other vertices in that graph.
 * 
 *  Arguments:
 *    Graph:
 * 		  graph * g
 *    Origin vertice:
 * 		  int  s
 *    Array of integers that will be filled with the shortest paths :
 * 		  int *st
 *    Array of integers that will be filled with the weight of the path to each vertice:
 * 		  int *wt

 *  Return value:
 *    None
 */
void dijkstra(graph *g, int s, int *st, int *wt) {
	g_data *help_w, *aux;
    int w, vertex, verts, aux_vertex, aux_w, h_pos;
    queue *q;
    node **aux_adj;
	node *t;

    verts = graphGetVert(g); 
	q = queueInit(verts);
    
	for(vertex = 0; vertex < verts; (vertex)++) {
		st[vertex] = -1;
		wt[vertex] = MAX_WT;
		insertInHeap(q, newGData(MAX_WT, vertex) , compWeight); 
	}
	
	wt[s] = 0;
	changeQueueData(q, s, newGData(0, s)); 
	fixUp(q, s, compInts);
	
	while(!emptyHeap(q)) {
      
		help_w = (g_data *)removeHeap(q, compWeight);
        aux_vertex = help_w->vertex;
        
		if(wt[aux_vertex] != MAX_WT){
			
            aux_adj = graphGetAdj(g); 
			for(t = aux_adj[aux_vertex]; t != NULL; t = nextNode(t)) {
                aux = (g_data *)getData(t);
                w = aux->vertex;
                aux_w = aux->weight;
				
                          
				if(wt[w] > (wt[aux_vertex] + aux_w)) {
					wt[w] = (wt[aux_vertex] + aux_w);
                    
                    h_pos=findQueueV(q, verts, w);  /*Encontrar pos da heap com o vertice w para lhe alterar o peso*/
                    changeQueueData(q, h_pos, newGData(wt[w], w));   
                   
                    fixUp(q, h_pos, compInts);
					st[w] = aux_vertex;
				}
			}
		}
	}
    return;
}


/*
 *  Function:
 *    WriteOutput
 *
 *  Description:
 *    Writes the first line of the solution in the output file.
 * 
 *  Arguments:
 *    Pointer to the file stream:
 *        FILE * fp
 *    Word to be written:
 *		  char * word
 *    Cost of the problem:
 * 		  int cost
 * 
 *  Return value:
 *    None
 */
/*Write the first line for each problem in the solution file */
void writefirstOutput(FILE * fp, char * word, int cost) { 
	   fprintf(fp, "%s %d\n", word, cost); /* Write origin word and cost*/

    return;
}

/*
 *  Function:
 *   WriteOutput
 *
 *  Description:
 *    Writes a word in the output file.
 * 
 *  Arguments:
 *    Pointer to the file stream:
 *        FILE * fp
 *    Word to be written:
 *		  char * word
 * 
 *  Return value:
 *    None
 */
void writeOutput(FILE * fp, char * word) { 
    
    fprintf(fp, "%s\n", word);

    return;
}

/*
 *  Function:
 *   OutputFileExtention
 *
 *  Description:
 *    Generates the name of the output file based on the input file, 
 * 	  now with the extension .path.
 *
 *  Arguments:
 *    Name of the input file:
 *        char * name_input
 *
 *  Return value:
 *    Name of the output file:
 *      char * name_output 
 */
char * outputFileExtension(char * name_input){
	char *name_output, *dot;
	
	name_output = (char *)allocate(strlen(name_input) + 2);
	dot = strrchr(name_input, '.');
	
	*dot = '\0';
	
	strcat(name_input, ".path");
	strcpy(name_output, name_input);
	
	return name_output;
}

/*
 *  Function:
 *   freeMatrix
 *
 *  Description:
 *    Frees Dictionary Matrix.
 * 
 *  Arguments:
 *    Dictionary Matrix:
 * 		 char ***mar
 *    Size Array with the number of occurences of each size of word:
 *       int *size
 *    Size of the first dimension of the Matrix:
 *       int init_size
 *
 *  Return value:
 *    None
 */
void freeMatrix(char ***mat, int *size, int init_size) {
	int i, j;
	
	for(i = 0; i < init_size; i++) {
		for(j = 0; j < size[i]; j++)
			free(mat[i][j]);
		if(size[i] != 0)
			free(mat[i]);
	}
	return;
}

