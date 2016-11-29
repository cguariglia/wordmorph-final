#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>

#define MAX_STRING 100

void problemCounter(FILE *prob, int *problem_array);
void initDictionary(FILE *dic, FILE *prob);
void problemSolver(FILE *dic, FILE *prob);
void wordReader(FILE *input, char **output[MAX_STRING], int *size_array);
void initDictionary(FILE *prob, FILE *dic, char **dictionary[MAX_STRING], int *to_solve, int *word_count);

#endif
