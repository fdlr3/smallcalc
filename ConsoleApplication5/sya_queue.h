#ifndef SYA_QUEUE_INCLUED
#define SYA_QUEUE_INCLUED

#include "tokenizer.h"
#include "sya_stack.h"

typedef struct {
	stack *s1, *s2;
	unsigned int count;
} queue;

queue *create_queue();
void q_enqueue(queue *q, ops *o);
ops *q_dequeue(queue *q);
ops *q_peek(queue *q);
void free_queue(queue *q);



#endif

