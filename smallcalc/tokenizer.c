
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include <math.h>


//-----------------TOKENIZE LOGIC-----------------
ops *
tokenize(char *c) {
	ops *op = malloc(sizeof(ops));

	op->value = c;
	int found = 0;

	//if its a token
	if (!isdigit(c[0])) {
		size_t len = strnlen(c, MAX_TOKEN_LENGTH);
		for (int i = 0; i < token_co; i++) {
			if (tokens[i].len == len &&
				strcmp(tokens[i].name, c) == 0) {
				//check for constants
				if (strcmp(tokens[i].name, "e") == 0) {
					op->value = malloc(CONSTANT_LEN);
					memcpy(op->value, Stringify(C_E), CONSTANT_LEN);
					free(c);
				}
				else if (strcmp(tokens[i].name, "pi") == 0) {
					op->value = malloc(CONSTANT_LEN);
					memcpy(op->value, Stringify(C_PI), CONSTANT_LEN);
					free(c);
				}
				op->type = tokens[i].type;
				op->prec = tokens[i].prec;
				op->asoc = tokens[i].asoc;
				found = 1;
				break;
			}
		}
	}
	//if its a number
	else if (is_number(c)) {
		op->asoc = -1;
		op->prec = NONE_P;
		op->type = NUMBER;
		found = 1;
	}

	if (found) {
		return op;
	}
	else {
		free(c);
		free(op);
		return NULL;
	}
		

}

int is_number(const char *str)
{
	while (*str != '\0') {
		if ((*str >= '0' && *str <= '9') || *str == '.') {
			*(str++);
		}
		else {
			return 0;
		}
	}
	return 1;
}



void free_ops(ops *o, int remove) {
	//if remove true frees string
	if (remove) {
		free(o->value);
	}
	free(o);
}

char *next_token(char *exp, char **save) {
	char *pt = exp, *tok = NULL;
	char buffer[MAX_TOKEN_LENGTH] = {0};
	unsigned int found = 0;

	if (exp == NULL) {
		pt = *save;
	}

	//ignore space OR column
	while (*pt == ' ' || *pt == ',') {
		pt++;
	}

	//check for tokens
	if (!isdigit(*pt)) {
		for (int i = 0; i < token_co; i++) {
			if (*pt == tokens[i].name[0]) {
				if (tokens[i].len > 1) {
					size_t st = 1, en = tokens[i].len - 1;
					while (st <= en) {
						if (*++pt != tokens[i].name[st++]) {
							return NULL;
						}
					}
					strncpy(buffer, tokens[i].name, tokens[i].len);
					buffer[tokens[i].len] = '\0';
					found = 1;
					break;
				}
				//token size is only 1
				else {
					buffer[0] = tokens[i].name[0];
					buffer[1] = '\0';
					found = 1;
					break;
				}
			}
		}
	}
	//check for numbers
	else if (isdigit(*pt)) {
		size_t i = 0;

		while (isdigit(*pt) || *pt == '.') {
			buffer[i++] = *pt++;
		}

		if (i > 0) {
			buffer[i] = '\0';
			found = 1;
			//need to recall one pointer back because of upper while loop
			*pt--;
		}
	}

	//if a token is found locate memory and return it
	if (found) {
		size_t tok_len = strnlen(buffer, MAX_TOKEN_LENGTH);
		tok = malloc(tok_len + 1);
		memcpy(tok, buffer, tok_len + 1);
	}

	*save = pt + 1;
	return tok;
}

