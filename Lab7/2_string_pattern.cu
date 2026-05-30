#include <iostream>
#include <cstring>
#include <cuda_runtime.h>

__global__ void generateRS(char *S, char *RS, int n)
{
    int tid = threadIdx.x;

    if (tid < n)
    {
        // Copy full string starting at position tid*n
        for (int i = 0; i < n - tid; i++)
        {
            RS[tid * n + i] = S[i];
        }
    }
}

int main()
{
    char S[100];

    std::cout << "Enter string: ";
    std::cin >> S;

    int n = strlen(S);

    int rsSize = n * (n + 1) / 2;

    char *h_RS = new char[rsSize + 1];
    memset(h_RS, 0, rsSize + 1);

    char *d_S, *d_RS;

    cudaMalloc((void **)&d_S, n + 1);
    cudaMalloc((void **)&d_RS, rsSize + 1);

    cudaMemcpy(d_S, S, n + 1, cudaMemcpyHostToDevice);
    cudaMemset(d_RS, 0, rsSize + 1);

    generateRS<<<1, n>>>(d_S, d_RS, n);

    cudaMemcpy(h_RS, d_RS, rsSize, cudaMemcpyDeviceToHost);

    h_RS[rsSize] = '\0';

    std::cout << "Output string RS: " << h_RS << std::endl;

    cudaFree(d_S);
    cudaFree(d_RS);
    delete[] h_RS;

    return 0;
}