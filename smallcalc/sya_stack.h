#ifndef SYA_STACK_INCLUED
#define SYA_STACK_INCLUED

#define MAX_STACK_SIZE 56

#include "tokenizer.h"

typedef struct {
	ops **s;
	unsigned int count;
} stack;


stack *create_stack();
void s_push(stack *st, ops *o);
ops *s_pop(stack *st);
ops *s_peek(stack *st);
void free_stack(stack *st);

#endif
