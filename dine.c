/*CIS3110 Assignment 3


References: I readed pseude code on page 228 from textbook
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 
#include "dine.h"        
     
#define eating 0
#define thinking 1

int a =0; // philosopher
int b =0; // time
int f[20];
pthread_mutex_t d[50];
pthread_cond_t e;
int c [100]; // state
int totalEat;
int eaten = 0;

int main(int argc, char * argv[])
{
	pthread_t pthread[a];
    pthread_mutex_init(&d[50], NULL);
    pthread_cond_init(&e, NULL);
// user input the number of philosophers and each one 
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    if (argc != 3)
    {
        printf("You have inputed the wrong command.\n");
        exit(1);
    }
    if (a <= 2)
    {
        printf("The number of philosophers should larger than 2.\n");
        exit(1);
    }
    if (b < 1 || b > 1000)
    {
        printf("The number of times each philosopher should eat should between 1 - 1000\n");
        exit(1);
    }
 	
 	totalEat = a*b;
 // create pthread
	for(long i =0; i< a; i++)
	{
		pthread_create(&pthread[i], NULL, philosophers, (void *)i );
	}
 // free and wait for other
	
	for(int i=0; i< a; i++)
	{
		pthread_join (pthread[i], NULL);
	}
    pthread_exit(NULL);
}

// pthread
void * philosophers(void *pthread)
{
	int seat;
	int chopstick_left;
	int chopstick_right;
	seat = (long)pthread;
	c[seat] = thinking;

	printf(" seat: (thinking) %d\n", seat+1);
	chopstick_right = (seat + 1)% a;
	
	chopstick_left = (seat + (a-1))% a ;
	
	while( eaten < totalEat)
	{	
		if (f[seat] < b){
		
			pickup(seat, chopstick_right, chopstick_left);
			sleep(1);
		}
		sleep(1);		
	}
	pthread_exit(NULL);
}
// make each philosopher to pick left-side choptick and right-side chopstick
void pickup(int seat, int chopstick_right, int chopstick_left)
{	
	pthread_mutex_lock(&d[chopstick_left]);
	pthread_mutex_lock(&d[chopstick_right]);
//	sleep(1);
	test(seat, chopstick_right, chopstick_left);
	if(c[seat] != eating)
	{
		pthread_cond_wait(&e ,&d[chopstick_left]);
		pthread_cond_wait(&e ,&d[chopstick_right]);				
	}
}
// unlock chopsticks 
void putdown(int seat, int chopstick_right, int chopstick_left)
{	
	c[seat] = thinking;

	pthread_mutex_unlock( d);	
	pthread_mutex_unlock(&d[chopstick_left]);	
	pthread_mutex_unlock(&d[chopstick_right]);	
	
	//	c[seat] = thinking;				
}
// test does philosopher allow to eat or not
void test(int seat, int chopstick_right, int chopstick_left)
{
	if((c[(seat + (a -1))%a] != eating) && (c[(seat + 1)%a] != eating) && (c[seat] == thinking))
	{	
		c[seat] = eating;
		f[seat]++;
		eaten++;
		printf("        philosopher %d eating\n", seat+1);	
		putdown(seat, chopstick_right, chopstick_left);
		printf("philosopher %d thinking\n", seat+1);				
	}
}


