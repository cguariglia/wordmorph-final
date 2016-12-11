#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "datastructs.h"

#define MAX_STRING 100

void * allocate(size_t);
FILE * fcheck(char *, char *);
char* outputFileExtension(char * name_input);

int calculateDifferentLetters(char *word1, char *word2, int cost);
int compInts(Item i1, Item i2);
int compWeight(Item item1, Item item2);

void lowerWeight(queue *q, int idx, Item new_weight);
void dijkstra(graph *g, int s, int end, int max_step, int *st, int *wt);

void writefirstOutput(FILE * fp, char * word, int cost);
void writeOutput(FILE * fp, char * word);

void freeMatrix(char ***mat, int *size, int init_size);

#endif

