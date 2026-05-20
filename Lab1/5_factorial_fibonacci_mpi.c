/*
==========================================================
Program Name : 5_factorial_fibonacci_mpi.c

Objective:
-----------
This MPI program demonstrates:
1. MPI Initialization
2. Process Rank Identification
3. Conditional Parallel Execution
4. Function Calling in MPI
5. Factorial and Fibonacci Calculations

Concept:
---------
Each MPI process performs a different task
based on whether its rank is EVEN or ODD.

EVEN Rank Processes:
    -> Calculate Factorial

ODD Rank Processes:
    -> Calculate Fibonacci

Examples:
----------
Rank 0 -> Factorial of 0
Rank 1 -> Fibonacci of 1
Rank 2 -> Factorial of 2
Rank 3 -> Fibonacci of 3
Rank 4 -> Factorial of 4

This program helps understand:
- MPI process ranks
- Parallel task distribution
- User-defined functions
- Conditional execution

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library header file

/*
==========================================================
Function: factorial()

Purpose:
--------
Calculates factorial of a number.

Formula:
--------
n! = 1 × 2 × 3 × ... × n

Example:
--------
4! = 4 × 3 × 2 × 1 = 24
==========================================================
*/

int factorial(int n)
{
    int f = 1;   // Stores factorial result
    int i;       // Loop counter

    /*
    Multiply numbers from 1 to n
    */
    for(i = 1; i <= n; i++)
    {
        f *= i;
    }

    /*
    Return factorial value
    */
    return f;
}

/*
==========================================================
Function: fibonacci()

Purpose:
--------
Calculates nth Fibonacci number.

Fibonacci Series:
-----------------
0, 1, 1, 2, 3, 5, 8, 13 ...

Formula:
--------
next = previous1 + previous2
==========================================================
*/

int fibonacci(int n)
{
    /*
    Initial Fibonacci values
    */
    int a = 0;
    int b = 1;
    int c;
    int i;

    /*
    Generate Fibonacci series up to nth term
    */
    for(i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    /*
    Special case:
    Fibonacci(0) = 0

    Otherwise return b
    */
    return n == 0 ? 0 : b;
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
    Variable Declaration
    ------------------------------------------------------
    */

    int rank;   // Stores process rank (process ID)

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

    MPI assigns a unique ID (rank)
    to each process.

    Example:
        Process 0 -> rank = 0
        Process 1 -> rank = 1
        Process 2 -> rank = 2
        Process 3 -> rank = 3
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Conditional Parallel Execution
    ------------------------------------------------------

    EVEN ranks:
        Perform factorial calculation

    ODD ranks:
        Perform Fibonacci calculation
    */

    if(rank % 2 == 0)
    {
        /*
        EVEN rank process executes this block
        */

        printf("Factorial of %d = %d\n",
               rank,
               factorial(rank));
    }
    else
    {
        /*
        ODD rank process executes this block
        */

        printf("Fibonacci of %d = %d\n",
               rank,
               fibonacci(rank));
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