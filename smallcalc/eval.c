#include "eval.h"
#include <math.h>
#include <string.h>



double 
eval(eval_stack *t, int size) {
	eval_stack *s1 = create_eval_stack(size);
	eval_tok *op;

	while(s1->count != 1 || t->count > 0) {
		if (t->count > 0) {
			op = eval_pop(t);
		}
		else {
			op = eval_pop(s1);
		}

		//number
		if (op->type == EVAL_NUM) {
			eval_push(s1, op);
		}
		// +, - *, ^, /
		else if (op->type == EVAL_OP) {
			double val1 = get_number_eval(eval_pop(s1));
			double val2 = get_number_eval(eval_pop(s1));

			double result = calc_2(op->op, val1, val2);
			eval_tok *t = create_eval_num(result);
			eval_push(s1, t);
			free_eval_operator(op);
		}
		// sin, cos, tan, max, ln, log
		else if (op->type == EVAL_FUNC) {
			double val = get_number_eval(eval_pop(s1));

			double result = calc_1(op->op, val);
			eval_tok *t = create_eval_num(result);
			eval_push(s1, t);
			free_eval_operator(op);
		}
	}
	op = eval_pop(s1);
	double result = op->val;
	free(op);
	free_eval_stack(t);
	free_eval_stack(s1);
	return result;
}

eval_stack *
conv_eval(queue *q, int *save_count) {
	size_t size = q->count;
	eval_stack *st = create_eval_stack(size);
	eval_tok *tok;

	//convert to eval_toks
	ops *ops = NULL;
	for (int i = size-1; i >= 0; i--) {
		ops = q_dequeue(q);
		tok = malloc(sizeof(eval_tok));
		if (ops->type == NUMBER) {
			tok->val = atof(ops->value);
			tok->type = EVAL_NUM;
			free_ops(ops, 1);
		}
		else if(ops->type == OPERATOR){
			tok->op = ops->value;
			tok->type = EVAL_OP;
			free_ops(ops, 0);
		}
		else if (ops->type == FUNCTION) {
			tok->op = ops->value;
			tok->type = EVAL_FUNC;
			free_ops(ops, 0);
		}
		st->s[i] = tok;
		st->count++;
	}
	free_queue(q);

	*save_count = size;
	return st;
}

double 
calc_2(const char *op, double con1, double con2) {
	if (strcmp(op, "+") == 0) {
		return con1 + con2;
	}
	else if (strcmp(op, "-") == 0) {
		return con2 - con1;
	}
	else if (strcmp(op, "max") == 0) {
		return con1 > con2 ? con1 : con2;
	}
	else if (strcmp(op, "^") == 0) {
		return powl(con1, con2);
	}
	else if (strcmp(op, "/") == 0) {
		return con1 / con2;
	}
	else if (strcmp(op, "*") == 0) {
		return con1 * con2;
	}
}

double 
calc_1(const char *op, double con) {
	if (strcmp(op, "sin") == 0) {
		return sinf(con);
	}
	else if (strcmp(op, "cos") == 0) {
		return cosf(con);
	}
	else if (strcmp(op, "tan") == 0) {
		return tanf(con);
	}
	else if (strcmp(op, "log") == 0) {
		return log10(con);
	}
	else if (strcmp(op, "ln") == 0) {
		return log(con);
	}
}