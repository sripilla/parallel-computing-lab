/*======================================================================
LAB 4 - Exercise Question 1

Program:
MPI program using N processes to find

1! + 2! + 3! + ..... + N!

using MPI_Scan().

The program also demonstrates MPI error handling routines.

Compilation:
mpicc 1_factorial_sum_using_scan_error_handling.c -o factorial_scan

Execution Example:
mpirun -np 5 ./factorial_scan

Example:
N = 5

1! = 1
2! = 2
3! = 6
4! = 24
5! = 120

Sum = 1 + 2 + 6 + 24 + 120 = 153
======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*------------------------------------------------------------------
Function to calculate factorial of a number
Example:
factorial(4) = 24
------------------------------------------------------------------*/
long long factorial(int n)
{
    long long fact = 1;

    for(int i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    return fact;
}

int main(int argc, char *argv[])
{
    int rank;               // Process ID
    int size;               // Total number of processes

    int N;                  // User input value
    long long local_fact;   // Factorial computed by each process
    long long prefix_sum;   // Result returned by MPI_Scan

    char error_string[MPI_MAX_ERROR_STRING];
    int error_length;

    /*--------------------------------------------------------------
    Initialize MPI Environment
    --------------------------------------------------------------*/
    MPI_Init(&argc, &argv);

    /*--------------------------------------------------------------
    Get rank (process number)
    --------------------------------------------------------------*/
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*--------------------------------------------------------------
    Get total number of processes
    --------------------------------------------------------------*/
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*--------------------------------------------------------------
    Change error handler so MPI returns errors instead of aborting
    --------------------------------------------------------------*/
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    /*--------------------------------------------------------------
    Root process takes input
    --------------------------------------------------------------*/
    if(rank == 0)
    {
        printf("Enter value of N: ");
        scanf("%d", &N);

        /*----------------------------------------------------------
        Error Handling:
        N must be greater than zero
        ----------------------------------------------------------*/
        if(N <= 0)
        {
            printf("ERROR: N must be greater than 0\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        /*----------------------------------------------------------
        Need at least N processes
        Process 0 computes 1!
        Process 1 computes 2!
        ...
        Process N-1 computes N!
        ----------------------------------------------------------*/
        if(size < N)
        {
            printf("\nERROR:\n");
            printf("Number of MPI processes must be at least N\n");
            printf("N = %d, Processes = %d\n", N, size);

            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    /*--------------------------------------------------------------
    Broadcast N to all processes
    --------------------------------------------------------------*/
    int error_code =
        MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /*--------------------------------------------------------------
    MPI Error Handling Example
    --------------------------------------------------------------*/
    if(error_code != MPI_SUCCESS)
    {
        MPI_Error_string(
            error_code,
            error_string,
            &error_length
        );

        printf("Process %d MPI Error: %s\n",
               rank,
               error_string);

        MPI_Finalize();
        return 0;
    }

    /*--------------------------------------------------------------
    Each process computes one factorial

    Rank 0 -> 1!
    Rank 1 -> 2!
    Rank 2 -> 3!
    ...
    --------------------------------------------------------------*/
    if(rank < N)
        local_fact = factorial(rank + 1);
    else
        local_fact = 0;

    /*--------------------------------------------------------------
    MPI_Scan performs prefix sum

    Example factorials:
    [1, 2, 6, 24, 120]

    Prefix sums:
    [1, 3, 9, 33, 153]
    --------------------------------------------------------------*/
    MPI_Scan(
        &local_fact,
        &prefix_sum,
        1,
        MPI_LONG_LONG,
        MPI_SUM,
        MPI_COMM_WORLD
    );

    /*--------------------------------------------------------------
    Display factorial and prefix sum of each process
    --------------------------------------------------------------*/
    if(rank < N)
    {
        printf("Process %d : %d! = %lld , Prefix Sum = %lld\n",
               rank,
               rank + 1,
               local_fact,
               prefix_sum);
    }

    /*--------------------------------------------------------------
    Last useful process contains final answer
    --------------------------------------------------------------*/
    if(rank == N - 1)
    {
        printf("\nFinal Result\n");
        printf("1! + 2! + ... + %d! = %lld\n",
               N,
               prefix_sum);
    }

    /*--------------------------------------------------------------
    Close MPI Environment
    --------------------------------------------------------------*/
    MPI_Finalize();

    return 0;
}