#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;

    // Start MPI environment
    MPI_Init(&argc, &argv);

    // Get process rank (ID)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print message from each process
    printf("Hello from process %d out of %d processes\n", rank, size);

    // End MPI environment
    MPI_Finalize();

    return 0;
}
