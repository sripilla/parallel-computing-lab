#include <stdio.h>
#include <cuda_runtime.h>

__global__ void oddEvenSort(int *arr, int phase, int n)
{
    int tid = threadIdx.x;

    int i;

    if (phase % 2 == 0)
        i = 2 * tid;      // Even phase
    else
        i = 2 * tid + 1;  // Odd phase

    if (i + 1 < n)
    {
        if (arr[i] > arr[i + 1])
        {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

int main()
{
    int n = 8;
    int h_arr[] = {64, 34, 25, 12, 22, 11, 90, 5};

    int *d_arr;

    cudaMalloc((void**)&d_arr, n * sizeof(int));

    cudaMemcpy(d_arr, h_arr, n * sizeof(int),
               cudaMemcpyHostToDevice);

    int threads = n / 2;

    for (int phase = 0; phase < n; phase++)
    {
        oddEvenSort<<<1, threads>>>(d_arr, phase, n);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(h_arr, d_arr, n * sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Sorted Array:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", h_arr[i]);

    printf("\n");

    cudaFree(d_arr);

    return 0;
}