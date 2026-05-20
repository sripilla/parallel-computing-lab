/*
==========================================================
Program Name :
11_reverse_integer_array_mpi.c

Write a program in MPI to reverse the digits of the following integer array of size 9 with 9 processes. Initialize the array to the following values. Input array : 18, 523, 301, 1234, 2, 14, 108, 150, 1928 Output array: 81, 325, 103, 4321, 2, 41, 801, 51, 8291

Objective:
-----------
This MPI program reverses the digits
of integers stored in an array.

Each MPI process handles ONE element
of the array in parallel.

Input Array:
-------------
18, 523, 301, 1234, 2, 14, 108, 150, 1928

Output Array:
--------------
81, 325, 103, 4321, 2, 41, 801, 51, 8291

Concepts Used:
---------------
1. MPI Initialization
2. Process Rank Identification
3. Parallel Array Processing
4. Digit Reversal Logic
5. Conditional Execution

Process Distribution:
----------------------
Process 0 -> reverses 18
Process 1 -> reverses 523
Process 2 -> reverses 301
...
Process 8 -> reverses 1928

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library header file

/*
==========================================================
Function : reverseNumber()

Purpose:
---------
Reverses digits of a given integer.

Example:
---------
Input  : 1234
Output : 4321
==========================================================
*/

int reverseNumber(int num)
{
    int reversed = 0;
    int digit;

    /*
    Extract digits one by one
    and build reversed number
    */

    while(num > 0)
    {
        /*
        Get last digit
        */
        digit = num % 10;

        /*
        Append digit to reversed number
        */
        reversed = reversed * 10 + digit;

        /*
        Remove last digit
        */
        num = num / 10;
    }

    /*
    Return reversed integer
    */
    return reversed;
}

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
    Input integer array
    */

    int arr[9] = {18, 523, 301, 1234, 2,
                  14, 108, 150, 1928};

    /*
    Variable to store reversed number
    */

    int reversed;

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

    MPI assigns unique rank to
    every process.

    Example:
        Process 0 -> rank = 0
        Process 1 -> rank = 1
        ...
        Process 8 -> rank = 8
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Reverse Array Element Based on Rank
    ------------------------------------------------------

    Each process handles one array element.

    rank < 9 ensures valid array access.
    */

    if(rank < 9)
    {
        /*
        Reverse digits of the number
        corresponding to current rank
        */

        reversed = reverseNumber(arr[rank]);

        /*
        Print original and reversed number
        */

        printf("Process %d : %d -> %d\n",
               rank,
               arr[rank],
               reversed);
    }

    /*
    ------------------------------------------------------
    Finalize MPI Environment
    ------------------------------------------------------

    Cleans up MPI resources.

    No MPI functions should be used after this.
    */

    MPI_Finalize();

    /*
    ------------------------------------------------------
    End Program Successfully
    ------------------------------------------------------
    */

    return 0;
}

//mpicc 11_reverse_integer_array_mpi.c -o 11_reverse_integer_array_mpi

// mpirun --oversubscribe -np 9 ./11_reverse_integer_array_mpi

