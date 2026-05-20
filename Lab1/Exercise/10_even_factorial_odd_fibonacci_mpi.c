/*
==========================================================
Program Name :
10_even_factorial_odd_fibonacci_mpi.c

Write a program in MPI where even ranked process prints factorial of the rank and odd ranked process prints ranks Fibonacci number.

Objective:
-----------
This MPI program demonstrates:
1. MPI Initialization
2. Process Rank Identification
3. Conditional Parallel Execution
4. Factorial Calculation
5. Fibonacci Calculation

Concept:
---------
EVEN ranked processes calculate:
        Factorial of rank

ODD ranked processes calculate:
        Fibonacci of rank

Example:
---------
Rank 0 -> Factorial of 0 = 1
Rank 1 -> Fibonacci of 1 = 1
Rank 2 -> Factorial of 2 = 2
Rank 3 -> Fibonacci of 3 = 2
Rank 4 -> Factorial of 4 = 24

Concepts Used:
---------------
- MPI process ranks
- Parallel task execution
- User-defined functions
- Conditional statements
- Loops

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library header file

/*
==========================================================
Function : factorial()

Purpose:
---------
Calculates factorial of a number.

Formula:
---------
n! = 1 × 2 × 3 × ... × n

Example:
---------
4! = 4 × 3 × 2 × 1 = 24
==========================================================
*/

int factorial(int n)
{
    int i;
    int fact = 1;

    /*
    Multiply numbers from 1 to n
    */
    for(i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    /*
    Return factorial result
    */
    return fact;
}

/*
==========================================================
Function : fibonacci()

Purpose:
---------
Calculates nth Fibonacci number.

Fibonacci Series:
-----------------
0, 1, 1, 2, 3, 5, 8, 13 ...

Logic:
------
Next term = previous term + current term
==========================================================
*/

int fibonacci(int n)
{
    int a = 0;
    int b = 1;
    int c;
    int i;

    /*
    Special case:
    Fibonacci of 0 is 0
    */
    if(n == 0)
    {
        return 0;
    }

    /*
    Generate Fibonacci sequence
    */
    for(i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    /*
    Return nth Fibonacci number
    */
    return b;
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

    int rank;   // Stores process rank

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
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Check Whether Rank is EVEN or ODD
    ------------------------------------------------------

    rank % 2 == 0
        -> EVEN rank

    rank % 2 != 0
        -> ODD rank
    */

    if(rank % 2 == 0)
    {
        /*
        EVEN ranked process calculates factorial
        */

        printf("Factorial of %d = %d\n",
               rank,
               factorial(rank));
    }
    else
    {
        /*
        ODD ranked process calculates Fibonacci
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

// mpicc 10_even_factorial_odd_fibonacci_mpi.c -o 10_even_factorial_odd_fibonacci_mpi

// mpirun --oversubscribe -np 5 ./10_even_factorial_odd_fibonacci_mpi