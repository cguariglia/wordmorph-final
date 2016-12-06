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
    changeQueueData(&q, idx, data);
    return;
}

/*Write the first line for each problem in the solution file */
void writefirstOutput(FILE * fp, char * word, int cost) { 
	
    fprintf(fp, "\n%s %d\n", word, cost); /* Write origin word and cost*/
    printf("\n%s %d\n", word, cost);

    return;
}

void writeOutput(FILE * fp, char * word) { 
    
    fprintf(fp, "%s\n", word);
    printf("%s\n", word);

    return;
}

void dijkstra(graph *g, int s, int *st, int *wt) {
	g_data *help_w;
    int w, vertex, verts, aux_vertex, aux_w, total_weight = 0;
    queue *q;
    node **aux_adj;
	node *t;
	g_data * aux;


	verts = graphGetVert(g); 
	q = queueInit(verts);
	for(vertex = 0; vertex < verts; (vertex)++) {
		st[vertex] = -1;
		wt[vertex] = MAX_WT;
		insertInHeap(q, newGData(MAX_WT, vertex) , compWeight);  /* O mesmo raciocinio para a heap*/
	}
	
	
	wt[s] = 0;
	changeQueueData(&q, s, newGData(0, s));    /* Mudar o peso do vertice s no vetor da queue*/
	fixUp(q, s, compInts);
	/*Soo far soo bueno */
	
	while(!emptyHeap(q)) {
        help_w = (g_data *)removeHeap(q, compWeight);
        aux_vertex = help_w->vertex;
        
		if(wt[aux_vertex] != MAX_WT){
			aux_adj = graphGetAdj(g);
             
            for(t = aux_adj[aux_vertex]; t != NULL; t = nextNode(t)) {
                aux = (g_data *)getData(t);
                w = aux->vertex;
                aux_w = aux->weight;

                /*printf(" EStamos na lista de adj de:%d, no vertice:%d, que tem um peso:%d\n",aux_vertex,w, aux_w); */
               
				if(wt[w] > (wt[aux_vertex] + aux_w)) {
					wt[w] = (wt[aux_vertex] + aux_w);
                    changeQueueData(&q, s, newGData(wt[w], w));
                    fixUp(q, w, compInts);
					st[w] = aux_vertex;
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
