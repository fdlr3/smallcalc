#include <stdlib.h>
#include <string.h>
#include "sya_queue.h"

queue *create_queue() {
	queue *que = malloc(sizeof(queue));

	que->count = 0;
	que->s1 = create_stack();
	que->s2 = create_stack();

	return que;
}
void q_enqueue(queue *q, ops *o) {
	while (q->s1->count != 0) {
		s_push(q->s2, s_pop(q->s1));
	}

	s_push(q->s1, o);

	while (q->s2->count != 0) {
		s_push(q->s1, s_pop(q->s2));
	}
	q->count++;
}
ops *q_dequeue(queue *q) {
	if (q->s1->count > 0) {
		q->count--;
		return s_pop(q->s1);
	}
	else {
		return NULL;
	}
}
ops *q_peek(queue *q) {
	if (q->s1->count > 0) {
		return s_peek(q->s1);
	}
	else {
		return NULL;
	}
}
void free_queue(queue *q) {
	free_stack(q->s1);
	free_stack(q->s2);
	free(q);
}