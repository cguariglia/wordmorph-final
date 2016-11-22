#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
