#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sya.h"


//start writing what type of token it is because you can see it here
queue *
sy_alghoritm(char * expr)
{
	queue* q = create_queue(MAX_STACK_SIZE);
	stack *s = create_stack(MAX_STACK_SIZE);
	char *save = NULL, *tok = NULL;
	unsigned int first = 1;


	while ((tok = next_token(expr, &save)) != NULL) {
		ops *op = tokenize(tok);
		if (op == NULL) {
			return q;
		}

		//if first change pointer to NULL
		if (first) {
			expr = NULL;
			first = 0;
		}

		//if token is a number
		if (op->type == NUMBER) {
			q_enqueue(q, op);
		}

		//if token is a function
		if (op->type == FUNCTION) {
			s_push(s, op);
		}

		//if token is an operator
		if (op->type == OPERATOR) {
			while (
				s->count > 0 &&
				//there is a function on top of stack
				(s_peek(s)->type == FUNCTION ||
					//there is an operator with a larger precedence
				(s_peek(s)->type == OPERATOR && s_peek(s)->prec > op->prec) ||
					//there is an operator with equal precedence AND is left associative
					(s_peek(s)->type == OPERATOR && s_peek(s)->prec == op->prec && s_peek(s)->asoc == L_AS)) &&
				//top operator is not left parenthesis
				s_peek(s)->type != LEFT_P) {
				//pop operators from the operator stack onto the output queue
					q_enqueue(q, s_pop(s));
			}
			//push it onto the operator stack.
			s_push(s, op);
		}

		//if token is a left parenthesis 
		if (op->type == LEFT_P) {
			s_push(s, op);
		}

		//if token is a right parenthesis 
		if (op->type == RIGHT_P) {
			//while its not a left parenthesis
			while (s_peek(s)->type != LEFT_P) {
				q_enqueue(q, s_pop(s));
			}
			//TODO if the stack runs out without finding a left paren, then there are mismatched parentheses.

			//if there is left parenthesis on top discard it 
			if (s_peek(s)->type == LEFT_P) {
				free_ops(s_pop(s), 1);
			}
			free_ops(op, 1);
		}

		//if there are no more tokens to read
		if (*save == '\0') {
			//while there are still operators in the stack
			while (s->count > 0) {
				q_enqueue(q, s_pop(s));
			}
			break;
		}
	}
	free_stack(s);
	return q;
}

