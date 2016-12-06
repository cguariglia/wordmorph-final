#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "datastructs.h"

#define MAX_STRING 100

void * allocate(size_t);
FILE * fcheck(char *, char *);
char* outputFileExtension(char * name_input);
int binarySearch(char *array[], int size, char *value);

void writefirstOutput(FILE * fp, char * word, int cost);
void writeOutput(FILE * fp, char * word);
int compWeight(Item item1, Item item2);

void dijkstra(graph *g, int s, int *st, int *wt);
void lowerWeight(queue *q, int idx, Item new_weight);
int compInts(Item i1, Item i2);
int calculateDifferentLetters(char *word1, char *word2);
void freeMatrix(char ***mat, int *size, int init_size);

#endif

