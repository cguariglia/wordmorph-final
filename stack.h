#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct _stack stack;

typedef void * Item;

stack *initStack();
int isEmpty(stack *s);
void push(stack **s, Item insert);
Item pop(stack **s);
void clearStack(stack *s);

#endif
