#include <stdio.h>
#include <cuda_runtime.h>
// Block size = N (single block with N threads)
__global__ void vectorAdd(float *A, float *B, float *C, int N)
{
    int i = threadIdx.x;

    if (i < N)
        C[i] = A[i] + B[i];
}

int main()
{
    int N = 8;
    size_t size = N * sizeof(float);

    float h_A[8] = {1,2,3,4,5,6,7,8};
    float h_B[8] = {10,20,30,40,50,60,70,80};
    float h_C[8];

    float *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // 1 block, N threads
    vectorAdd<<<1, N>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    printf("Result:\n");
    for(int i=0;i<N;i++)
        printf("%.0f ", h_C[i]);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}