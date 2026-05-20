/*
========================================================
Program Name : 1_synchronous_word_toggle.c
Write a MPI program using synchronous send. 
The sender process sends a word to the receiver. 
The second process receives the word, toggles each letter of the word 
and sends it back to the first process. Both processes use synchronous send operations.

Aim          : Demonstrate synchronous send in MPI

Description:
Process 0 sends a word to Process 1.
Process 1 receives the word, toggles the case
of each character, and sends it back.

Both communications use MPI_Ssend().
========================================================
*/

#include <mpi.h>      // MPI library
#include <stdio.h>    // Standard input/output
#include <string.h>   // strlen()
#include <ctype.h>    // islower(), toupper(), tolower()

int main(int argc, char *argv[])
{
    int rank;                  // Stores process rank
    char word[100];            // Character array to store word
    MPI_Status status;         // Stores receive status information

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get rank (process ID)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    ========================================================
    PROCESS 0  --> Sender
    ========================================================
    */
    if(rank == 0)
    {
        // Read word from user
        printf("Enter a word: ");
        scanf("%s", word);

        /*
        MPI_Ssend Syntax:
        MPI_Ssend(buffer, count, datatype,
                  destination, tag, communicator);

        Sends word synchronously to Process 1
        */

        MPI_Ssend(word,
                  strlen(word) + 1,
                  MPI_CHAR,
                  1,
                  0,
                  MPI_COMM_WORLD);

        printf("Process 0 sent word: %s\n", word);

        /*
        Receive modified word back from Process 1
        */

        MPI_Recv(word,
                 100,
                 MPI_CHAR,
                 1,
                 0,
                 MPI_COMM_WORLD,
                 &status);

        // Print modified word
        printf("Process 0 received modified word: %s\n", word);
    }

    /*
    ========================================================
    PROCESS 1  --> Receiver
    ========================================================
    */
    else if(rank == 1)
    {
        /*
        Receive word from Process 0
        */

        MPI_Recv(word,
                 100,
                 MPI_CHAR,
                 0,
                 0,
                 MPI_COMM_WORLD,
                 &status);

        printf("Process 1 received word: %s\n", word);

        /*
        Toggle case of each character

        Example:
        Hello --> hELLO
        */

        for(int i = 0; word[i] != '\0'; i++)
        {
            // If lowercase -> convert to uppercase
            if(islower(word[i]))
            {
                word[i] = toupper(word[i]);
            }

            // Else uppercase -> convert to lowercase
            else
            {
                word[i] = tolower(word[i]);
            }
        }

        /*
        Send modified word back synchronously
        */

        MPI_Ssend(word,
                  strlen(word) + 1,
                  MPI_CHAR,
                  0,
                  0,
                  MPI_COMM_WORLD);

        printf("Process 1 sent modified word: %s\n", word);
    }

    // End MPI environment
    MPI_Finalize();

    return 0;
}

