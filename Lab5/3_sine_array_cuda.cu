#include <stdio.h>
#include <math.h>
#include <cuda_runtime.h>

// CUDA Program to Compute Sine of Angles (in Radians) for a 1D Array

__global__ void computeSine(float *input, float *output, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
    {
        output[i] = sinf(input[i]);
    }
}

int main()
{
    int N = 5;
    int size = N * sizeof(float);

    float h_input[] = {0.0, 0.5236, 0.7854, 1.5708, 3.1416};
    float h_output[5];

    float *d_input, *d_output;

    cudaMalloc((void**)&d_input, size);
    cudaMalloc((void**)&d_output, size);

    cudaMemcpy(d_input, h_input, size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    computeSine<<<blocksPerGrid, threadsPerBlock>>>(d_input, d_output, N);

    cudaMemcpy(h_output, d_output, size, cudaMemcpyDeviceToHost);

    printf("Angle (rad)\tSine Value\n");

    for(int i = 0; i < N; i++)
    {
        printf("%f\t%f\n", h_input[i], h_output[i]);
    }

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}