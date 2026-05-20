#include <stdio.h>      // Standard input/output library
#include <mpi.h>        // MPI library

// Main function
int main(int argc, char *argv[])
{
    int rank;   // Stores process ID (rank)
    int size;   // Stores total number of processes

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank (ID) of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print message from each process
    printf("Hello from process %d out of %d\n", rank, size);

    // Finalize MPI environment
    MPI_Finalize();

    return 0;   // End program successfully
}