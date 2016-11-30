#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

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
		for(j = 0; j < size[i]; j++) {
			free(mat[i][j]);
		}
		if(size[i] != 0)
			free(mat[i]);
	}
	return;
}
