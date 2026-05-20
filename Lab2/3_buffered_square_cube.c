/*
========================================================
Program Name : 3_buffered_square_cube.c
Write a MPI program to read N elements of the array in the root process (process 0) where
N is equal to the total number of processes. 
The root process sends one value to each of the slaves.
Let even ranked process finds square of the received

Aim:
Root process reads N elements where
N = total number of processes.

Root sends one element to each process
using Buffered Send (MPI_Bsend).

Even ranked process:
    Finds square

Odd ranked process:
    Finds cube
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output
#include <stdlib.h>   // malloc()

int main(int argc, char *argv[])
{
    int rank;              // Process rank
    int size;              // Total number of processes
    int num;               // Number received by each process
    int arr[100];          // Array to store elements
    int result;            // Stores square/cube result

    MPI_Status status;

    /*
    ========================================================
    BUFFER VARIABLES FOR MPI_Bsend
    ========================================================
    */

    int buffer_size;
    char *buffer;

    /*
    ========================================================
    STEP 1: Initialize MPI
    ========================================================
    */

    MPI_Init(&argc, &argv);

    /*
    ========================================================
    STEP 2: Get Rank and Size
    ========================================================
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*
    ========================================================
    STEP 3: Calculate Buffer Size

    MPI_BSEND_OVERHEAD
    -> Extra memory needed internally by MPI
    ========================================================
    */

    buffer_size = size * (sizeof(int) + MPI_BSEND_OVERHEAD);

    /*
    Allocate memory for buffer
    */

    buffer = (char *)malloc(buffer_size);

    /*
    Attach buffer to MPI
    */

    MPI_Buffer_attach(buffer, buffer_size);

    /*
    ========================================================
    ROOT PROCESS (Process 0)
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
        using MPI_Bsend()
        */

        for(int i = 0; i < size; i++)
        {
            MPI_Bsend(&arr[i],
                      1,
                      MPI_INT,
                      i,
                      0,
                      MPI_COMM_WORLD);

            printf("Root sent %d to Process %d\n",
                   arr[i], i);
        }
    }

    /*
    ========================================================
    ALL PROCESSES RECEIVE DATA
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
    EVEN RANK -> SQUARE
    ODD RANK  -> CUBE
    ========================================================
    */

    if(rank % 2 == 0)
    {
        result = num * num;

        printf("Process %d is EVEN\n",
               rank);

        printf("Square of %d = %d\n",
               num, result);
    }

    else
    {
        result = num * num * num;

        printf("Process %d is ODD\n",
               rank);

        printf("Cube of %d = %d\n",
               num, result);
    }

    /*
    ========================================================
    DETACH BUFFER
    ========================================================
    */

    MPI_Buffer_detach(&buffer, &buffer_size);

    /*
    Free allocated memory
    */

    free(buffer);

    /*
    ========================================================
    FINALIZE MPI
    ========================================================
    */

    MPI_Finalize();

    return 0;
}

//mpicc 3_buffered_square_cube.c

//mpirun -np 4 ./a.out