#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define MAX_STRING 100

void * allocate(size_t);
FILE * fcheck(char *, char *);
char* outputFileExtension(char * name_input);

#endif
