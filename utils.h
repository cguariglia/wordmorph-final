#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "stack.h"

#define MAX_STRING 100

void * allocate(size_t);
FILE * fcheck(char *, char *);
char* outputFileExtension(char * name_input);
int binarySearch(char *array[], int size, char *value);

int calculateDifferentLetters(char *word1, char *word2);
void freeMatrix(char ***mat, int *size, int init_size);

#endif
