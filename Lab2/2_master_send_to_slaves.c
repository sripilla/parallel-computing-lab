/*
========================================================
Program Name : 2_master_send_to_slaves.c
Write a MPI program where the master process (process 0) sends a number to each of the slaves 
and the slave processes receive the number and prints it. Use standard send.
Aim:
Master process (Process 0) sends a number
to all slave processes using standard send.

Each slave process receives the number
and prints it.

MPI Function Used:
MPI_Send()  -> Standard Send
MPI_Recv()  -> Receive Message
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output

int main(int argc, char *argv[])
{
    int rank;          // Stores process rank
    int size;          // Stores total number of processes
    int number;        // Number to be sent
    MPI_Status status; // Stores receive status

    /*
    ========================================================
    STEP 1: Initialize MPI Environment
    ========================================================
    */

    MPI_Init(&argc, &argv);

    /*
    ========================================================
    STEP 2: Get Rank of Current Process

    rank = unique ID of each process

    Example:
    Process 0 -> rank 0
    Process 1 -> rank 1
    ========================================================
    */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ========================================================
    STEP 3: Get Total Number of Processes
    ========================================================
    */

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*
    ========================================================
    MASTER PROCESS (Process 0)
    ========================================================
    */

    if(rank == 0)
    {
        // Read number from user
        printf("Enter a number: ");
        scanf("%d", &number);

        /*
        Send number to all slave processes

        Loop starts from 1 because:
        rank 0 = master
        */

        for(int i = 1; i < size; i++)
        {
            /*
            MPI_Send Syntax:

            MPI_Send(buffer,
                     count,
                     datatype,
                     destination,
                     tag,
                     communicator);

            Sending integer 'number'
            to process i
            */

            MPI_Send(&number,
                     1,
                     MPI_INT,
                     i,
                     0,
                     MPI_COMM_WORLD);

            printf("Master sent %d to Process %d\n",
                   number, i);
        }
    }

    /*
    ========================================================
    SLAVE PROCESSES
    ========================================================
    */

    else
    {
        /*
        Receive number from master process
        */

        MPI_Recv(&number,
                 1,
                 MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD,
                 &status);

        /*
        Print received number
        */

        printf("Process %d received number %d\n",
               rank, number);
    }

    /*
    ========================================================
    STEP 4: End MPI Environment
    ========================================================
    */

    MPI_Finalize();

    return 0;
}

// mpicc 2_master_send_to_slaves.c

// mpirun -np 4 ./a.out