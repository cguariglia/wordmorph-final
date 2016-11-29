#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define MAX_STRING 100

void * allocate(size_t);
FILE * fcheck(char *, char *);
char* outputFileExtension(char * name_input);
int binarySearch(char *array[], int size, char *value);
int calculateDifferentLetters(char *word1, char *word2);

#endif
