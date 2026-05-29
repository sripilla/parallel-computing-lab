/*======================================================================
LAB 4 - Exercise Question 4

Program:
Write a MPI program to read a word of length N.

Using N processes (including root), generate the output pattern:

Example:

Input  : PCAP

Output : PCCAAAPPPP

Logic:
P -> repeated 1 time
C -> repeated 2 times
A -> repeated 3 times
P -> repeated 4 times

Result:
P + CC + AAA + PPPP = PCCAAAPPPP

MPI Concepts Used:
1. MPI_Scatter
2. MPI_Gather

Compilation:
mpicc 4_word_pattern_using_scatter_gather.c -o word_pattern

Execution:
mpirun --oversubscribe -np 4 ./word_pattern
======================================================================*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;                   // Process ID
    int size;                   // Number of processes

    char word[100];             // Input word

    char my_char;               // Character received by process

    char local_pattern[100];    // Local repeated pattern

    char gathered[1000];        // Gathered result at root

    int recvcounts[100];
    int displs[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*----------------------------------------------------------
    Root process reads the word
    ----------------------------------------------------------*/
    if(rank == 0)
    {
        printf("Enter a word: ");
        scanf("%s", word);

        int len = strlen(word);

        /*------------------------------------------------------
        Number of processes must equal word length
        ------------------------------------------------------*/
        if(len != size)
        {
            printf("\nERROR:\n");
            printf("Word length = %d\n", len);
            printf("Processes   = %d\n", size);
            printf("Run with exactly %d processes.\n", len);

            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    /*----------------------------------------------------------
    Send one character to each process
    ----------------------------------------------------------*/
    MPI_Scatter(
        word,
        1,
        MPI_CHAR,
        &my_char,
        1,
        MPI_CHAR,
        0,
        MPI_COMM_WORLD
    );

    /*----------------------------------------------------------
    Create local pattern

    Rank 0 -> repeat 1 time
    Rank 1 -> repeat 2 times
    Rank 2 -> repeat 3 times
    ...
    ----------------------------------------------------------*/
    for(int i = 0; i <= rank; i++)
    {
        local_pattern[i] = my_char;
    }

    local_pattern[rank + 1] = '\0';

    int local_length = rank + 1;

    /*----------------------------------------------------------
    Root prepares counts and displacements
    ----------------------------------------------------------*/
    if(rank == 0)
    {
        int position = 0;

        for(int i = 0; i < size; i++)
        {
            recvcounts[i] = i + 1;

            displs[i] = position;

            position += recvcounts[i];
        }
    }

    /*----------------------------------------------------------
    Gather all repeated strings
    ----------------------------------------------------------*/
    MPI_Gatherv(
        local_pattern,
        local_length,
        MPI_CHAR,
        gathered,
        recvcounts,
        displs,
        MPI_CHAR,
        0,
        MPI_COMM_WORLD
    );

    /*----------------------------------------------------------
    Root displays final word
    ----------------------------------------------------------*/
    if(rank == 0)
    {
        int total_length = size * (size + 1) / 2;

        gathered[total_length] = '\0';

        printf("\nOutput Word: %s\n", gathered);
    }

    MPI_Finalize();

    return 0;
}