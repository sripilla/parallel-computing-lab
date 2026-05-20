/*
========================================================
Program Name : 6_parallel_series_sum.c
Write a MPI program to read value of N in the root process.
 Using N processes, including root, find out 1! + (1+2) +3! +(1+2+3+4 ) +5! +(1+2+3+4+5+6) 
 and print the result in the root process
Aim:
Using N MPI processes, compute series:

1! + (1+2) + 3! + (1+2+3+4) + 5! + ...

Pattern:
Even rank process  -> factorial
Odd rank process   -> summation

Final result printed by root process.
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output

int main(int argc, char *argv[])
{
    int rank;              // Rank of current process
    int size;              // Total number of processes

    int local_sum = 0;     // Stores local computation
    int total_sum = 0;     // Stores final sum

    /*
    ========================================================
    STEP 1: Initialize MPI
    ========================================================
    */

    MPI_Init(&argc, &argv);

    /*
    ========================================================
    STEP 2: Get Rank and Size
    ========================================================
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*
    ========================================================
    VALUE USED BY EACH PROCESS

    Formula:
    n = rank + 1

    Example:
    rank 0 -> n = 1
    rank 1 -> n = 2
    rank 2 -> n = 3
    ========================================================
    */

    int n = rank + 1;

    /*
    ========================================================
    EVEN RANK PROCESS
    -> FACTORIAL
    ========================================================
    */

    if(rank % 2 == 0)
    {
        local_sum = 1;

        /*
        Find factorial of n
        */

        for(int i = 1; i <= n; i++)
        {
            local_sum = local_sum * i;
        }

        printf("Process %d computed %d! = %d\n",
               rank,
               n,
               local_sum);
    }

    /*
    ========================================================
    ODD RANK PROCESS
    -> SUMMATION
    ========================================================
    */

    else
    {
        local_sum = 0;

        /*
        Find:
        1 + 2 + 3 + ... + n
        */

        for(int i = 1; i <= n; i++)
        {
            local_sum = local_sum + i;
        }

        printf("Process %d computed sum(1 to %d) = %d\n",
               rank,
               n,
               local_sum);
    }

    /*
    ========================================================
    MPI_Reduce()

    Collects all local sums
    and adds them into total_sum
    at root process.
    ========================================================
    */

    MPI_Reduce(&local_sum,
               &total_sum,
               1,
               MPI_INT,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    /*
    ========================================================
    ROOT PROCESS PRINTS FINAL RESULT
    ========================================================
    */

    if(rank == 0)
    {
        printf("\nFinal Series Sum = %d\n",
               total_sum);
    }

    /*
    ========================================================
    STEP 3: Finalize MPI
    ========================================================
    */

    MPI_Finalize();

    return 0;
}

// mpicc 6_parallel_series_sum.c

// mpirun -np 6 ./a.out

