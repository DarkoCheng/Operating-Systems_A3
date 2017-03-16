CIS3110 Assignment 3

Author: 

References: I have learned the pseudocode from the textbook about part one with dining philosopher's problem. 
            About part 2 I basically followed the Ta's instruction to finish the part 2.

Note: there is no error and warning use flag -std=c99, -Wall and -pedantic under Ubuntu 15.10.
      to compile my program and run it simply type make and follow instructions below.

For part one: 
What this program can do?
1, solve  the  dining  philosopher's  problem.

What this program cannot do?
1, the user must input 2 commond line argunments, cannot be more or less.
2, the input must be numbers, cannot be others.
3, sometimes pthread goes to fast so the program might be wrong up (when there is 5 people, there maybe a case that 3 people eat together), but it barely happens.

For part two: 
What this program can do?
1, I finished first fit and worst fit and best fit. I used array to simulate the memory.
2, the user need to give the process file by commond line argunment.
3, I got right answer from the example given by prof on the courseLink. 

What this program cannot do?
1, this program cannot do next fit. But if I have time I can definitely to do that, because basically all I need to change is the if and else if statment. Use different conditions I can do next fit.
2, my program might not insert process when there is only 2 process in the memory and the hole is between the memory, I found this problem when I was doing best fit because there is a case for that, but for the example given by prof there is no such case for the first fit and worst fit.

