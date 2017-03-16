/*

*/
#include <stdlib.h>
#include "holes.h"
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[])
{
    int counter = 0;
    if (argc != 2)
    {
    	printf("wrong input\n");
    	exit(1);
    }
    FILE * op;
    op = fopen(argv[1], "r");
    if (op == NULL)
    {
    	printf("Fail to open the file %s\n", argv[1]);
        printf("The error is: %d\n",errno);
    	exit(1);
    }
    char * buffer;
    buffer = malloc(sizeof(char*));
    int size;
    char number;
    while (fgets(buffer, 50, op) != NULL) // read file line by line
    {
         sscanf(buffer, "%c %d", &number, &size);
         enQueue(number, size, 0);
         counter++;
    }
    printf("Below is first fit:\n");
    firstFit(counter);
    counter = 0;
    fclose(op);
    op = fopen(argv[1], "r");
    while (fgets(buffer, 50, op) != NULL)  // read file line by line
    {
        sscanf(buffer, "%c %d", &number, &size);
        enQueue(number, size, 0);
        counter++;
    }
    printf("\n\n\n\n\n\nBelow is worst fit:\n");
    worstFit(counter);
    counter = 0;
    fclose(op);
    op = fopen(argv[1], "r");
    while (fgets(buffer, 50, op) != NULL)  // read file line by line
    {
        sscanf(buffer, "%c %d", &number, &size);
        enQueue(number, size, 0);
        counter++;
    }
    printf("\n\n\n\n\n\nBelow is best fit:\n");
    bestFit(counter);

    free(buffer);
    fclose(op);
    destroy();
    return 0;
}

void bestFit(int counter)
{
    queue * current;
    memory * temp[counter];
    for (int g = 0; g < counter; g++)
    {
         temp[g] = (memory*)malloc(sizeof(memory));
    }
    current = (queue*)malloc(sizeof(queue));
    int a, b, c, times, d, holes, make, h = 0;
    int pro = 0;
    make = 0;
    int l = 0;
    holes = 0;
    double counterLoad = 0, totalPro = 0, totaoHoles = 0, totalMem = 0;
    a = 1;
    int mem;
    mem = 0;
    times = 0;
    b = 128;
    c = 0;
    for (a = 0; a < counter; a++) // first time load into memory, make sure there is also process in the memory
    {
        current = first();
        if (current->size > b)
        {
            break;
        }
        counterLoad++;
        temp[a]->size = current->size;
        temp[a] -> number = current -> number;
        temp[a]->start = c;
        totalPro = totalPro + a+1;
        temp[a]->kick = current->kick;
        c = c + temp[a] -> size;
        temp[a]->age = times;
        b = b - temp[a]->size;
        times++;
        mem = mem + temp[a] -> size;
        totalMem = totalMem + mem;
        printMem(a+1, 1, mem, a+1);
        totaoHoles++;
        deQueue();
        if (isEmpty() != 0)
        {
            printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
            return;
        }
        pro++;
    }
    mem = 0;
    b = 128;
    while(isEmpty() == 0)
    {
        make = 0;
        times++;
        current = first();
        c = 0;
        int small = 200;
        int holeSize = 0;
        int smallPos = 0;
        for (d = 0; d < pro; d++) // check the biggest hole for worst fit.
        {
            if (d == 0 && temp[0] -> start != 0 )
            {
                holes++;
                if (small >= temp[0] -> start - current -> size && temp[0] -> start - current -> size >= 0)
                {
                    holeSize = temp[0] -> start;
                    small = temp[0] -> start - current -> size;
                    smallPos = 0;
                }
            }
            else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
            {
                holes++;
                if (small >= 128 - temp[d]->size - temp[d] -> start - current -> size && 128 - temp[d]->size - temp[d] -> start - current -> size >= 0)
                {
                    holeSize = 128 - temp[d]->size - temp[d]->start;
                    small = 128 - temp[d]->size - temp[d] -> start - current -> size;
                    smallPos = d+1;
                }
            }
            
            else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
            {
                holes++;
                if (small >= temp[d+1]->start - temp[d]->size - temp[d]->start - current -> size && temp[d+1]->start - temp[d]->size - temp[d]->start - current -> size >= 0)
                {
                    holeSize = temp[d+1]->start - temp[d]->size - temp[d]->start;
                    small = temp[d+1]->start - temp[d]->size - temp[d]->start - current -> size;
                    smallPos = d+1;
                }
            }
        }
        holes = 0;
        if (smallPos == 0 && holeSize >= current->size)
        {
            times++;
            make = 1;
            counterLoad++;
            for (int j = pro; j >= smallPos; j--) // insert into memory array. All same thing doing below so I just comment here not after.
            {
                temp[j] = temp[j-1];
            }
            pro++;
            totalPro = totalPro + pro;
            temp[smallPos] = malloc(sizeof(memory));
            temp[smallPos] -> size = current->size;
            temp[smallPos] -> age = times;
            temp[smallPos]->kick = current->kick;
            temp[smallPos] -> number = current->number;
            temp[smallPos] -> start = 0;
            for (int k = 0; k < pro; k++)  // get the number of memory, also same for thing below. 
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)  // check how many holes, also same thing for below.
            {
                if (d == 1 && (temp[0] -> start != 0) )
                {
                    holes++;
                }
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }

            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            deQueue();  
            holes = 0;
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;   
        }
        else if (smallPos != 0 && smallPos == pro-1 && holeSize >= current->size)
        {
            times++;
            make = 1;
            counterLoad++;            
            for (int j = pro ; j > smallPos; j--) 
            {
                temp[j] = temp[j -1];
            }
            totalPro = totalPro + pro;
            temp[smallPos] = malloc(sizeof(memory));
            temp[smallPos] -> size = current->size;
            temp[smallPos] -> age = times;
            temp[smallPos] -> kick = current->kick;
            temp[smallPos] -> number = current->number;
            temp[smallPos] -> start = temp[smallPos-1]->size + temp[smallPos-1]->start;
            pro++;
            for (int k = 0; k < pro; k++)
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)
            {
                if (d == 1 && (temp[0] -> start != 0) )
                {
                    holes++;
                } 
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }
            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            deQueue();  
            holes = 0;
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;
        }
        else if (smallPos != 0 && smallPos != pro-1 && holeSize >= current->size)
        {
            times++;
            make = 1;
            counterLoad++;            
            for (int j = pro ; j > smallPos; j--) 
            {
                temp[j] = temp[j -1];
            }
            totalPro = totalPro + pro;
            temp[smallPos] = malloc(sizeof(memory));
            temp[smallPos] -> size = current->size;
            temp[smallPos] -> age = times;
            temp[smallPos] -> kick = current->kick;
            temp[smallPos] -> number = current->number;
            temp[smallPos] -> start = temp[smallPos-1]->size + temp[smallPos-1]->start;
            pro++;
            for (int k = 0; k < pro; k++)
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)
            {
                if (d == 1 && (temp[0] -> start != 0) )
                {
                    holes++;
                } 
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }
            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            deQueue();  
            holes = 0;
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;
        }
        else if ( smallPos == pro-1 && holeSize >= current->size)
        {
            pro++;
            totalPro = totalPro + pro;
            times++;
            counterLoad++;
            make = 1;
            temp[smallPos+1] = malloc(sizeof(memory));
            temp[smallPos+1]->size = current->size;
            temp[smallPos+1]->number = current->number;
            temp[smallPos+1]->kick = current->kick;
            temp[smallPos+1]->age = times;
            temp[smallPos+1]->start = temp[smallPos]->start + temp[smallPos]->size;
            for (int k = 0; k < pro; k++)
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)
            {
                if (d == 1 && temp[0] -> start != 0 )
                {
                    holes++;
                }
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }
            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            holes = 0;
            deQueue();  
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;
        }
        if (make == 0)
        {
            int small = temp[0]->age;
            h = 0;
            for (int f = 0; f < pro; f++)
            {
                if (temp[f]->age < small)
                {
                    small = temp[f]->age;
                    h = f;
                }
            }
            if (temp[h]->kick < 2)
            {
                
                temp[h]-> kick = temp[h] -> kick+1;
                enQueue(temp[h] -> number, temp[h] ->size, temp[h]->kick);
            }
            for ( int i = h; i < pro -1; i++ )
            {
                temp[i] = temp[i+1];
            }
            pro--;
        }
        if (pro == 0) // need to make sure there is also process in the memory array, so have to code it here again.
        {
            b = 128;
            for (a = 0; a < counter; a++)
            {
                temp[a] = malloc(sizeof(memory));
                current = first();
                if (current->size > b)
                {
                    break;
                }
                times++;
                counterLoad++;
                temp[a]->size = current->size;
                temp[a] -> number = current -> number;
                temp[a]->start = c;
                temp[a]->kick = current->kick;
                c = c + temp[a] -> size;
                temp[a]->age = times;
                b = b - temp[a]->size;
                make = 1;
                mem = mem + temp[a] -> size;
                pro++;
                totaoHoles++;
                totalPro = totalPro + pro;
                totalMem = totalMem + mem;
                printMem(pro, 1, mem, times+1);
                deQueue();
                if (isEmpty() != 0)
                {
                    printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                    return;
                }
            }
        }
        make = 0;
        holes = 0;
    }
    return;
}

void worstFit(int counter)
{
    queue * current;
    memory * temp[counter];
    for (int g = 0; g < counter; g++)
    {
         temp[g] = (memory*)malloc(sizeof(memory));
    }
    current = (queue*)malloc(sizeof(queue));
    int a, b, c, times, d, holes, make, h = 0;
    int pro = 0;
    make = 0;
    int l = 0;
    holes = 0;
    double counterLoad = 0, totalPro = 0, totaoHoles = 0, totalMem = 0;
    a = 1;
    int mem;
    mem = 0;
    times = 0;
    b = 128;
    c = 0;
    for (a = 0; a < counter; a++) // first time load into memory, make sure there is also process in the memory
    {
        current = first();
        if (current->size > b)
        {
            break;
        }
        counterLoad++;
        temp[a]->size = current->size;
        temp[a] -> number = current -> number;
        temp[a]->start = c;
        totalPro = totalPro + a+1;
        temp[a]->kick = current->kick;
        c = c + temp[a] -> size;
        temp[a]->age = times;
        b = b - temp[a]->size;
        times++;
        mem = mem + temp[a] -> size;
        totalMem = totalMem + mem;
        printMem(a+1, 1, mem, a+1);
        totaoHoles++;
        deQueue();
        if (isEmpty() != 0)
        {
            printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
            return;
        }
        pro++;
    }
    mem = 0;
    b = 128;
    while(isEmpty() == 0)  // load process until waiting queue is empty.
    {
        make = 0;
        int bigHole = 0;
        int bigHolePos = 0;
        times++;
        current = first();
        c = 0;
        for (d = 0; d < pro; d++) // check the biggest hole for worst fit.
        {
            if (d == 1 && temp[0] -> start != 0 )
            {
                holes++;
                if (temp[0] -> start >= bigHole)
                {
                    bigHole = temp[0] -> start;
                    bigHolePos = 0;
                }
            }
            else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
            {
                holes++;
                if (128 - temp[d]->size - temp[d] -> start >= bigHole)
                {
                    bigHole = 128 - temp[d]->size - temp[d]->start;
                    bigHolePos = d+1;
                }
            }
            
            else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
            {
                holes++;
                if (temp[d+1]->start - temp[d]->size - temp[d]->start >= bigHole)
                {
                    bigHole = temp[d+1]->start - temp[d]->size - temp[d]->start;
                    bigHolePos = d+1;
                }
               
            }
        }
        holes = 0;
        if (bigHolePos == 0 && bigHole >= current->size)
        {
            times++;
            make = 1;
            counterLoad++;
            for (int j = pro; j >= bigHolePos; j--) // insert into memory array. All same thing doing below so I just comment here not after.
            {
                temp[j] = temp[j-1];
            }
            pro++;
            totalPro = totalPro + pro;
            temp[bigHolePos] = malloc(sizeof(memory));
            temp[bigHolePos] -> size = current->size;
            temp[bigHolePos] -> age = times;
            temp[bigHolePos]->kick = current->kick;
            temp[bigHolePos] -> number = current->number;
            temp[bigHolePos] -> start = 0;
            for (int k = 0; k < pro; k++)  // get the number of memory, also same for thing below. 
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)  // check how many holes, also same thing for below.
            {
                if (d == 1 && (temp[0] -> start != 0) )
                {
                    holes++;
                }
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }

            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            deQueue();  
            holes = 0;
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;   
        }
        else if (bigHolePos == pro-1 && bigHole >= current->size)
        {
            pro++;
            totalPro = totalPro + pro;
            times++;
            counterLoad++;
            make = 1;
            temp[bigHolePos+1] = malloc(sizeof(memory));
            temp[bigHolePos+1]->size = current->size;
            temp[bigHolePos+1]->number = current->number;
            temp[bigHolePos+1]->kick = current->kick;
            temp[bigHolePos+1]->age = times;
            temp[bigHolePos+1]->start = temp[bigHolePos]->start + temp[bigHolePos]->size;
            for (int k = 0; k < pro; k++)
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)
            {
                if (d == 1 && temp[0] -> start != 0 )
                {
                    holes++;
                }
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }
            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            holes = 0;
            deQueue();  
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;
        }
         else if (bigHolePos != 0 && bigHolePos == pro-1 && bigHole >= current->size)
        {
            times++;
            make = 1;
            counterLoad++;            
            for (int j = pro ; j > bigHolePos; j--) 
            {
                temp[j] = temp[j -1];
            }
            totalPro = totalPro + pro;
            temp[bigHolePos] = malloc(sizeof(memory));
            temp[bigHolePos] -> size = current->size;
            temp[bigHolePos] -> age = times;
            temp[bigHolePos] -> kick = current->kick;
            temp[bigHolePos] -> number = current->number;
            temp[bigHolePos] -> start = temp[bigHolePos-1]->size + temp[bigHolePos-1]->start;
            pro++;
            for (int k = 0; k < pro; k++)
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)
            {
                if (d == 1 && (temp[0] -> start != 0) )
                {
                    holes++;
                } 
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }
            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            deQueue();  
            holes = 0;
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;
        }
        else if (bigHolePos != 0 && bigHolePos != pro-1 && bigHole >= current->size)
        {
            times++;
            make = 1;
            counterLoad++;            
            for (int j = pro ; j > bigHolePos; j--) 
            {
                temp[j] = temp[j -1];
            }
            totalPro = totalPro + pro;
            temp[bigHolePos] = malloc(sizeof(memory));
            temp[bigHolePos] -> size = current->size;
            temp[bigHolePos] -> age = times;
            temp[bigHolePos] -> kick = current->kick;
            temp[bigHolePos] -> number = current->number;
            temp[bigHolePos] -> start = temp[bigHolePos-1]->size + temp[bigHolePos-1]->start;
            pro++;
            for (int k = 0; k < pro; k++)
            {
                l = l + temp[k]->size;
            }
            totalMem = totalMem + l;
            for (d = 0; d < pro; d++)
            {
                if (d == 1 && (temp[0] -> start != 0) )
                {
                    holes++;
                } 
                else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                {
                    holes++;
                }
                else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                {
                    holes++;
                }
            }
            totaoHoles = totaoHoles + holes;
            printMem(pro, holes, l, times+1);
            deQueue();  
            holes = 0;
            if (isEmpty() != 0)
            {
                printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                return;
            }
            l = 0;
            make = 0;
            holes = 0;
            continue;
        }
        if (make == 0)
        {
            int small = temp[0]->age;
            h = 0;
            for (int f = 0; f < pro; f++)
            {
                if (temp[f]->age < small)
                {
                    small = temp[f]->age;
                    h = f;
                }
            }
            if (temp[h]->kick < 3)
            {
                enQueue(temp[h] -> number, temp[h] ->size, temp[h]->kick + 1);
            }
            for ( int i = h; i < pro -1; i++ )
            {
                temp[i] = temp[i+1];
            }
            pro--;
        }
        if (pro == 0) // need to make sure there is also process in the memory array, so have to code it here again.
        {
            b = 128;
            for (a = 0; a < counter; a++)
            {
                temp[a] = malloc(sizeof(memory));
                current = first();
                if (current->size > b)
                {
                    break;
                }
                times++;
                temp[a]->size = current->size;
                temp[a] -> number = current -> number;
                temp[a]->start = c;
                counterLoad++;
                temp[a]->kick = current->kick;
                c = c + temp[a] -> size;
                temp[a]->age = times;
                b = b - temp[a]->size;
                make = 1;
                mem = mem + temp[a] -> size;
                pro++;
                totaoHoles++;
                totalPro = totalPro + pro;
                totalMem = totalMem + mem;
                printMem(pro, 1, mem, times+1);
                deQueue();
                if (isEmpty() != 0)
                {
                    printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                    return;
                }
            }
        }
        make = 0;
        holes = 0;
    }
    return;    
}

void firstFit(int counter)
{
    queue * current;
    memory * temp[counter];
    for (int g = 0; g < counter; g++)
    {
         temp[g] = (memory*)malloc(sizeof(memory));
    }
    current = (queue*)malloc(sizeof(queue));
    int a, b, c, times, d, holes, make, e, h = 0;
    int pro = 0;
    make = 0;
    int l = 0;
    holes = 0;
    double counterLoad = 0, totalPro = 0, totaoHoles = 0, totalMem = 0;
    a = 1;
    int mem;
    mem = 0;
    times = 0;
    b = 128;
    c = 0;
    for (a = 0; a < counter; a++)
    {
        current = first();
        if (current->size > b)
        {
            break;
        }
        counterLoad++;
        temp[a]->size = current->size;
        temp[a] -> number = current -> number;
        temp[a]->start = c;
        totalPro = totalPro + a+1;
        temp[a]->kick = current->kick;
        c = c + temp[a] -> size;
        temp[a]->age = times;
        b = b - temp[a]->size;
        times++;
        mem = mem + temp[a] -> size;
        totalMem = totalMem + mem;
        printMem(a+1, 1, mem, a+1);
        totaoHoles++;
        deQueue();
        if (isEmpty() != 0)
        {
            printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
            return;
        }
        pro++;
    }
    mem = 0;
    b = 128;
    while(isEmpty() == 0)
    {
        times++;
        current = first();
        c = 0;
        for (e = 0; e < pro; e++)
        {
            if (e == pro-1 && temp[e] ->size + temp[e]->start + current->size < 128)
            {
                if (current->size < 128 - temp[e] ->size - temp[e]->start)
                {
                    pro++;
                    totalPro = totalPro + pro;
                    times++;
                    counterLoad++;
                    make = 1;
                    temp[e+1] = malloc(sizeof(memory));
                    temp[e+1]->size = current->size;
                    temp[e+1]->number = current->number;
                    temp[e+1]->kick = current->kick;
                    temp[e+1]->age = times;
                    temp[e+1]->start = temp[e]->start + temp[e]->size;
                    for (int k = 0; k < pro; k++)
                    {
                        l = l + temp[k]->size;
                    }
                    totalMem = totalMem + l;
                    for (d = 0; d < pro; d++)
                    {
                        if (d == 1 && temp[0] -> start != 0 )
                        {
                            holes++;
                        }
                        else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                        {
                            holes++;
                        }
                        else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                        {
                            holes++;
                        }

                    }
                    totaoHoles = totaoHoles + holes;
                    printMem(pro, holes, l, times+1);
                    holes = 0;
                    deQueue();  
                    if (isEmpty() != 0)
                    {
                        printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                        return;
                    }
                    l = 0;
                    break;
                }
                
            }
            if (e == 0 && temp[e]->start != 0 && temp[e]->start > current->size)
            {
                times++;
                make = 1;
                counterLoad++;
                for (int j = pro; j >= e; j--) 
                {
                    temp[j] = temp[j-1];
                }
                pro++;
                totalPro = totalPro + pro;
                temp[e] = malloc(sizeof(memory));
                temp[e] -> size = current->size;
                temp[e] -> age = times;
                temp[e]->kick = current->kick;
                temp[e] -> number = current->number;
                temp[e] -> start = 0;
                for (int k = 0; k < pro; k++)
                {
                    l = l + temp[k]->size;
                }
                totalMem = totalMem + l;
                for (d = 0; d < pro; d++)
                {
                    if (d == 1 && (temp[0] -> start != 0) )
                    {
                        holes++;
                    }
                    else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                    {
                        holes++;
                    }
                    else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                    {
                        holes++;
                    }

                }
                totaoHoles = totaoHoles + holes;
                printMem(pro, holes, l, times+1);
                deQueue();  
                holes = 0;
                if (isEmpty() != 0)
                {
                    printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                    return;
                }
                l = 0;
                break;
            }
            else if (  (temp[e+1]->start - temp[e]->size - temp[e]->start >= current->size) && (temp[e]->size + temp[e]->start < temp[e+1]->start) )
            {
                times++;
                make = 1;
                counterLoad++;
                for (int j = pro; j > e; j--) 
                {
                    temp[j] = temp[j -1];
                }
                pro++;
                totalPro = totalPro + pro;
                temp[e+1] = malloc(sizeof(memory));
                temp[e+1] -> size = current->size;
                temp[e+1] -> age = times;
                temp[e+1] -> kick = current->kick;
                temp[e+1] -> number = current->number;
                temp[e+1] -> start = temp[e]->size + temp[e]->start;
                for (int k = 0; k < pro; k++)
                {
                    l = l + temp[k]->size;
                }
                totalMem = totalMem + l;
                for (d = 0; d < pro; d++)
                {
                    if (d == 1 && (temp[0] -> start != 0) )
                    {
                        holes++;
                    } 
                    else if (d == pro-1 && (temp[d]->size + temp[d] -> start != 128) )
                    {
                        holes++;
                    }
                    else if ( temp[d]->size + temp[d]->start != temp[d+1]->start)
                    {
                        holes++;
                    }

                }
                totaoHoles = totaoHoles + holes;
                printMem(pro, holes, l, times+1);
                deQueue();  
                holes = 0;
                if (isEmpty() != 0)
                {
                    printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                    return;
                }
                l = 0;
                break;
            }
        }
        if (make == 0)
        {
            int small = temp[0]->age;
            h = 0;
            for (int f = 0; f < pro; f++)
            {
                if (temp[f]->age < small)
                {
                    small = temp[f]->age;
                    h = f;
                }
            }
            if (temp[h]->kick < 3)
            {
                enQueue(temp[h] -> number, temp[h] ->size, temp[h]->kick + 1);
            }
            for ( int i = h; i < pro -1; i++ )
            {
                temp[i] = temp[i+1];
            }
            pro--;
        }
        if (pro == 0)
        {
            for (a = 0; a < counter; a++)
            {
                temp[a] = malloc(sizeof(memory));
                current = first();
                if (current->size > b)
                {
                    break;
                }
                times++;
                counterLoad++;
                temp[a]->size = current->size;
                temp[a] -> number = current -> number;
                temp[a]->start = c;
                temp[a]->kick = current->kick;
                c = c + temp[a] -> size;
                temp[a]->age = times;
                b = b - temp[a]->size;
                make = 1;
                mem = mem + temp[a] -> size;
                pro++;
                totaoHoles++;
                totalPro = totalPro + pro;
                totalMem = totalMem + mem;
                printMem(pro, 1, mem, times+1);
                deQueue();
                if (isEmpty() != 0)
                {
                    printf("Total loads = %.2f, average #processes = %.2f, average #holes = %.2f, cumulative %%mem = %.2f \n", counterLoad, totalPro/counterLoad, totaoHoles/counterLoad, totalMem/counterLoad);
                    return;
                }

            }
        }
        make = 0;
        holes = 0;
    }
    return;
}

void printMem(int a, int hole, int mem, int aver)
{
    int b;
    double c,d;
    b = hole;
    c = mem/128.0 * 100;
    d = c/aver;
    
    printf("pid loaded, #processes = %d, #holes = %d, &memusage = %.2f, cumulative %%mem = %.2f\n", a, b, c, d);
    return;
}

void enQueue(char number1, int size1, int hit)
{
    queue * temp;
    temp = (queue*)malloc(sizeof(queue));
    if (temp == NULL)
    {
        printf("Fail to allocate memory.\n");
        exit(1);
    }
    temp->number = number1;
    temp->size = size1;
    temp->kick = hit;
    temp->next = NULL;

    if (front == NULL && back == NULL)
    {
        front = back = temp;
        return;
    }
    back -> next = temp;
    back = temp;
    return;
}

void deQueue()
{
    queue * temp = front;
    if (front == NULL)
    {
        printf("dequeue the queue is empty.\n");
        return;
    }
    if (front == back)
    {
        front = back = NULL;
    }
    else
    {
        front = front->next;
    }
    free(temp);
    return;
}

void print()
{
    queue * temp;
    temp = front;
    while (temp != NULL)
    {
        printf("%c %d\n", temp->number, temp->size);
        temp = temp->next;
    }
    return;
}

queue * first()
{
    if (front == NULL)
    {
        printf("first The queue is empty.\n");
        return NULL;
    }
    return front;
}

int isEmpty()
{
    if (front == NULL && back == NULL)
    {
        return 1;
    }
    return 0;
}

void destroy()
{
    while( back != NULL)
    {
        queue * temp = back->next;
        free(back);
        back = temp;
    }
    front = NULL;
}
