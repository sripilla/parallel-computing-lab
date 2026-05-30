#include <stdio.h>
#include <cuda_runtime.h>

__global__ void selectionSort(int *arr, int n)
{
    int i = threadIdx.x;

    if (i < n - 1)
    {
        int min_idx = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main()
{
    int n = 8;
    int h_arr[] = {64, 25, 12, 22, 11, 90, 34, 5};

    int *d_arr;

    cudaMalloc((void**)&d_arr, n * sizeof(int));

    cudaMemcpy(d_arr, h_arr, n * sizeof(int),
               cudaMemcpyHostToDevice);

    selectionSort<<<1, n>>>(d_arr, n);

    cudaMemcpy(h_arr, d_arr, n * sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Sorted Array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", h_arr[i]);

    printf("\n");

    cudaFree(d_arr);

    return 0;
}