/*======================================================================
LAB 4 - Exercise Question 2

Program:
Write an MPI program to read a 3 x 3 matrix.
Enter an element to be searched in the root process.
Find the number of occurrences of this element in the matrix
using three processes.

Concepts Used:
1. MPI_Bcast()
2. MPI_Scatter()
3. MPI_Reduce()
4. Parallel Searching

Compilation:
mpicc 2_matrix_element_occurrence_count.c -o matrix_search

Execution:
mpirun --oversubscribe -np 3 ./matrix_search

======================================================================*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;                   // Process ID
    int size;                   // Number of processes

    int matrix[3][3];           // 3x3 matrix
    int row[3];                 // Row received by each process

    int search_element;         // Element to search
    int local_count = 0;        // Count found by each process
    int total_count = 0;        // Final count

    /*--------------------------------------------------------------
    Initialize MPI Environment
    --------------------------------------------------------------*/
    MPI_Init(&argc, &argv);

    /*--------------------------------------------------------------
    Get Process Rank
    --------------------------------------------------------------*/
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*--------------------------------------------------------------
    Get Total Number of Processes
    --------------------------------------------------------------*/
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*--------------------------------------------------------------
    Ensure exactly 3 processes are used
    --------------------------------------------------------------*/
    if(size != 3)
    {
        if(rank == 0)
        {
            printf("ERROR: Run the program with exactly 3 processes.\n");
        }

        MPI_Finalize();
        return 0;
    }

    /*--------------------------------------------------------------
    Root process inputs matrix and search element
    --------------------------------------------------------------*/
    if(rank == 0)
    {
        printf("Enter the 3x3 matrix elements:\n");

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("Enter element to search: ");
        scanf("%d", &search_element);
    }

    /*--------------------------------------------------------------
    Broadcast search element to all processes
    --------------------------------------------------------------*/
    MPI_Bcast(
        &search_element,
        1,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    /*--------------------------------------------------------------
    Scatter matrix rows

    Process 0 gets Row 1
    Process 1 gets Row 2
    Process 2 gets Row 3
    --------------------------------------------------------------*/
    MPI_Scatter(
        matrix,
        3,
        MPI_INT,
        row,
        3,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    /*--------------------------------------------------------------
    Search element in received row
    --------------------------------------------------------------*/
    for(int i = 0; i < 3; i++)
    {
        if(row[i] == search_element)
        {
            local_count++;
        }
    }

    /*--------------------------------------------------------------
    Display local count of each process
    --------------------------------------------------------------*/
    printf("Process %d found %d occurrence(s)\n",
           rank,
           local_count);

    /*--------------------------------------------------------------
    Sum all local counts at root process
    --------------------------------------------------------------*/
    MPI_Reduce(
        &local_count,
        &total_count,
        1,
        MPI_INT,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    /*--------------------------------------------------------------
    Root process prints final answer
    --------------------------------------------------------------*/
    if(rank == 0)
    {
        printf("\nTotal occurrences of %d = %d\n",
               search_element,
               total_count);
    }

    /*--------------------------------------------------------------
    Terminate MPI Environment
    --------------------------------------------------------------*/
    MPI_Finalize();

    return 0;
}