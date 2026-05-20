/*
==========================================================
Program Name : 3_arithmetic_operations_mpi.c

Objective:
-----------
This MPI program demonstrates:
1. MPI Initialization
2. Process Rank Identification
3. Parallel Conditional Execution
4. Performing Different Arithmetic Operations
   using different MPI processes

Concept:
---------
Each MPI process performs a different operation
based on its rank.

Rank 0 -> Addition
Rank 1 -> Subtraction
Rank 2 -> Multiplication
Rank 3 -> Division

This program helps understand:
- Process ranks
- Conditional execution in MPI
- Parallel task distribution

==========================================================
*/

#include <stdio.h>   // Standard input/output library
#include <mpi.h>     // MPI library header file

// Main function
int main(int argc, char *argv[])
{
    /*
    ------------------------------------------------------
    Variable Declarations
    ------------------------------------------------------
    */

    int rank;      // Stores rank (ID) of each process

    // Two integer values for arithmetic operations
    int a = 20;
    int b = 10;

    /*
    ------------------------------------------------------
    Initialize MPI Environment
    ------------------------------------------------------

    This function starts the MPI execution environment.

    It must be called before any MPI function.
    */
    MPI_Init(&argc, &argv);

    /*
    ------------------------------------------------------
    Get Rank of Current Process
    ------------------------------------------------------

    MPI_COMM_WORLD:
        Default communicator containing all processes.

    rank:
        Unique process ID assigned by MPI.

    Example:
        Process 0 -> rank = 0
        Process 1 -> rank = 1
        Process 2 -> rank = 2
        Process 3 -> rank = 3
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Conditional Arithmetic Operations
    ------------------------------------------------------

    Different processes perform different tasks.

    This demonstrates task distribution in
    parallel computing.
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
    Return Statement
    ------------------------------------------------------

    return 0 indicates successful program execution.
    */
    return 0;
}