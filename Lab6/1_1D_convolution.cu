#include <stdio.h>
#include <cuda_runtime.h>

#define WIDTH 8
#define MASK_WIDTH 3

// CUDA Kernel for 1D Convolution
__global__ void convolution1D(int *N, int *M, int *P, int width)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < width)
    {
        int sum = 0;

        for (int j = 0; j < MASK_WIDTH; j++)
        {
            int idx = i - MASK_WIDTH / 2 + j;

            if (idx >= 0 && idx < width)
                sum += N[idx] * M[j];
        }

        P[i] = sum;
    }
}

int main()
{
    int h_N[WIDTH] = {1, 2, 3, 4, 5, 6, 7, 8};
    int h_M[MASK_WIDTH] = {1, 0, -1};
    int h_P[WIDTH];

    int *d_N, *d_M, *d_P;

    // Allocate device memory
    cudaMalloc((void **)&d_N, WIDTH * sizeof(int));
    cudaMalloc((void **)&d_M, MASK_WIDTH * sizeof(int));
    cudaMalloc((void **)&d_P, WIDTH * sizeof(int));

    // Copy data from host to device
    cudaMemcpy(d_N, h_N, WIDTH * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, MASK_WIDTH * sizeof(int), cudaMemcpyHostToDevice);

    // Launch kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (WIDTH + threadsPerBlock - 1) / threadsPerBlock;

    convolution1D<<<blocksPerGrid, threadsPerBlock>>>(d_N, d_M, d_P, WIDTH);

    // Copy result back to host
    cudaMemcpy(h_P, d_P, WIDTH * sizeof(int), cudaMemcpyDeviceToHost);

    // Display result
    printf("Output Array:\n");
    for (int i = 0; i < WIDTH; i++)
    {
        printf("%d ", h_P[i]);
    }
    printf("\n");

    // Free memory
    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    return 0;
}