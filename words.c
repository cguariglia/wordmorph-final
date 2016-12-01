#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "datastructs.h"

/* In this file:
 * Functions that are directly linked to solving the given problem. */

/* Check which graphs need to be built based upon the problem file. Also max weight */
void problemCounter(FILE *prob, int *problem_array) {
	char aux1[MAX_STRING], aux2[MAX_STRING];
	int max_change, i;
	
	for(i = 0; i < MAX_STRING; i++)
		problem_array[i] = 0;
	
	while(fscanf(prob, "%s %s %d", aux1, aux2, &max_change) == 3) {
        if(max_change > problem_array[strlen(aux1)])
		    problem_array[strlen(aux1)] = max_change; /* This array determines which graphs actually get built */
    }
	
    rewind(prob); /* We're going to use it later, so might as well bring it back to the beginning now. */
    
	return;	
}

void wordCounter(FILE *input, int *occurrences, int *problems) {
	int i;
	char word[MAX_STRING];
	
	for(i = 0; i < MAX_STRING; i++)
		occurrences[i] = 0;
	
	while(fscanf(input, "%s", word) == 1) {
		if(problems[strlen(word)] > 0) /*If the problem file involves a word of that size */
			occurrences[strlen(word)] += 1; 
	}
		
	return;
}

/* Copies word from file to 3D matrix and sorts individual arrays */
void wordReader(FILE *input, char **output[MAX_STRING], int *size_array) {
	char word[MAX_STRING];
	int index, i, length;

	int aux_array[MAX_STRING];
    
	/* Allocates each segment of the array depending on how many words of that length there are.*/
	for(i = 0; i < MAX_STRING; i++) {
		if(size_array[i] != 0) {
			output[i] = (char **)allocate(sizeof(char *) * size_array[i]);
			aux_array[i] = size_array[i];
		}
	}
    
    rewind(input);
	
	while(fscanf(input, "%s", word) == 1) {
		length = strlen(word);

		index = size_array[length] - aux_array[length];
		
		/* Copy word to word array */
		if(size_array[length] != 0) {
			output[length][index] = (char *)allocate(sizeof(char) * (length + 1));
			strcpy(output[length][index], word);
			aux_array[length] -= 1;
		}
	}
	
    /* Sorts each array of the matrix */
	/*for(i = 0; i < MAX_STRING; i++) {
		if(size_array[i] != 0) {
			quickSort(output[i], 0, size_array[i] - 1);
		}
	}*/
		
	return;
}

void initDictionary(FILE *prob, FILE *dic, char **dictionary[MAX_STRING], int *to_solve, int *word_count) {
	
	problemCounter(prob, to_solve);
	wordCounter(dic, word_count, to_solve);
	wordReader(dic, dictionary, word_count);
    
	return;
}

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

void initGraphs(graph **all_graphs, int *max_change, int *size_array, char ***dict) {
    int i, j, n, word_weight;
    g_data _insert_data = {0, 0};
    g_data *insert_data = &_insert_data;
    node **aux_list;
    
    for(i = 0; i < MAX_STRING; i++) {
        if(max_change[i] > 0) {
            all_graphs[i] = graphInit(size_array[i]);
            aux_list = graphGetAdj(all_graphs[i]);
     
            
            for(j = 0; j < size_array[i]; j++) {
                for(n = 0; n < size_array[i]; n++) {
                    word_weight = calculateDifferentLetters(dict[i][j], dict[i][n]);
                    insert_data->weight = word_weight;
                    insert_data->vertex = n;
                    if(word_weight > 0 && word_weight <= max_change[i]) {
                        aux_list[j] = insertSortedList(aux_list[j], insert_data, compWeight);
						
                    }
                }
            }
        }
    
    }
    
    
    
    return;
}

void freeAllGraphs(graph **all_graphs/*, int *size_array*/) {
    int i;
    
    for(i = 0; i < MAX_STRING; i++) {
        free(all_graphs[i]);
    }
        
    free(all_graphs);
    
    return;
}

/* Second read of the problems file, in which the problems are actually solved and written to the output file.
 * Basically the main function of the whole program. */
void problemSolver(FILE *dic, FILE *prob) {
    char aux1[MAX_STRING], aux2[MAX_STRING];
    char **dict[MAX_STRING];
	int changed_letters[MAX_STRING], word_count[MAX_STRING];
    int max_change;
    graph **all_graphs;

    initDictionary(prob, dic, dict, changed_letters, word_count);
    
    
    all_graphs = (graph **)allocate(sizeof(graph *) * MAX_STRING);
    if (all_graphs == NULL) exit(0);
   
    initGraphs(all_graphs, changed_letters, word_count, dict);
   

	freeAllGraphs(all_graphs);
    
    /*
    while(fscanf(prob, "%s %s %d", aux1, aux2, &max_change) == 3) {
        
    }*/
    
    return;
}

/*

void solveAllProblems(graph **all_graphs)
{
	int i;
	
	for(i = 0; i < MAX_STRING; i++) { /* Para cada problema */ 
	
	
/*	
	} 
}
*/


void solveProblem(graph *g, ) /*Resolver para 1 palavra - ou seja para so 1 linha do ficheiro de problemas */
{
	
	
	
	
	
} 


void dijkstra(graph *g, int s, int *st, int *wt) {
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



