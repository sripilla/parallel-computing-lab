/*
==========================================================
Program Name : 8_parallel_calculator_mpi.c

Write a program in MPI to simulate simple calculator. Perform each operation using different process in parallel.

Objective:
-----------
This MPI program simulates a simple calculator
using parallel processing.

Each MPI process performs a different
arithmetic operation simultaneously.

Operations:
-------------
Rank 0 -> Addition
Rank 1 -> Subtraction
Rank 2 -> Multiplication
Rank 3 -> Division

Concepts Used:
---------------
1. MPI Initialization
2. Process Rank Identification
3. Parallel Task Distribution
4. Conditional Execution
5. Arithmetic Operations

Example:
---------
If:
    a = 20
    b = 10

Then:
    Rank 0 -> 20 + 10 = 30
    Rank 1 -> 20 - 10 = 10
    Rank 2 -> 20 * 10 = 200
    Rank 3 -> 20 / 10 = 2

This demonstrates how different processes
can execute different tasks in parallel.

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library header file

/*
==========================================================
Main Function
==========================================================
*/

int main(int argc, char *argv[])
{
    /*
    ------------------------------------------------------
    Variable Declarations
    ------------------------------------------------------
    */

    int rank;   // Stores process rank (process ID)

    // Input numbers for calculator operations
    int a = 20;
    int b = 10;

    /*
    ------------------------------------------------------
    Initialize MPI Environment
    ------------------------------------------------------

    Starts MPI execution environment.

    Must be called before any MPI function.
    */
    MPI_Init(&argc, &argv);

    /*
    ------------------------------------------------------
    Get Rank of Current Process
    ------------------------------------------------------

    MPI assigns a unique rank to every process.

    Example:
        Process 0 -> rank = 0
        Process 1 -> rank = 1
        Process 2 -> rank = 2
        Process 3 -> rank = 3
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Perform Different Operations
    Based on Process Rank
    ------------------------------------------------------

    Each process executes a different task.

    This demonstrates parallel task execution.
    */

    // Rank 0 performs addition
    if(rank == 0)
    {
        printf("Addition = %d\n", a + b);
    }

    // Rank 1 performs subtraction
    else if(rank == 1)
    {
        printf("Subtraction = %d\n", a - b);
    }

    // Rank 2 performs multiplication
    else if(rank == 2)
    {
        printf("Multiplication = %d\n", a * b);
    }

    // Rank 3 performs division
    else if(rank == 3)
    {
        /*
        Integer division is performed here.
        */

        printf("Division = %d\n", a / b);
    }

    /*
    ------------------------------------------------------
    Finalize MPI Environment
    ------------------------------------------------------

    Cleans up MPI resources.

    No MPI functions should be called after this.
    */
    MPI_Finalize();

    /*
    ------------------------------------------------------
    End Program Successfully
    ------------------------------------------------------
    */

    return 0;
}

// mpicc 8_parallel_calculator_mpi.c -o 8_parallel_calculator_mpi

// mpirun --oversubscribe -np 4 ./8_parallel_calculator_mpi