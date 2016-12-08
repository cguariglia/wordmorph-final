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

/* Returns how many different letters there are in two words */
int calculateDifferentLetters(char *word1, char *word2) {
    int i, different_letters = 0;
    
    for(i = 0; i < strlen(word1); i++)
        if(word1[i] != word2[i])
            different_letters += 1;
    
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

/* Lowers something's priority (in this case, by lowering its weight */
void lowerWeight(queue *q, int idx, Item new_weight) {
    g_data _data = {0, 0};
    g_data *data = &_data;
    
    changeQueueData(q, idx, data);
    return;
}

void dijkstra(graph *g, int s, int end, int *st, int *wt) {
    int w, vertex, verts, aux_w, h_pos;
    queue *q;
    node **aux_adj;
	node *t;
    g_data _change_data = {0, 0};
	g_data *aux, *help_w, *change_data = &_change_data;
    
    /* Inicializar a queue / heap com todos os pesos no maximo */
    verts = graphGetVert(g); 
	q = queueInit(verts);
	for(vertex = 0; vertex < verts; vertex++) {
		st[vertex] = -1;
		wt[vertex] = MAX_WT;
		insertInHeap(q, newGData(MAX_WT, vertex), compWeight); 
	}
    
    /* Por a prioridade do ponto de partida a 0 */
	wt[s] = 0;
    change_data->vertex = s;
    change_data->weight = 0;
	changeQueueData(q, s, change_data); /* Mudar o peso do vertice s no vetor da queue*/
	fixUp(q, s, compWeight);

	while(!emptyHeap(q)) {
        help_w = (g_data *)removeHeap(q, compWeight);
        
        if(help_w->vertex == end)
            break;
            
		if(wt[help_w->vertex] != MAX_WT) {
            
            aux_adj = graphGetAdj(g); 
			for(t = aux_adj[help_w->vertex]; t != NULL; t = nextNode(t)) {
                aux = (g_data *)getData(t);
                w = aux->vertex;
                aux_w = aux->weight;
				
                          
				if(wt[w] > (wt[help_w->vertex] + aux_w)) {
					wt[w] = (wt[help_w->vertex] + aux_w);
					
                    h_pos = findQueueV(q, verts, w); /*Encontrar pos da heap com o vertice w para lhe alterar o peso */
                    change_data->vertex = w;
                    change_data->weight = wt[w];
                    changeQueueData(q, h_pos, change_data);
                    fixUp(q, h_pos, compWeight);
                    
					st[w] = help_w->vertex;
				}
			}
		}
        
        free(help_w); /* free the helper pointer slave dude */
	}
    
    freeHeap(q);
    
    return;
}

/* Write the first line for each problem in the solution file, since it's different from all the others */
void writefirstOutput(FILE * fp, char * word, int cost) { 
	
    fprintf(fp, "%s %d\n", word, cost); /* Write origin word and cost */
    /* printf("%s %d\n", word, cost); */
    return;
}

void writeOutput(FILE * fp, char * word) { 
    
    fprintf(fp, "%s\n", word);
    /* printf("%s\n", word); */

    return;
}

/* Frees a whole matrix (but the size must be passed as an array) */
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

