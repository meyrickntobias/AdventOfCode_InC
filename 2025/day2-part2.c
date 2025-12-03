#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "input_processing.h"

int compareIntegers(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int getFactors(int num, int* factorArr) {
    int mid = num / 2 + 1;
    int factorCount = 0;

    for (int i = 2; i < mid; i++) {
        if (num % i == 0) factorArr[factorCount++] = i; 
    }

    factorArr[factorCount++] = 1;
    factorArr[factorCount++] = num;

    return factorCount;
}

bool isSymmetrical(char *originalStr, int length) {
    // Get common factors of the length, e.g: 6 = 1, 2, 3, 6
    int factors[length];
    int factorCount = getFactors(length, factors);
    qsort(factors, factorCount, sizeof(int), compareIntegers);

    // Iterate over every factor, starting from the first one (1)
    for (int i = 0; i < (factorCount - 1); i++) {
        int factor = factors[i];

        int j = 0;
        // Store the number of digits that factor refers to
        char digits[factor + 1];            // Account for string termination
        char previousDigits[factor + 1];

        bool isSymmetric = false;

        // Iterate over the length of the string
        while (j <= (length - factor)) {
            // Copy the relevant characters into the digits buffer
            for (int x = 0; x < factor; x++) {
                digits[x] = originalStr[x+j];                 
            }
            digits[factor] = '\0';
            
            // On the first iteration, don't compare, just fill the previousDigits buffer
            if (j == 0) {
                strcpy(previousDigits, digits);
                j += factor;
                continue;
            }

            if (strcmp(previousDigits, digits) != 0) {
                isSymmetric = false;
                break;
            }

            j += factor;
            isSymmetric = true;
        }

        if (isSymmetric) {
            return true;
        }
    }

    return false;
}

bool isValid(uint64_t num) {
    char buffer[20]; 
    sprintf(buffer, "%llu", num);
    size_t len = strlen(buffer);
    if (isSymmetrical(buffer, len)) {
        return false;
    } else {
        return true;
    }
}

int main() {
    char text[10000];
    int charCount = readFile("input/day2.txt", text);
    printf("%d\n", charCount);

    int isLower = 1;
    char numBuffer[20];
    int numIndex = 0;

    // Assuming we have less than 100 ranges
    uint64_t rangeLower[100];
    uint64_t rangeUpper[100];
    int rangeCount = 0;
    
    for (int i = 0; i < charCount; i++)
    {
        char c = text[i];
        // printf("%c", c);
        if (c == ',' || i == charCount - 1) {
            char* endptr;
            numBuffer[numIndex] = '\0';
            uint64_t upper = strtoul(numBuffer, &endptr, 10);
            rangeUpper[rangeCount] = upper;
            rangeCount++;
            numIndex = 0;
        } else if (c == '-') {
            char* endptr;
            numBuffer[numIndex] = '\0';
            uint64_t lower = strtoul(numBuffer, &endptr, 10);
            rangeLower[rangeCount] = lower;
            numIndex = 0;
        } else if (c == '\n') {
            continue;
        } else {
            // assume it's an int, add to buffer
            numBuffer[numIndex++] = c;
        }
    }

    uint64_t runningTotal = 0;
    printf("Range count: %d \n", rangeCount);
    
    for (int i = 0; i < rangeCount; i++) {
        uint64_t lower = rangeLower[i];
        uint64_t upper = rangeUpper[i];

        if (lower >= upper) continue;   

        printf("\n");
        printf("Lower: %llu, Upper: %llu \n", lower, upper);
        for (uint64_t j = lower; j <= upper; j++) {
            if (!isValid(j)) {
                runningTotal += j;
                printf("Invalid ID found %lu \n", j);
            }
        }
    }
    
    printf("Total = %llu \n", runningTotal);
    /*
    uint64_t nums[] = { 756756, 111, 21212121, 101, 755557 };
    int numCount = sizeof(nums) / sizeof(uint64_t);
    printf("1 for valid, 0 for invalid\n");
    for (int i = 0; i < numCount; i++) {
        printf("%llu %d \n", nums[i], isValid(nums[i]));
    }

    printf("\n");
    */

    return 0;   
}
