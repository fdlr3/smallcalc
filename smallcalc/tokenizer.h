#ifndef _TOKENIZER_H_INCLUDED_
#define _TOKENIZER_H_INCLUDED_

//------------TOKENIZER------------

#define STR_HELPER(x) #x
#define Stringify(x) STR_HELPER(x)

#define MAX_TOKEN_LENGTH 20
#define C_PI 3.141592653589793238
#define C_E  2.718281828459045235
#define CONSTANT_LEN 21

typedef enum { L_AS = 1, R_AS = 2, NONE_P = 3 } associativity;
typedef enum { FUNCTION = 1, NUMBER = 2, OPERATOR = 3, LEFT_P = 5, RIGHT_P = 6 } token_type;

typedef struct {
	const char *name;
	const int len, prec;
	const associativity asoc;
	const token_type type;
} token;

typedef struct {
	char *value;
	int prec;
	associativity asoc;
	token_type type;
} ops;

static token tokens[] = {
	{ "+", 1, 2, L_AS, OPERATOR },
	{ "-", 1, 2, L_AS, OPERATOR },
	{ "/", 1, 3, L_AS, OPERATOR },
	{ "*", 1, 3, L_AS, OPERATOR },
	{ "^", 1, 4, R_AS, OPERATOR },
	{ "sin", 3, -1, NONE_P, FUNCTION },
	{ "cos", 3, -1, NONE_P, FUNCTION },
	{ "tan", 3, -1, NONE_P, FUNCTION },
	{ "arccos", 3, -1, NONE_P, FUNCTION },
	{ "arcsin", 3, -1, NONE_P, FUNCTION },
	{ "arctan", 3, -1, NONE_P, FUNCTION },
	{ "mod", 3, -1, NONE_P, FUNCTION },
	{ "sqrt", 3, -1, NONE_P, FUNCTION },
	{ "abs", 3, -1, NONE_P, FUNCTION },
	{ "max", 3, -1, NONE_P, FUNCTION },
	{ "(", 1, -1, NONE_P, LEFT_P },
	{ ")", 1, -1, NONE_P, RIGHT_P },
	{ "x", 1, -1, NONE_P, NUMBER },
	{ "e", 1, -1, NONE_P, NUMBER },
	{ "pi", 2, -1, NONE_P, NUMBER },
	{ "log", 3, -1, NONE_P, FUNCTION },
	{ "ln", 2, -1, NONE_P, FUNCTION }
	};

static unsigned int token_co = sizeof(tokens) / sizeof(tokens[0]);

char *next_token(char *exp, char **save);
ops *tokenize(char *c);
int is_number(const char *str);
void free_ops(ops *o, int remove);




#endif