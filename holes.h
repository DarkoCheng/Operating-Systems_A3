#ifndef HOLES_HEADER_
#define HOLES_HEADER_

typedef struct queue{
	char number;
	int size;
	int kick;
	struct queue * next;
}queue;

queue * front = NULL;
queue * back = NULL;

typedef struct memory{
	char number;
	int size;
	int start;
	int age;
	int kick;
}memory;

/*
Function: main function for best fit
In: int, first time total number of process
out: right answer I assume.
*/
void bestFit(int counter);
/*
Function: delete element from queue
in: none.
out: none.
*/
void deQueue();
/*
Function: insert element into queue
in: all varaibles for queue struct
out; none.
*/
void enQueue(char number, int size, int hit);
/*
Function: print out the queue.
in: none.
out: none.
*/
void print();
/*
Function: get the first element of queue.
In: none
Out: none
*/
queue * first();
/*
Function: destroy the queue
In: none.
Out: none
*/
void destroy();
/*
Function: print out the load line
In: all varaibles need for the load line
Out: none
*/
void printMem(int a, int b, int c, int d);
/*
Function: main function for the first fit.
In: number of queue elements
Out: none
*/
void firstFit(int counter);
/*
Function: main function for worst fit.
In: number of queue.
Out: none
*/
void worstFit(int counter);
/*
Function: check if the queue is empty or not
In: none.
Out: none.
*/
int isEmpty();

#endif