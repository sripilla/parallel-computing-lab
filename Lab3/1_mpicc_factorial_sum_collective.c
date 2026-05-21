#include <mpi.h>      // Header file for MPI functions
#include <stdio.h>    // Header file for standard input/output

/*
Write a MPI program to read N values in the root process. 
Root process sends one value to each process. 
Every process receives it and finds the factorial of that number and 
returns it to the root process. Root process gathers the factorial and 
finds sum of it. Use N number of processes.
*/

// Function to calculate factorial
int factorial(int n)
{
    int fact = 1;
    int i;

    // Loop to calculate factorial
    for(i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    return fact;
}

int main(int argc, char *argv[])
{
    int rank;              // Rank (ID) of process
    int size;              // Total number of processes
    int A[100];            // Array to store input numbers in root
    int B[100];            // Array to store factorials in root
    int num;               // Number received by each process
    int fact;              // Factorial calculated by each process
    int sum = 0;           // Sum of factorials
    int i;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get rank of current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process reads input values
    if(rank == 0)
    {
        printf("Enter %d numbers:\n", size);

        // Read N numbers where N = number of processes
        for(i = 0; i < size; i++)
        {
            scanf("%d", &A[i]);
        }
    }

    // Scatter one number to each process
    MPI_Scatter(
        A,                  // Send buffer (root array)
        1,                  // Number of elements sent to each process
        MPI_INT,            // Datatype of send buffer
        &num,               // Receive buffer
        1,                  // Number of elements received
        MPI_INT,            // Datatype of receive buffer
        0,                  // Root process rank
        MPI_COMM_WORLD      // Communicator
    );

    // Print received value in each process
    printf("Process %d received number %d\n", rank, num);

    // Each process calculates factorial
    fact = factorial(num);

    // Print factorial calculated by each process
    printf("Process %d calculated factorial = %d\n", rank, fact);

    // Gather factorials back to root process
    MPI_Gather(
        &fact,              // Send buffer
        1,                  // Number of elements to send
        MPI_INT,            // Datatype
        B,                  // Receive buffer in root
        1,                  // Number of elements received from each process
        MPI_INT,            // Datatype
        0,                  // Root process
        MPI_COMM_WORLD      // Communicator
    );

    // Root process prints factorials and calculates sum
    if(rank == 0)
    {
        printf("\nFactorials gathered in root process:\n");

        for(i = 0; i < size; i++)
        {
            printf("%d ", B[i]);

            // Add factorial to sum
            sum = sum + B[i];
        }

        // Print final sum
        printf("\n\nSum of factorials = %d\n", sum);
    }

    // End MPI environment
    MPI_Finalize();

    return 0;
}


// mpicc 1_mpicc_factorial_sum_collective.c

// mpirun -np 4 ./a.out


/* Sample Input
1 2 3 4
*/

/* Sample Output
Process 0 received 1
Process 1 received 2
Process 2 received 3
Process 3 received 4

Squared values:
1 4 9 16
*/