/*
========================================================
Program Name : 8_standard_send_deadlock.c
Implement at least 2 programs to identify deadlock conditions in synchronous send 
and standard send with multiple point to point communications between two processes
Aim:
Demonstrate deadlock using standard send
with multiple point-to-point communications.

Both processes try to send large messages first.

Possible Result:
DEADLOCK
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output

#define SIZE 1000000

int main(int argc, char *argv[])
{
    int rank;                  // Rank of current process

    /*
    Large arrays increase chance of deadlock
    because MPI may avoid internal buffering
    */

    int send_data[SIZE];
    int recv_data[SIZE];

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
        printf("Process 0 sending large message...\n");

        /*
        Standard send to Process 1
        */

        MPI_Send(send_data,
                 SIZE,
                 MPI_INT,
                 1,
                 0,
                 MPI_COMM_WORLD);

        /*
        Receive from Process 1
        */

        MPI_Recv(recv_data,
                 SIZE,
                 MPI_INT,
                 1,
                 0,
                 MPI_COMM_WORLD,
                 &status);

        printf("Process 0 completed\n");
    }

    /*
    ========================================================
    PROCESS 1
    ========================================================
    */

    else if(rank == 1)
    {
        printf("Process 1 sending large message...\n");

        /*
        Standard send to Process 0
        */

        MPI_Send(send_data,
                 SIZE,
                 MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD);

        /*
        Receive from Process 0
        */

        MPI_Recv(recv_data,
                 SIZE,
                 MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD,
                 &status);

        printf("Process 1 completed\n");
    }

    /*
    ========================================================
    FINALIZE MPI
    ========================================================
    */

    MPI_Finalize();

    return 0;
}

// mpicc 8_standard_send_deadlock.c

// mpirun -np 2 ./a.out