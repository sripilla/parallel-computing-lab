/*
==========================================================
Program Name :
7_even_hello_odd_world_mpi.c

Write a simple MPI program to find out pow (x, rank) for all the processes where 'x' is the integer constant and 'rank' is the rank of the process. Write a program in MPI where even ranked process prints "Hello" and odd ranked process prints "World".

Objective:
-----------
This MPI program demonstrates:
1. MPI Initialization
2. Process Rank Identification
3. Conditional Execution

Concept:
---------
EVEN ranked processes print:
        "Hello"

ODD ranked processes print:
        "World"

Example:
---------
Rank 0 -> Hello
Rank 1 -> World
Rank 2 -> Hello
Rank 3 -> World

Concepts Used:
---------------
- MPI ranks
- Parallel execution
- if-else condition
- Modulus operator (%)

==========================================================
*/

#include <stdio.h>   // Standard input/output
#include <mpi.h>     // MPI library

// Main function
int main(int argc, char *argv[])
{
    /*
    ------------------------------------------------------
    Variable Declaration
    ------------------------------------------------------
    */

    int rank;   // Stores process rank

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
    Check Whether Rank is EVEN or ODD
    ------------------------------------------------------

    rank % 2 == 0
        -> EVEN

    rank % 2 != 0
        -> ODD
    */

    if(rank % 2 == 0)
    {
        /*
        EVEN ranked process executes this block
        */

        printf("Hello from process %d\n", rank);
    }
    else
    {
        /*
        ODD ranked process executes this block
        */

        printf("World from process %d\n", rank);
    }

    /*
    ------------------------------------------------------
    Finalize MPI Environment
    ------------------------------------------------------
    */

    MPI_Finalize();

    return 0;
}

//mpicc 7_even_hello_odd_world_mpi.c -o 7_even_hello_odd_world_mpi

// mpirun --oversubscribe -np 4 ./7_even_hello_odd_world_mpi

