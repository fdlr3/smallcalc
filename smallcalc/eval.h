#ifndef EVAL_INCLUDED
#define EVAL_INCLUDED

#include "sya_queue.h"
#include "eval_stack.h"


eval_stack *conv_eval(queue *q, int *save_count);

double eval(eval_stack *t, int size);

double calc_2(const char *op, double con1, double con2);
double calc_1(const char *op, double con);

#endif

