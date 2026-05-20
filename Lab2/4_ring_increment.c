/*
========================================================
Program Name : 4_ring_increment.c
Write a MPI program to read an integer value in the root process. 
Root process sends this value to Process, ProcessI sends this value to Process2 and so on. 
Last process sends the value back to root process. 
When sending the value each process will first increment the received value by one. 
Write the program using point to point communication routines.

Aim:
Root process reads an integer value.

Process flow:
P0 -> P1 -> P2 -> ... -> Last Process -> P0

Each process:
1. Receives value
2. Increments value by 1
3. Sends to next process

Last process sends final value
back to root process.
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output

int main(int argc, char *argv[])
{
    int rank;              // Rank of current process
    int size;              // Total number of processes
    int value;             // Integer value passed between processes

    MPI_Status status;

    /*
    ========================================================
    STEP 1: Initialize MPI
    ========================================================
    */

    MPI_Init(&argc, &argv);

    /*
    ========================================================
    STEP 2: Get Process Rank and Total Processes
    ========================================================
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*
    ========================================================
    ROOT PROCESS (PROCESS 0)
    ========================================================
    */

    if(rank == 0)
    {
        /*
        Read integer from user
        */

        printf("Enter an integer value: ");
        scanf("%d", &value);

        printf("\nProcess 0 initial value = %d\n",
               value);

        /*
        Increment value before sending
        */

        value++;

        /*
        Send incremented value to Process 1
        */

        MPI_Send(&value,
                 1,
                 MPI_INT,
                 1,
                 0,
                 MPI_COMM_WORLD);

        printf("Process 0 sent value %d to Process 1\n",
               value);

        /*
        Receive final value from last process
        */

        MPI_Recv(&value,
                 1,
                 MPI_INT,
                 size - 1,
                 0,
                 MPI_COMM_WORLD,
                 &status);

        /*
        Print final received value
        */

        printf("\nProcess 0 received final value = %d\n",
               value);
    }

    /*
    ========================================================
    ALL OTHER PROCESSES
    ========================================================
    */

    else
    {
        /*
        Receive value from previous process

        Example:
        Process 2 receives from Process 1
        */

        MPI_Recv(&value,
                 1,
                 MPI_INT,
                 rank - 1,
                 0,
                 MPI_COMM_WORLD,
                 &status);

        printf("Process %d received value %d\n",
               rank, value);

        /*
        Increment value
        */

        value++;

        /*
        IF NOT LAST PROCESS
        Send to next process
        */

        if(rank != size - 1)
        {
            MPI_Send(&value,
                     1,
                     MPI_INT,
                     rank + 1,
                     0,
                     MPI_COMM_WORLD);

            printf("Process %d sent value %d to Process %d\n",
                   rank,
                   value,
                   rank + 1);
        }

        /*
        LAST PROCESS
        Sends value back to root process
        */

        else
        {
            MPI_Send(&value,
                     1,
                     MPI_INT,
                     0,
                     0,
                     MPI_COMM_WORLD);

            printf("Last Process %d sent final value %d back to Process 0\n",
                   rank,
                   value);
        }
    }

    /*
    ========================================================
    STEP 3: Finalize MPI
    ========================================================
    */

    MPI_Finalize();

    return 0;
}

// mpicc 4_ring_increment.c

// mpirun -np 4 ./a.out