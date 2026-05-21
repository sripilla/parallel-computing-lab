#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output
#include <string.h>   // String handling functions
/*
Write a MPI program to read a string. Using N processes (string length is evenly 
divisible by N), 
find the number of non-vowels in the string. 
In the root process print number of non-vowels found by each process and print
the total number of non-vowels.
*/
int main(int argc, char *argv[])
{
    int rank;                  // Rank of current process
    int size;                  // Total number of processes

    char str[100];             // Original string in root
    char subStr[100];          // Part of string received by each process

    int length;                // Length of string
    int charsPerProcess;       // Characters sent to each process

    int localCount = 0;        // Non-vowel count in each process
    int counts[100];           // Array to store counts in root

    int totalCount = 0;        // Final total non-vowel count

    int i;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get rank of current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process reads string
    if(rank == 0)
    {
        printf("Enter a string: ");
        scanf("%s", str);

        // Find length of string
        length = strlen(str);

        // Check divisibility condition
        if(length % size != 0)
        {
            printf("String length is not divisible by "
                   "number of processes\n");
        }

        // Calculate characters per process
        charsPerProcess = length / size;
    }

    // Broadcast charsPerProcess to all processes
    MPI_Bcast(
        &charsPerProcess,      // Variable to send
        1,                     // One value
        MPI_INT,               // Datatype
        0,                     // Root process
        MPI_COMM_WORLD         // Communicator
    );

    // Scatter equal characters to all processes
    MPI_Scatter(
        str,                   // Send buffer
        charsPerProcess,       // Characters per process
        MPI_CHAR,              // Datatype
        subStr,                // Receive buffer
        charsPerProcess,       // Characters received
        MPI_CHAR,              // Datatype
        0,                     // Root process
        MPI_COMM_WORLD         // Communicator
    );

    // Add null character at end of substring
    subStr[charsPerProcess] = '\0';

    // Print substring received by process
    printf("Process %d received substring = %s\n",
           rank, subStr);

    // Count non-vowels in substring
    for(i = 0; i < charsPerProcess; i++)
    {
        char ch = subStr[i];

        // Convert uppercase vowels also
        if(ch!='a' && ch!='e' && ch!='i' &&
           ch!='o' && ch!='u' &&
           ch!='A' && ch!='E' && ch!='I' &&
           ch!='O' && ch!='U')
        {
            localCount++;
        }
    }

    // Print local non-vowel count
    printf("Process %d non-vowel count = %d\n",
           rank, localCount);

    // Gather counts in root process
    MPI_Gather(
        &localCount,           // Send local count
        1,                     // One value
        MPI_INT,               // Datatype
        counts,                // Receive array
        1,                     // One value from each process
        MPI_INT,               // Datatype
        0,                     // Root process
        MPI_COMM_WORLD         // Communicator
    );

    // Root process prints all counts and total
    if(rank == 0)
    {
        printf("\nCounts received in root process:\n");

        for(i = 0; i < size; i++)
        {
            printf("Process %d -> %d\n",
                   i, counts[i]);

            // Add local count to total
            totalCount = totalCount + counts[i];
        }

        // Print final total
        printf("\nTotal non-vowels = %d\n",
               totalCount);
    }

    // End MPI environment
    MPI_Finalize();

    return 0;
}

// mpicc 3_mpicc_non_vowel_count.c

// mpirun -np 4 ./a.out