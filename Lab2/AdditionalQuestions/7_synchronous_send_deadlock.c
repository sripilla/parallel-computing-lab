/*
========================================================
Program Name : 7_synchronous_send_deadlock.c
Implement at least 2 programs to identify deadlock conditions in synchronous send 
and standard send with multiple point to point communications between two processes
Aim:
Demonstrate deadlock using synchronous send.

Both processes perform MPI_Ssend() first.
Since synchronous send waits for receiver,
both processes wait forever.

Result:
DEADLOCK
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output

int main(int argc, char *argv[])
{
    int rank;              // Rank of current process
    int data = 100;        // Data to send
    int recv_data;         // Variable to receive data

    MPI_Status status;

    /*
    ========================================================
    STEP 1: Initialize MPI
    ========================================================
    */

    MPI_Init(&argc, &argv);

    /*
    ========================================================
    STEP 2: Get Rank
    ========================================================
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ========================================================
    PROCESS 0
    ========================================================
    */

    if(rank == 0)
    {
        printf("Process 0 trying synchronous send...\n");

        /*
        MPI_Ssend waits until receiver is ready.

        But Process 1 is ALSO waiting in MPI_Ssend.
        */

        MPI_Ssend(&data,
                  1,
                  MPI_INT,
                  1,
                  0,
                  MPI_COMM_WORLD);

        /*
        This line never executes due to deadlock
        */

        MPI_Recv(&recv_data,
                 1,
                 MPI_INT,
                 1,
                 0,
                 MPI_COMM_WORLD,
                 &status);
    }

    /*
    ========================================================
    PROCESS 1
    ========================================================
    */

    else if(rank == 1)
    {
        printf("Process 1 trying synchronous send...\n");

        /*
        Process 1 also waits forever
        */

        MPI_Ssend(&data,
                  1,
                  MPI_INT,
                  0,
                  0,
                  MPI_COMM_WORLD);

        /*
        This line never executes
        */

        MPI_Recv(&recv_data,
                 1,
                 MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD,
                 &status);
    }

    /*
    ========================================================
    PROGRAM NEVER REACHES HERE
    ========================================================
    */

    MPI_Finalize();

    return 0;
}

// mpicc 7_synchronous_send_deadlock.c

// mpirun -np 2 ./a.out