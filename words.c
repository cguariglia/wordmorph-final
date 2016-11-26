#include <stdlib.h>
#include <stdio.h>

/* Check which graphs need to be built based upon the problem file */
void problemCounter(FILE *prob, int *problem_array) {
	char aux1[MAX_STRING], aux2[MAX_STRING];
	int option, i;
	
	for(i = 0; i < MAX_STRING; i++)
		problem_array[i] = 0;
	
	while(fscanf(prob, "%s %s %d", aux1, aux2, &option) == 3)
		problem_array[strlen(aux1)] = 1;		
	
	return;	
}
