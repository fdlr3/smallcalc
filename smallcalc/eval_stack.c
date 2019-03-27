#include "eval_stack.h"

#include <stdlib.h>
#include <string.h>

eval_stack *
create_eval_stack(int size) {
	eval_stack *st = malloc(sizeof(eval_stack));

	st->s = malloc(sizeof(eval_tok*) * size);

	st->count = 0;

	return st;
}

void 
eval_push(eval_stack *st, eval_tok *o) {
	st->s[st->count++] = o;
}

eval_tok *
eval_pop(eval_stack *st) {
	eval_stack *op = NULL;
	if (st->count > 0) {
		op = st->s[st->count - 1];
		st->count--;
		st->s[st->count] = NULL;
	}
	return op;
}

eval_tok *
eval_peek(eval_stack *st) {
	if (st->count <= 0) {
		return NULL;
	}
	return st->s[st->count - 1];
}

void 
free_eval_stack(eval_stack *st) {
	for (int i = 0; i < st->count; i++) {
		free(st->s[i]);
	}
	free(st->s);
	free(st);
}

void free_eval_operator(eval_tok *o) {
	if (o->op && o) {
		free(o->op);
		free(o);
	}
	else {
		printf("Free failed in function free_eval_operator\m");
	}
}

eval_tok *create_eval_num(double num) {
	eval_tok *eval = malloc(sizeof(eval_tok));
	eval->type = EVAL_NUM;
	eval->val = num;
	return eval;
}

double get_number_eval(eval_tok *o) {
	double val = o->val;
	free(o);
	return val;
}