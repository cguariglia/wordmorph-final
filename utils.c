#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "datastructs.h"

/* In this file:
 * Functions that wouldn't fit in any other file, mostly related to dealing with the files themselves and Dijkstra's algorithm */

/* Wrapper function around malloc, including check for memory allocation failure. */
void * allocate(size_t size) {
	void *ptr;
	
	ptr = malloc(size);
	
	if(ptr == NULL)
		exit(0);
	
	return ptr;
}

/* Checks if the file has the correct extension and opens file. */
FILE * fcheck(char *fname, char *ext) {
	FILE *f;
	
	if(strcmp(strrchr(fname, '.'), ext) != 0)
		exit(0);
	
	f = fopen(fname, "r");
	if(f == NULL)
		exit(0);
	
	return f;
}

/* Given a name and a desired file extension, returns the new filename */
char* outputFileExtension(char * name_input){
	char *name_output, *dot;
	
	name_output = (char *)allocate(strlen(name_input) + 2);
	dot = strrchr(name_input, '.');
	
	*dot = '\0';
	
	strcat(name_input, ".path");
	strcpy(name_output, name_input);
	
	return name_output;
}

/* Returns how many letters differ between two words */
int calculateDifferentLetters(char *word1, char *word2, int cost) {
    int i, different_letters = 0;
    
    for(i = 0; i < strlen(word1); i++){
        if(word1[i] != word2[i])
            different_letters += 1;
            
        if((different_letters > cost) && (cost != -2) ) return -1; /* When this function is used to determine insertion in adj list 
        when the number of different letters is bigger than the maximum cost return value < 0 */
        
        /* When this function is used in any other context, the cost has the value - 2 */
    } 
    return different_letters;
}


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

/* Given two g_datas, compares their weights
 * Obviously the Items/void * need to be g_datas */
int compWeight(Item i1, Item i2) {
    g_data *item1 = i1;
    g_data *item2 = i2;

    if(item1->weight > item2->weight)
        return 1;
    else if(item1->weight == item2->weight)
        return 0;
    else if(item1->weight < item2->weight)
        return -1;
        
    return 0;
}

void dijkstra(graph *g, int s, int end, int max_step, int *st, int *wt) {
    int w, vertex, verts, aux_w, h_pos;
    queue *q;
    node **aux_adj;
	node *t;
    g_data _change_data = {0, 0};
	g_data *aux, *help_w, *change_data = &_change_data;

    /* Init Heap with two arrays with same size as the number of vertices in the graph */
    verts = graphGetVert(g); 
	q = queueInit(verts);
    
    /* Init weight of vertices in the heap and wt with MAX_WT and st with -1 */
    for(vertex = 0; vertex < verts; vertex++) {
		st[vertex] = -1;
		wt[vertex] = MAX_WT;
		insertInHeap(q, newGData(MAX_WT, vertex), compWeight);
	}
   
	/* Change weight of origin vertex in wt to 0 */
	wt[s] = 0;
    change_data->vertex = s;
    change_data->weight = 0;
	changeQueueData(q, s, change_data); /* Change weight of origin vertex in heap to 0 */
	fixUp(q, s, compWeight); /* Reinstate heap condition */

	while(!emptyHeap(q)) {
        help_w = (g_data *)removeHeap(q, compWeight);
        /* If we've already found the end node, then there's no point in continuing */
        if(help_w->vertex == end) {
            free(help_w);
            break;
        }
        
        if(wt[help_w->vertex] != MAX_WT) { /* If there is a path to the node */
            aux_adj = graphGetAdj(g); 
            
			for(t = aux_adj[help_w->vertex]; t != NULL; t = nextNode(t)) {
                aux = (g_data *)getData(t);
                w = aux->vertex;
                aux_w = aux->weight;
                          
                /* aux_w <= max_step because max_step depends on the problem - we can't go through a connection that's bigger than allowed */
				if(aux_w <= max_step && wt[w] > (wt[help_w->vertex] + aux_w)) {
					
					wt[w] = (wt[help_w->vertex] + aux_w);
					
                    h_pos = findQueueV(q, w);
                    change_data->vertex = w;
                    change_data->weight = wt[w];
                    changeQueueData(q, h_pos, change_data); /* Change weight of vertex w in heap */
                    fixUp(q, h_pos, compWeight);
                    
					st[w] = help_w->vertex;
				}
			}
		}
        free(help_w);
	}
    
    freeHeap(q);
    
    return;
}

/* Write the first line for each problem in the solution file, since it's different from all the others */
void writefirstOutput(FILE * fp, char * word, int cost) { 
	fprintf(fp, "%s %d\n", word, cost); /* Write origin word and cost */
    return;
}

void writeOutput(FILE * fp, char * word) { 
    fprintf(fp, "%s\n", word);
    return;
}

/* Frees a Matrix, being the second dimension size passed as an array */
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

