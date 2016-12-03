#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "datastructs.h"

/* In this file:
 * Functions that wouldn't fit in any other file, mostly related to dealing with the files themselves. */

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

/* Binary searches. */
int binarySearch(char *array[], int size, char *value) {
	int left, right, middle;
	
	left = 0;
	right = size;
	
	while(left <= right) {
		middle = (right + left) / 2;
		
		if(strcmp(array[middle], value) > 0)
			right = middle - 1;
		else if(strcmp(array[middle], value) < 0)
			left = middle + 1;
		else 
			return middle;
	}
	
	return -1;
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

void lowerWeight(queue *q, int idx, Item new_weight) {
    g_data _data = {0, 0};
    g_data *data = &_data;
    changeQueueData(&q, idx, data);
    return;
}

/*Write the first line for each problem in the solution file */
void writefirstOutput(FILE * fp, char * word, int cost) { 
	
    fprintf(fp, "\n%s %d\n", word, cost); /* Write origin word and cost*/

    return;
}

void writeOutput(FILE * fp, char * word) { 
    
    fprintf(fp, "%s\n", word); 

    return;
}

void dijkstra(graph *g, int s, int *st, int *wt) {
	int *help_w;
    int w, verts;
    g_data _v = {0, 0};
	g_data *v, *aux;
    queue *q;
    node **aux_adj;
	node *t;
    
    v = &_v;
    verts = graphGetVert(g);
	q = queueInit(verts);

	for(v->vertex = verts - 1; v->vertex >= 0; v->vertex--) {
		st[v->vertex] = -1;		
		wt[v->vertex] = MAX_WT;
		v->weight = MAX_WT;	
		insertInHeap(q, v, compInts);	
	}
		
	wt[s] = 0;
	
    fixLowerPriority(q, verts - 1 - s, 0, lowerWeight, compInts);
 
	while(!emptyHeap(q)) {
        help_w = removeHeap(q);
        v->vertex = *help_w;
        
		if(wt[v->vertex] != MAX_WT){
            aux_adj = graphGetAdj(g);
            
			for(t = aux_adj[v->vertex]; t != NULL; t = nextNode(t)) {
                aux = getData(t);
                w = aux->vertex;
                
				if(wt[w] > (wt[v->vertex] + aux->weight)) {
					wt[w] = (wt[v->vertex] + aux->weight);
                    fixLowerPriority(q, verts - 1 - w, &wt[w], lowerWeight, compInts);
					st[w] = v->vertex;
				}
			}
		}
	}

    return;
}


/* Returns how many different letters there are in different words */
int calculateDifferentLetters(char *word1, char *word2) {
    int i, different_letters = 0;
    
    for(i = 0; i < strlen(word1); i++)
        if(word1[i] != word2[i])
            different_letters += 1;
    
    return different_letters;
}

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
