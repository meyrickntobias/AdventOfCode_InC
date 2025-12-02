#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isSymmetrical(char *originalStr, int length) {
    if (length % 2 != 0) return 0; 
    for (int i = 0; i < length / 2; i++) {
        if (originalStr[i] == originalStr[i + (length / 2)]) continue;
        return 0;
    }
    return 1;
}

int isValid(unsigned long num) {
    char buffer[20]; 
    sprintf(buffer, "%lu", num);
    size_t len = strlen(buffer);
    return isSymmetrical(buffer, len) == 0;
}

int main() {
    FILE *input = fopen("input/day2.txt", "r");
    char c;
    int isLower = 1;
    char numBuffer[20];
    int numIndex = 0;

    // Assuming we have less than 100 ranges
    unsigned long rangeLower[100];
    unsigned long rangeUpper[100];
    int rangeCount = 0;
    
    while ((c = fgetc(input)) != EOF) {
        // printf("%c", c);
        
        if (c == ',') {
            char* endptr;
            numBuffer[numIndex] = '\0';
            unsigned long upper = strtoul(numBuffer, &endptr, 10);
            rangeUpper[rangeCount] = upper;
            rangeCount++;
            numIndex = 0;
        } else if (c == '-') {
            char* endptr;
            numBuffer[numIndex] = '\0';
            unsigned long lower = strtoul(numBuffer, &endptr, 10);
            rangeLower[rangeCount] = lower;
            numIndex = 0;
        } else if (c == '\n') {
            continue;
        } else {
            // assume it's an int, add to buffer
            numBuffer[numIndex++] = c;
        }
    }
    
    for (int i = 0; i < rangeCount; i++) {
        printf("Lower: %lu, Upper: %lu \n", rangeLower[i], rangeUpper[i]);
    }

    unsigned long runningTotal = 0;
    
    for (int i = 0; i < rangeCount; i++) {
        unsigned long lower = rangeLower[i];
        unsigned long upper = rangeUpper[i];

        for (unsigned long j = lower; j <= upper; j++) {
            if (!isValid(j)) {
                runningTotal += j;
                printf("Invalid ID found %lu \n", j);
            }
        }
    }
    
    printf("Total = %lu \n", runningTotal);

    return 0;
}