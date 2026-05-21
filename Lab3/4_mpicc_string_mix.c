#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output
#include <string.h>   // String functions

/*
Write a MPI Program to read two strings S1 and S2 of same length in the root process. 
Using N processes including the root (string length is evenly divisible by N), 
produce the resultant string as shown below. 
Display the resultant string in the root process. Use Collective communication routines.
Example:
String SI: string
String S2: length
Resultant String : slternigntgh
*/

int main(int argc, char *argv[])
{
    int rank;                  // Rank of process
    int size;                  // Total number of processes

    char S1[100];              // First string
    char S2[100];              // Second string

    char part1[100];           // Substring from S1
    char part2[100];           // Substring from S2

    char mixedPart[200];       // Mixed substring by each process

    char result[200];          // Final resultant string

    int length;                // Length of strings
    int charsPerProcess;       // Characters per process

    int i, j;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get process rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process reads strings
    if(rank == 0)
    {
        printf("Enter first string: ");
        scanf("%s", S1);

        printf("Enter second string: ");
        scanf("%s", S2);

        // Find length of string
        length = strlen(S1);

        // Check equal length condition
        if(length != strlen(S2))
        {
            printf("Strings are not of same length\n");
        }

        // Check divisibility condition
        if(length % size != 0)
        {
            printf("String length not divisible by "
                   "number of processes\n");
        }

        // Calculate characters per process
        charsPerProcess = length / size;
    }

    // Broadcast charsPerProcess to all processes
    MPI_Bcast(
        &charsPerProcess,
        1,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    // Scatter S1 among processes
    MPI_Scatter(
        S1,                    // Send buffer
        charsPerProcess,       // Characters sent
        MPI_CHAR,
        part1,                 // Receive buffer
        charsPerProcess,
        MPI_CHAR,
        0,
        MPI_COMM_WORLD
    );

    // Scatter S2 among processes
    MPI_Scatter(
        S2,
        charsPerProcess,
        MPI_CHAR,
        part2,
        charsPerProcess,
        MPI_CHAR,
        0,
        MPI_COMM_WORLD
    );

    // Add null character
    part1[charsPerProcess] = '\0';
    part2[charsPerProcess] = '\0';

    // Print received parts
    printf("Process %d received:\n", rank);
    printf("Part from S1 = %s\n", part1);
    printf("Part from S2 = %s\n", part2);

    // Mix strings alternately
    j = 0;

    for(i = 0; i < charsPerProcess; i++)
    {
        mixedPart[j++] = part1[i];
        mixedPart[j++] = part2[i];
    }

    // Add null character
    mixedPart[j] = '\0';

    // Print mixed part
    printf("Process %d mixed part = %s\n",
           rank, mixedPart);

    // Gather all mixed parts into root
    MPI_Gather(
        mixedPart,                     // Send buffer
        2 * charsPerProcess,          // Characters sent
        MPI_CHAR,
        result,                       // Receive buffer
        2 * charsPerProcess,          // Characters received
        MPI_CHAR,
        0,
        MPI_COMM_WORLD
    );

    // Root process prints final result
    if(rank == 0)
    {
        // Add null character
        result[2 * length] = '\0';

        printf("\nResultant String = %s\n",
               result);
    }

    // End MPI environment
    MPI_Finalize();

    return 0;
}

// mpicc 4_mpicc_string_mix.c

// mpirun -np 3 ./a.out

