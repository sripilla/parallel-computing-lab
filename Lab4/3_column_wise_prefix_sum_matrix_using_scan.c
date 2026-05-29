/*======================================================================
LAB 4 - Exercise Question 3

Program:
Write a MPI program to read a 4 x 4 matrix and display the output
shown in the question using four processes.

Input Matrix Example:

1 2 3 4
1 2 3 1
1 1 1 1
2 1 2 1

Output Matrix:

1 2 3 4
2 4 6 5
3 5 7 6
5 6 9 7

Explanation:
The output is obtained by performing COLUMN-WISE PREFIX SUMS.

Column 1:
1
1+1=2
1+1+1=3
1+1+1+2=5

Column 2:
2
2+2=4
2+2+1=5
2+2+1+1=6

MPI Concept Used:
MPI_Scatter()  -> Distribute one row to each process
MPI_Scan()     -> Compute prefix sums
MPI_Gather()   -> Collect results at root process

Compilation:
mpicc 3_column_wise_prefix_sum_matrix_using_scan.c -o matrix_prefix

Execution:
mpirun --oversubscribe -np 4 ./matrix_prefix
======================================================================*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;               // Process ID
    int size;               // Number of processes

    int matrix[4][4];       // Input matrix
    int local_row[4];       // Row received by each process

    int prefix_row[4];      // Prefix sum row

    int result[4][4];       // Final output matrix

    /*--------------------------------------------------------------
    Initialize MPI
    --------------------------------------------------------------*/
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*--------------------------------------------------------------
    Ensure exactly 4 processes
    --------------------------------------------------------------*/
    if(size != 4)
    {
        if(rank == 0)
        {
            printf("ERROR: Run with exactly 4 processes.\n");
        }

        MPI_Finalize();
        return 0;
    }

    /*--------------------------------------------------------------
    Root process reads 4 x 4 matrix
    --------------------------------------------------------------*/
    if(rank == 0)
    {
        printf("Enter 4 x 4 matrix elements:\n");

        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }
    }

    /*--------------------------------------------------------------
    Scatter one row to each process

    Process 0 -> Row 1
    Process 1 -> Row 2
    Process 2 -> Row 3
    Process 3 -> Row 4
    --------------------------------------------------------------*/
    MPI_Scatter(
        matrix,
        4,
        MPI_INT,
        local_row,
        4,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    /*--------------------------------------------------------------
    MPI_Scan performs element-wise prefix sum

    Example:

    Row1 = [1 2 3 4]

    Row2 = [1 2 3 1]

    Scan result at Process 1:
    [2 4 6 5]
    --------------------------------------------------------------*/
    MPI_Scan(
        local_row,
        prefix_row,
        4,
        MPI_INT,
        MPI_SUM,
        MPI_COMM_WORLD
    );

    /*--------------------------------------------------------------
    Gather prefix rows back to root process
    --------------------------------------------------------------*/
    MPI_Gather(
        prefix_row,
        4,
        MPI_INT,
        result,
        4,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    /*--------------------------------------------------------------
    Root process prints output matrix
    --------------------------------------------------------------*/
    if(rank == 0)
    {
        printf("\nOutput Matrix:\n");

        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }

    /*--------------------------------------------------------------
    Terminate MPI
    --------------------------------------------------------------*/
    MPI_Finalize();

    return 0;
}