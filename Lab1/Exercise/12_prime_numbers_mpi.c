/*
==========================================================
Program Name :
12_prime_numbers_mpi.c

Write a MPI program to find the prime numbers between 1 and 100 using two processes

Objective:
-----------
This MPI program finds prime numbers
between 1 and 100 using TWO processes.

Process Distribution:
----------------------
Process 0:
    Finds prime numbers from 1 to 50

Process 1:
    Finds prime numbers from 51 to 100

Concepts Used:
---------------
1. MPI Initialization
2. Process Rank Identification
3. Parallel Range Distribution
4. Prime Number Checking
5. Conditional Execution

What is a Prime Number?
------------------------
A prime number has exactly TWO factors:
    1 and itself

Examples:
----------
2, 3, 5, 7, 11, 13 ...

==========================================================
*/

#include <stdio.h>   // Standard input/output functions
#include <mpi.h>     // MPI library header file

/*
==========================================================
Function : isPrime()

Purpose:
---------
Checks whether a number is prime.

Returns:
---------
1 -> Prime
0 -> Not Prime
==========================================================
*/

int isPrime(int n)
{
    int i;

    /*
    Numbers less than 2 are not prime
    */

    if(n < 2)
    {
        return 0;
    }

    /*
    Check divisibility from 2 to n/2
    */

    for(i = 2; i <= n / 2; i++)
    {
        /*
        If divisible, not prime
        */

        if(n % i == 0)
        {
            return 0;
        }
    }

    /*
    If no divisors found, number is prime
    */

    return 1;
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

    int rank;      // Stores process rank
    int start;     // Starting range
    int end;       // Ending range
    int i;

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

    Process 0 -> rank = 0
    Process 1 -> rank = 1
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ------------------------------------------------------
    Divide Work Between Processes
    ------------------------------------------------------

    Process 0:
        Checks numbers from 1 to 50

    Process 1:
        Checks numbers from 51 to 100
    */

    if(rank == 0)
    {
        start = 1;
        end = 50;
    }
    else
    {
        start = 51;
        end = 100;
    }

    /*
    ------------------------------------------------------
    Print Process Information
    ------------------------------------------------------
    */

    printf("\nProcess %d checking range %d to %d\n",
           rank,
           start,
           end);

    /*
    ------------------------------------------------------
    Find Prime Numbers in Assigned Range
    ------------------------------------------------------
    */

    for(i = start; i <= end; i++)
    {
        /*
        Check if number is prime
        */

        if(isPrime(i))
        {
            printf("%d ", i);
        }
    }

    /*
    Print newline for better formatting
    */

    printf("\n");

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

// mpicc 12_prime_numbers_mpi.c -o 12_prime_numbers_mpi

// mpirun --oversubscribe -np 2 ./12_prime_numbers_mpi