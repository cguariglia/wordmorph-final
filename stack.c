#include <stdio.h>
#include <stdlib.h>
#include "lists.h"


struct _stack {
	Item data;
	struct _stack *next;
};


stack *initStack() {
	return NULL;
}


int isEmpty(stack *s) {
	return (s == NULL);
}


void push(stack **s, Item insert) {
	 stack *top = (stack *)malloc(sizeof(stack));
	 if(top == NULL)
		exit(0);
	 
	 top->data = insert;
	 top->next = *s;
	 *s = top;
	 
	 return;
}


Item pop(stack **s) {
	stack *aux;
	Item content;
	
	aux = *s;
	if(*s != NULL)
		*s = (*s)->next;
	
	content = aux->data;
	free(aux);
	
	return content;
}
	
	

void clearStack(stack *s) {
	stack *next;
	
	while(s != NULL) {
		next = s->next;
		free(s);
		s = next;
	}
	
	return;
}
