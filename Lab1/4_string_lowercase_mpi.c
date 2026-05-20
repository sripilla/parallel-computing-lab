/*
==========================================================
Program Name : 4_string_lowercase_mpi.c

Objective:
-----------
This MPI program demonstrates:
1. MPI Initialization
2. Process Rank Identification
3. Parallel String Manipulation
4. Character Conversion using tolower()

Concept:
---------
A string "HELLO" is shared in all processes.

Each process changes ONE character
(from uppercase to lowercase)
based on its rank.

Rank 0 -> changes H to h
Rank 1 -> changes E to e
Rank 2 -> changes L to l
Rank 3 -> changes L to l
Rank 4 -> changes O to o

This program helps understand:
- MPI process ranks
- Parallel execution
- Character manipulation
- String processing in MPI

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library header file
#include <ctype.h>   // Character handling functions like tolower()

// Main function
int main(int argc, char *argv[])
{
    /*
    ------------------------------------------------------
    Variable Declarations
    ------------------------------------------------------
    */

    int rank;   // Stores process rank (process ID)

    /*
    String to be modified

    Each process gets its own copy of the string
    because MPI processes have separate memory spaces.
    */
    char str[] = "HELLO";

    /*
    ------------------------------------------------------
    Initialize MPI Environment
    ------------------------------------------------------

    Starts MPI execution environment.

    Must be called before any MPI functions.
    */
    MPI_Init(&argc, &argv);

    /*
    ------------------------------------------------------
    Get Rank of Current Process
    ------------------------------------------------------

    MPI assigns a unique rank to each process.

    Example:
        Process 0 -> rank = 0
        Process 1 -> rank = 1
        Process 2 -> rank = 2
        Process 3 -> rank = 3
        Process 4 -> rank = 4
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Modify Character Based on Rank
    ------------------------------------------------------

    rank < 5 ensures processes only access
    valid positions of the string.

    String indexes:
        H -> index 0
        E -> index 1
        L -> index 2
        L -> index 3
        O -> index 4

    tolower() converts uppercase letters
    to lowercase letters.
    */

    if(rank < 5)
    {
        /*
        Convert character at current rank position
        to lowercase.
        */
        str[rank] = tolower(str[rank]);

        /*
        Print modified string by current process.
        */
        printf("Process %d changed string to %s\n",
               rank, str);
    }

    /*
    ------------------------------------------------------
    Finalize MPI Environment
    ------------------------------------------------------

    Cleans up MPI resources.

    No MPI function should be used after this.
    */
    MPI_Finalize();

    /*
    ------------------------------------------------------
    End Program Successfully
    ------------------------------------------------------
    */
    return 0;
}