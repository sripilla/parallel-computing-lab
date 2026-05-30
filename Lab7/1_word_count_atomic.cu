#include <iostream>
#include <cstring>
#include <cuda_runtime.h>

__global__ void countWordOccurrences(char *sentence, char *word, int *count,
                                     int sentenceLen, int wordLen)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx <= sentenceLen - wordLen)
    {
        bool match = true;

        for (int i = 0; i < wordLen; i++)
        {
            if (sentence[idx + i] != word[i])
            {
                match = false;
                break;
            }
        }

        // Check word boundaries
        if (match)
        {
            bool startBoundary = (idx == 0 || sentence[idx - 1] == ' ');
            bool endBoundary =
                (idx + wordLen == sentenceLen ||
                 sentence[idx + wordLen] == ' ');

            if (startBoundary && endBoundary)
            {
                atomicAdd(count, 1);
            }
        }
    }
}

int main()
{
    char sentence[200];
    char word[50];

    std::cout << "Enter sentence: ";
    std::cin.getline(sentence, 200);

    std::cout << "Enter word to search: ";
    std::cin.getline(word, 50);

    int sentenceLen = strlen(sentence);
    int wordLen = strlen(word);

    char *d_sentence, *d_word;
    int *d_count, count = 0;

    cudaMalloc((void **)&d_sentence, sentenceLen + 1);
    cudaMalloc((void **)&d_word, wordLen + 1);
    cudaMalloc((void **)&d_count, sizeof(int));

    cudaMemcpy(d_sentence, sentence, sentenceLen + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, wordLen + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocks = (sentenceLen + threadsPerBlock - 1) / threadsPerBlock;

    countWordOccurrences<<<blocks, threadsPerBlock>>>(
        d_sentence, d_word, d_count, sentenceLen, wordLen);

    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    std::cout << "Number of occurrences of \"" << word
              << "\" = " << count << std::endl;

    cudaFree(d_sentence);
    cudaFree(d_word);
    cudaFree(d_count);

    return 0;
}