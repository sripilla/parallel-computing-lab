/*
========================================================
Program Name : 5_parallel_prime_check.c
Write a MPI program to read N elements of an array in the master process. 
Let N processes including master process check the array values are prime or not.
Aim:
Master process reads N elements of an array.

N = total number of processes.

Each process receives one element
and checks whether the number is
PRIME or NOT PRIME.
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output

int main(int argc, char *argv[])
{
    int rank;              // Rank of current process
    int size;              // Total number of processes
    int arr[100];          // Array to store elements
    int num;               // Number received by process
    int flag = 0;          // Prime checking flag

    MPI_Status status;

    /*
    ========================================================
    STEP 1: Initialize MPI Environment
    ========================================================
    */

    MPI_Init(&argc, &argv);

    /*
    ========================================================
    STEP 2: Get Rank and Total Number of Processes
    ========================================================
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*
    ========================================================
    MASTER PROCESS (Process 0)
    ========================================================
    */

    if(rank == 0)
    {
        printf("Enter %d elements:\n", size);

        /*
        Read array elements
        */

        for(int i = 0; i < size; i++)
        {
            scanf("%d", &arr[i]);
        }

        /*
        Send one element to each process
        */

        for(int i = 0; i < size; i++)
        {
            MPI_Send(&arr[i],
                     1,
                     MPI_INT,
                     i,
                     0,
                     MPI_COMM_WORLD);

            printf("Master sent %d to Process %d\n",
                   arr[i], i);
        }
    }

    /*
    ========================================================
    ALL PROCESSES RECEIVE ONE NUMBER
    ========================================================
    */

    MPI_Recv(&num,
             1,
             MPI_INT,
             0,
             0,
             MPI_COMM_WORLD,
             &status);

    /*
    ========================================================
    PRIME NUMBER CHECKING LOGIC
    ========================================================
    */

    /*
    Numbers <= 1 are NOT PRIME
    */

    if(num <= 1)
    {
        flag = 1;
    }

    /*
    Check divisibility from 2 to num/2
    */

    for(int i = 2; i <= num / 2; i++)
    {
        /*
        If divisible -> NOT PRIME
        */

        if(num % i == 0)
        {
            flag = 1;
            break;
        }
    }

    /*
    ========================================================
    DISPLAY RESULT
    ========================================================
    */

    if(flag == 0)
    {
        printf("Process %d : %d is PRIME\n",
               rank, num);
    }

    else
    {
        printf("Process %d : %d is NOT PRIME\n",
               rank, num);
    }

    /*
    ========================================================
    STEP 3: Finalize MPI
    ========================================================
    */

    MPI_Finalize();

    return 0;
}

// mpicc 5_parallel_prime_check.c

// mpirun -np 4 ./a.out