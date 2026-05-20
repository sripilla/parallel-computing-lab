/*
==========================================================
Program Name : 6_power_rank_mpi.c

Write a simple MPI program to find out pow (x, rank) for all the processes where 'x' is the integer constant and 'rank' is the rank of the process. Write a program in MPI where even ranked process prints "Hello" and odd ranked process prints "World".

Objective:
-----------
This MPI program calculates:

        pow(x, rank)

where:
    x     = constant integer
    rank  = process rank

Each process computes:
        x ^ rank

Example:
---------
If x = 2

Rank 0 -> 2^0 = 1
Rank 1 -> 2^1 = 2
Rank 2 -> 2^2 = 4
Rank 3 -> 2^3 = 8

Concepts Used:
---------------
1. MPI Initialization
2. Process Rank Identification
3. Mathematical Power Function
4. Parallel Computation

==========================================================
*/

#include <stdio.h>   // Standard input/output
#include <mpi.h>     // MPI library
#include <math.h>    // pow() function

// Main function
int main(int argc, char *argv[])
{
    /*
    ------------------------------------------------------
    Variable Declarations
    ------------------------------------------------------
    */

    int rank;      // Stores process rank
    int x = 2;     // Constant base value

    double result; // Stores power result

    /*
    ------------------------------------------------------
    Initialize MPI Environment
    ------------------------------------------------------
    */

    MPI_Init(&argc, &argv);

    /*
    ------------------------------------------------------
    Get Rank of Current Process
    ------------------------------------------------------
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Calculate x^rank
    ------------------------------------------------------

    pow(base, exponent)

    Example:
        pow(2,3) = 8
    */

    result = pow(x, rank);

    /*
    ------------------------------------------------------
    Print Result
    ------------------------------------------------------
    */

    printf("Process %d : %d^%d = %.0lf\n",
           rank, x, rank, result);

    /*
    ------------------------------------------------------
    Finalize MPI Environment
    ------------------------------------------------------
    */

    MPI_Finalize();

    return 0;
}

// mpicc 6_power_rank_mpi.c -o 6_power_rank_mpi -lm

// mpirun --oversubscribe -np 4 ./6_power_rank_mpi