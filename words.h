#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include "datastructs.h"

#define MAX_STRING 100

void problemCounter(FILE *prob, int *problem_array);
void initDictionary(FILE *prob, FILE *dic, char **dictionary[MAX_STRING], int *to_solve, int *word_count);
int compWeight(Item item1, Item item2);
void initGraphs(graph **all_graphs, int *max_change, int *size_array, char ***dict);
int compWeight(Item item1, Item item2);
void problemSolver(FILE *dic, FILE *prob);
void wordReader(FILE *input, char **output[MAX_STRING], int *size_array);
void wordCounter(FILE *input, int *occurrences, int *problems);
void initDictionary(FILE *prob, FILE *dic, char **dictionary[MAX_STRING], int *to_solve, int *word_count);
void problemSolver(FILE *dic, FILE *prob);

void dijkstra(graph *g, int s, int *st, int *wt);

void freeAllGraphs(graph **all_graphs, int *size_array);

#endif
