/*
==========================================================
Program Name :
9_toggle_string_character_mpi.c

Write a program in MPI to toggle the character of a given string indexed by the rank of the process. Hint: Suppose the string is HELLO and there are 5 processes, then process 0 toggle 'H' to 'h', process I toggle 'E' to 'e' and so on.

Objective:
-----------
This MPI program toggles the character
of a string based on the rank of the process.

Concept:
---------
Each process modifies ONE character
of the string whose index matches
the process rank.

Example:
---------
String = "HELLO"

Process 0:
    H -> h

Process 1:
    E -> e

Process 2:
    L -> l

Process 3:
    L -> l

Process 4:
    O -> o

Concepts Used:
---------------
1. MPI Initialization
2. Process Rank Identification
3. String Manipulation
4. Character Toggle using tolower()
5. Parallel Execution

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library
#include <ctype.h>   // Character handling functions

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

    int rank;   // Stores process rank

    /*
    Original string

    NOTE:
    Each MPI process gets its own copy
    of the string because MPI processes
    have separate memory spaces.
    */
    char str[] = "HELLO";

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

    MPI assigns a unique rank to
    every process.

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
    Toggle Character Based on Rank
    ------------------------------------------------------

    rank < 5 ensures process does not
    access invalid string positions.

    String Indexes:
        H -> index 0
        E -> index 1
        L -> index 2
        L -> index 3
        O -> index 4
    */

    if(rank < 5)
    {
        /*
        Convert uppercase character
        to lowercase character.

        tolower() converts:
            H -> h
            E -> e
            etc.
        */
        str[rank] = tolower(str[rank]);

        /*
        Print modified string
        after toggling.
        */
        printf("Process %d changed string to %s\n",
               rank,
               str);
    }

    /*
    ------------------------------------------------------
    Finalize MPI Environment
    ------------------------------------------------------

    Cleans up MPI resources.

    No MPI functions should be used
    after this.
    */
    MPI_Finalize();

    /*
    ------------------------------------------------------
    End Program Successfully
    ------------------------------------------------------
    */

    return 0;
}

// mpicc 9_toggle_string_character_mpi.c -o 9_toggle_string_character_mpi

// mpirun --oversubscribe -np 5 ./9_toggle_string_character_mpi

