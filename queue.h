struct Queue{
	int array[50];
	int f;
	int b;
};

int isfull(struct Queue *q);
int isempty(struct Queue *q);
void push(struct Queue *q, int x);
int pop(struct Queue *q);
