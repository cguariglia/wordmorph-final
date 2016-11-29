#ifndef LISTS_H
#define LISTS_H

typedef struct _stack stack;

typedef int Item;

stack *initStack();
int isEmpty(stack *s);
void push(stack **s, Item insert);
Item pop(stack **s);
void clearStack(stack *s);

#endif
