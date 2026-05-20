/*
==========================================================
Program Name : even_odd_mpi.c

Objective:
-----------
This MPI program demonstrates:
1. MPI initialization
2. Getting process rank
3. Conditional execution based on rank
4. Parallel execution using multiple processes

Concept:
---------
- Even ranked processes print:
      "Hello from rank X"

- Odd ranked processes print:
      "World from rank X"

This helps understand:
- MPI process ranks
- Parallel execution
- Conditional branching in MPI

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library header file

// Main function
int main(int argc, char *argv[])
{
    // Variable to store the rank (ID) of each process
    int rank;

    /*
    ------------------------------------------------------
    Initialize MPI Environment
    ------------------------------------------------------

    This function starts the MPI execution environment.

    It must be called before using any MPI functions.

    argc and argv are passed so MPI can process
    command-line arguments if needed.
    */
    MPI_Init(&argc, &argv);

    /*
    ------------------------------------------------------
    Get Rank of Current Process
    ------------------------------------------------------

    MPI_COMM_WORLD:
        Default communicator containing all processes.

    rank:
        Stores the unique ID of the current process.

    Example:
        Process 0 -> rank = 0
        Process 1 -> rank = 1
        Process 2 -> rank = 2
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Conditional Execution
    ------------------------------------------------------

    rank % 2 checks whether rank is:
        EVEN -> remainder = 0
        ODD  -> remainder = 1

    Even ranks print "Hello"
    Odd ranks print "World"
    */

    if(rank % 2 == 0)
    {
        // Executed by even-numbered processes
        printf("Hello from rank %d\n", rank);
    }
    else
    {
        // Executed by odd-numbered processes
        printf("World from rank %d\n", rank);
    }

    /*
    ------------------------------------------------------
    Finalize MPI Environment
    ------------------------------------------------------

    Cleans up MPI resources.

    No MPI function should be called after this.
    */
    MPI_Finalize();

    // Return 0 indicates successful execution
    return 0;
}