#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sya.h"
#include "tokenizer.h"
#include "eval.h"
#include "eval_stack.h"

int main()
{

	char *asd = "e + 2";

	queue *q = sy_alghoritm(asd);

	int count = 0;
	eval_stack *toks = conv_eval(q, &count);
	double a = eval(toks, count);
	printf("%lf \n", a);




	getchar();
    return 0;
}

