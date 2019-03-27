#ifndef EVAL_STACK_INCLUED
#define EVAL_STACK_INCLUED

typedef enum { EVAL_OP = 1, EVAL_NUM = 2, EVAL_FUNC = 3 } eval_type;

typedef struct {
	double val;
	char *op;
	eval_type type;
} eval_tok;

typedef struct {
	eval_tok **s;
	unsigned int count;
} eval_stack;

void free_eval_operator(eval_tok *o);
eval_tok *create_eval_num(double num);
double get_number_eval(eval_tok *o);

eval_stack *create_eval_stack(int size);
void eval_push(eval_stack *st, eval_tok *o);
eval_tok *eval_pop(eval_stack *st);
eval_tok *eval_peek(eval_stack *st);
void free_eval_stack(eval_stack *st);

#endif
