#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output library

/*Write a MPI program to read N values in the root process. 
Root process sends one value to each process. 
Every process receives it and finds the factorial of that number and 
returns it to the root process. Root process gathers the factorial and
 finds sum of it. Use N number of processes.*/

int main(int argc, char *argv[])
{
    int rank;                  // Rank of process
    int size;                  // Total number of processes
    int M;                     // Number of elements per process
    int A[100];                // Main array in root process
    int subArray[100];         // Array received by each process
    float localAverage;        // Average calculated by each process
    float averages[100];       // Array to store averages in root
    float totalAverage = 0;    // Final average
    int totalElements;         // Total number of elements
    int i, sum;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get rank of current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process reads M and array elements
    if(rank == 0)
    {
        // Read value of M
        printf("Enter value of M: ");
        scanf("%d", &M);

        // Total elements = N x M
        totalElements = size * M;

        printf("Enter %d elements:\n", totalElements);

        // Read array elements
        for(i = 0; i < totalElements; i++)
        {
            scanf("%d", &A[i]);
        }
    }

    // Broadcast value of M to all processes
    MPI_Bcast(
        &M,                    // Address of M
        1,                     // One value
        MPI_INT,               // Datatype
        0,                     // Root process
        MPI_COMM_WORLD         // Communicator
    );

    // Scatter M elements to each process
    MPI_Scatter(
        A,                     // Send buffer
        M,                     // M elements sent to each process
        MPI_INT,               // Datatype
        subArray,              // Receive buffer
        M,                     // Receive M elements
        MPI_INT,               // Datatype
        0,                     // Root process
        MPI_COMM_WORLD         // Communicator
    );

    // Print elements received by each process
    printf("Process %d received: ", rank);

    for(i = 0; i < M; i++)
    {
        printf("%d ", subArray[i]);
    }

    printf("\n");

    // Calculate local sum
    sum = 0;

    for(i = 0; i < M; i++)
    {
        sum = sum + subArray[i];
    }

    // Calculate local average
    localAverage = (float)sum / M;

    // Print local average
    printf("Process %d local average = %.2f\n",
           rank, localAverage);

    // Gather all averages in root process
    MPI_Gather(
        &localAverage,         // Send local average
        1,                     // One value
        MPI_FLOAT,             // Datatype
        averages,              // Receive buffer in root
        1,                     // One value from each process
        MPI_FLOAT,             // Datatype
        0,                     // Root process
        MPI_COMM_WORLD         // Communicator
    );

    // Root process calculates total average
    if(rank == 0)
    {
        printf("\nAverages received in root process:\n");

        for(i = 0; i < size; i++)
        {
            printf("%.2f ", averages[i]);

            totalAverage = totalAverage + averages[i];
        }

        // Final total average
        totalAverage = totalAverage / size;

        printf("\n\nTotal Average = %.2f\n",
               totalAverage);
    }

    // End MPI environment
    MPI_Finalize();

    return 0;
}

//mpicc 2_mpicc_average_collective.c

//mpirun -np 4 ./a.out

/* Sample Input
Enter value of M: 2

Enter 8 elements:
1 2 3 4 5 6 7 8
*/

/*Sample Output
Process 0 received: 1 2
Process 1 received: 3 4
Process 2 received: 5 6
Process 3 received: 7 8

Process 0 local average = 1.50
Process 1 local average = 3.50
Process 2 local average = 5.50
Process 3 local average = 7.50

Averages received in root process:
1.50 3.50 5.50 7.50

Total Average = 4.50*/