all: hole dine

hole: holes.c
		gcc -Wall -pedantic -std=c99 holes.c -o hole

dine: dine.c
		gcc -Wall -pedantic -std=c99 -pthread dine.c -o dine
clean:
	$(RM) myprog
