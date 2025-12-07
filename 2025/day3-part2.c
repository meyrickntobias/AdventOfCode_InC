
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include "input_processing.h"
#include <math.h>
#include <time.h>

typedef struct {
    int** banks;
    int bankCount;
    int bankLength;
} InputData;

int largestPossibleJoltage(int* bank, int length) {
    int highest = 0;
    for (int i = 0; i < length - 1; i++)
    {

        for (int j = i + 1; j < length; j++) {
            int joltage = bank[i] * 10 + bank[j];
            if (joltage > highest) highest = joltage;
        }
    }
    return highest;
}

InputData processInput(char* fileName) {
    char textBuffer[21000];
    int charCount = readFile(fileName, textBuffer);

    char c;
    int **banks = NULL;

    int bankBuffer[300]; 
    int numbersInBank = 0;
    int bankLength = 0;
    int bankCount = 0;

    for (int i = 0; i < charCount; i++) {
        c = textBuffer[i];
        // printf("%c", c);

        if (c == '\n' || i == charCount - 1) {
            // allocate memory in banks
            banks = realloc(banks, sizeof(int*) * (bankCount + 1));
            banks[bankCount] = malloc(sizeof(int) * numbersInBank);

            for (int j = 0; j < numbersInBank; j++) {
                banks[bankCount][j] = bankBuffer[j];
            }

            if (bankCount == 0) bankLength = numbersInBank;

            bankCount++;
            numbersInBank = 0;
            continue;
        }
        if (isdigit(c)) {
            bankBuffer[numbersInBank] = c - '0';
            numbersInBank++;
        }
    }

    InputData input = { banks, bankCount, bankLength };

    return input;
}

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();
 
    char text[10000];
    // int banks[4][15] = { { 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1 }, { 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9 }, { 2, 3, 4, 2, 3, 4, 2, 3, 4, 2, 3, 4, 2, 7, 8 }, { 8, 1, 8, 1, 8, 1, 9, 1, 1, 1, 1, 2, 1, 1, 1 } }; 
    InputData input = processInput("input/day3_input.txt");
    printf("%d %d\n", input.bankCount, input.bankLength);

    int runningTotal = 0;

    /*
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < InputData.bankLength; j++) {
            printf("%d", InputData.banks[i][j]);
        }
        printf("\n");
    }
    */
    
    for (int i = 0; i < InputData.bankCount - 1; i++)
    {
        int joltage = largestPossibleJoltage(InputData.banks[i], InputData.bankLength);
        printf("Joltage = %d \n", joltage);
        runningTotal += joltage;
    }

    for (int i = 0; i < InputData.bankCount; i++)
    {
        free(InputData.banks[i]);
    }
    free(InputData.banks);

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Total = %d \n", runningTotal);
    printf("Execution time %f seconds\n", time_spent);

    return 0;   
}
