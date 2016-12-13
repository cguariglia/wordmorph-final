#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include "datastructs.h"

#define MAX_STRING 100

void problemCounter(FILE *prob, int *problem_array);
void wordCounter(FILE *input, int *occurrences, int *problems);
void wordReader(FILE *input, char **output[MAX_STRING], int *size_array);

void initDictionary(FILE *prob, FILE *dic, char **dictionary[MAX_STRING], int *to_solve, int *word_count);


void initGraphs(graph **all_graphs, int *max_change, int *size_array, char ***dict);
void printPath(FILE *output, int w_size, int *st, int origin_v, int final_v, char **dic[MAX_STRING], int cur);
int calculateTotalCost(int *st, int final_v, char **dic);

void solveAllProblems(FILE *input, FILE *output, graph **all_graphs, char **dictionary[MAX_STRING], int *size_array);

void problemSolver(FILE *dic, FILE *prob, FILE *path);

void freeAllGraphs(graph **all_graphs);

#endif

