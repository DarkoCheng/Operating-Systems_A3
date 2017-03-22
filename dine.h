#ifndef P1_HEADER_
#define P1_HEADER_

/*
Function: create pthrea
In: void pointer for pthrea
out: none
*/
void *philosophers(void *pthread );
/*
Function: test if the philosopher has the chopsticks or not
in: 3 ints, seat number, chop number of both side
out: none
*/
void test(int seat,int chopstick_right, int chopstick_left);
/*
Function: pick up chopsticks
in: 3 ints as above
out: none
*/
void pickup(int seat, int chopstick_right, int chopstick_left);
/*
Function: put down chopsticks
in: 3 ints as above
out: none.
*/
void putdown(int seat, int chopstick_right, int chopstick_left );


#endif
