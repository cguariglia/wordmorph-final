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
		
	return;
}

void initDictionary(FILE *prob, FILE *dic, char **dictionary[MAX_STRING], int *to_solve, int *word_count) {
	
	problemCounter(prob, to_solve);
	wordCounter(dic, word_count, to_solve);
	wordReader(dic, dictionary, word_count);
    
	return;
}

void initGraphs(graph **all_graphs, int *max_change, int *size_array, char ***dict) {
    int i, j, n, word_weight, weight;
    node **adj_list;
    
    /* fixed bug. bons algoritmos e felizes estruturas de dados */
    
    for(i = 0; i < MAX_STRING; i++) {
        if(max_change[i] > 0) {    
            all_graphs[i] = graphInit(size_array[i]);
            adj_list = graphGetAdj(all_graphs[i]);
            
            /* actually build the adj linked list for each word of i letters */
            for(j = 0; j < size_array[i]; j++) {
                for(n = 0; n < j; n++) {
                    word_weight = calculateDifferentLetters(dict[i][j], dict[i][n]);
                    
                    if(word_weight > 0 && word_weight <= max_change[i]) {
                        weight = word_weight * word_weight;
                        
                        adj_list[j] = insertSortedList(adj_list[j], newGData(weight, n), compWeight);
                        adj_list[n] = insertSortedList(adj_list[n], newGData(weight, j), compWeight);
                    }
                }
            }
            /*printf("-- finished doing adj for len %d --\n", i);
            
            for(j = 0; j < size_array[i]; j++) {
                printf("adj list for word %s:\n", dict[i][j]);
                if (adj_list[j] == NULL) printf("null\n");
                for(aux = adj_list[j]; aux != NULL; aux = nextNode(aux)) {
                    printf(" -> %s", dict[i][((g_data *)getData(aux))->vertex]); 
            }
                printf("\n");*/
        }
    }
    
    return;
}

void printPath(FILE *output, int w_size, int *st, int origin_v, int final_v, char **dic[MAX_STRING], int cur) {
    /*Retrace path to origin vertice*/
    if(st[cur] == -1) return;
	else if(cur != -1 && st[cur] != -1) {
	    /*Print word correspondent to vertex aux*/
        printPath(output, w_size, st, origin_v, final_v, dic, st[cur]);
        writeOutput(output, dic[w_size][cur]);
	}

	fprintf(output, "\n"); 

    return;
}

void solveAllProblems(FILE *input, FILE *output, graph **all_graphs, char **dictionary[MAX_STRING], int *size_array) {
	char aux1[MAX_STRING], aux2[MAX_STRING];
	int cost = 0, length = 0, i, verts, origin_v = 0, final_v = 0;
    int *wt, *st;
	
	
    /* Dado os elementos de um grafo - ver qual e o vertice origem - palavra do ficheiro de prob e o seu n de vertice no grafo*/
	/* Com base nessa valor do vertice - correr o dijkstra que gera o caminho*/
	/* Imprimir no ficheiro de saida as palavras do caminho com base nos valores no vetor s*/

    /* Para cada problema */ 
    
    rewind(input);
	
	while(fscanf(input, "%s %s %d", aux1, aux2, &cost) == 3) {
        length = strlen(aux1);
        
        for(i = 0; i < size_array[strlen(aux1)]; i++) {
            if(strcmp(aux1, dictionary[length][i]) == 0)
                origin_v = i;
            else if(strcmp(aux2, dictionary[length][i]) == 0)
                final_v = i;
        }
        
        verts = graphGetVert(all_graphs[length]);
        
        wt = (int *)allocate(verts * sizeof(int));
        st = (int *)allocate(verts * sizeof(int));
        
	    dijkstra(all_graphs[length], origin_v, st, wt);
        
        writefirstOutput(output, dictionary[length][origin_v], cost); /* Since the first line is special */			
        printPath(output, length, st, origin_v, final_v, dictionary, st[final_v]);
        writeOutput(output, dictionary[length][final_v]);
        
        free(wt);
        free(st);
    }
}

void freeAllGraphs(graph **all_graphs, int *size_array) {
    int i;
    
    for(i = 0; i < MAX_STRING; i++)
        if(size_array[i] != 0)
            freeGraph(all_graphs[i], free);
        
    free(all_graphs);
    
    return;
}

/* Second read of the problems file, in which the problems are actually solved and written to the output file.
 * Basically the main function of the whole program. */
void problemSolver(FILE *dic, FILE *prob, FILE *path) {
    char **dict[MAX_STRING];
	int changed_letters[MAX_STRING], word_count[MAX_STRING];
    graph **all_graphs;

    initDictionary(prob, dic, dict, changed_letters, word_count);
    
    all_graphs = (graph **)allocate(sizeof(graph *) * MAX_STRING);
 
    initGraphs(all_graphs, changed_letters, word_count, dict);   
    solveAllProblems(prob, path, all_graphs, dict, word_count);
    /*Isto da problemas
    freeAllGraphs(all_graphs, word_count);
    freeMatrix(dict, word_count, MAX_STRING);*/ 
    
    return;
}
