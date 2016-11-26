#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "graphs.h"

/* In this file:
 * Functions that are directly linked to solving the given problem. */

/* Check which graphs need to be built based upon the problem file */
void problemCounter(FILE *prob, int *problem_array) {
	char aux1[MAX_STRING], aux2[MAX_STRING];
	int max_change, i;
	
	for(i = 0; i < MAX_STRING; i++)
		problem_array[i] = 0;
	
	while(fscanf(prob, "%s %s %d", aux1, aux2, &max_change) == 3)
		problem_array[strlen(aux1)] = 1; /* This array determines which graphs actually get built */
	
    rewind(prob); /* We're going to use it later, so might as well bring it back to the beginning now. */
    
	return;	
}

void initDictionary(FILE *dic, FILE *prob) {
    int problem_array[MAX_STRING];
    
    problemCounter(prob, problem_array);
    /* Graph functions go here, probs */
}

/* Second read of the problems file, in which the problems are actually solved and written to the output file.
 * Basically the main function of the whole program. */
void problemSolver(FILE *prob, FILE* dic) {
    char aux1[MAX_STRING], aux2[MAX_STRING];
	int max_change;
    
    while(fscanf(prob, "%s %s %d", aux1, aux2, &max_change) == 3) {
        
    }
    
    return;
}
