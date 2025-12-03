#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "input_processing.h"

int isSymmetrical(char *originalStr, int length) {
    if (length % 2 != 0) return 0; 
    for (int i = 0; i < length / 2; i++) {
        if (originalStr[i] == originalStr[i + (length / 2)]) continue;
        return 0;
    }
    return 1;
}

int isValid(uint64_t num) {
    char buffer[20]; 
    sprintf(buffer, "%llu", num);
    size_t len = strlen(buffer);
    return isSymmetrical(buffer, len) == 0;
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
        if (c == ',') {
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

        printf("Lower: %llu, Upper: %llu \n", lower, upper);

        for (uint64_t j = lower; j <= upper; j++) {
            if (!isValid(j)) {
                runningTotal += j;
                // printf("Invalid ID found %lu \n", j);
            }
        }
    }
    
    printf("Total = %llu \n", runningTotal);

    return 0;
}