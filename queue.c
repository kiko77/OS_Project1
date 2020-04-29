#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int isfull(struct Queue *q){return ((q->b+1)%50 == q->f);}

int isempty(struct Queue *q){return (q->f == q->b);}

void push(struct Queue *q, int x){
	if(isfull(q)){exit(-1);}
	q->b = (q->b+1)%50;
	q->array[q->b] = x;
}
int pop(struct Queue *q){
	if(isempty(q)){return -1;}
	else{
		q->f = (q->f+1)%50;
		return (q->array[q->f]);
	}
}
