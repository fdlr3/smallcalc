#include <stdlib.h>
#include <string.h>
#include "sya_stack.h"

stack *
create_stack() {
	stack *st = malloc(sizeof(stack));
	st->s = malloc(sizeof(ops*) * MAX_STACK_SIZE);

	st->count = 0;

	return st;
}

void
s_push(stack *st, ops *o) {
	st->s[st->count++] = o;
}

ops *
s_pop(stack *st) {
	ops *op = NULL;
	if (st->count > 0) {
		op = st->s[st->count - 1];
		st->count--;
		st->s[st->count] = NULL;
	}
	return op;
}

ops *
s_peek(stack *st) {
	if (st->count <= 0) {
		return NULL;
	}
	return st->s[st->count - 1];
}

void
free_stack(stack *st) {
	for (int i = 0; i < st->count; i++) {
		free_ops(*(st->s), 1);
		st->s++;
	}
	free(st->s);
	free(st);
}