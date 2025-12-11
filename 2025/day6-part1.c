#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#include "input_processing.h"
#include "helpers/grid.h"

#define INPUT_BUFFER_MAX 100000

uint64_t calculator(int* nums, int countOfNums, char operator) {
    uint64_t total = nums[0];
    for (int i = 1; i < countOfNums; i++) {
        if (operator == '+') total += nums[i];
        if (operator == '*') total *= nums[i];
    }
    return total;
}

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();
    
    char inputBuffer[INPUT_BUFFER_MAX];
    int charCount = readFile("input/day6_input.txt", inputBuffer);
    int width = widthOfLine(inputBuffer, charCount);

    printf("Width of line = %d \n", width);
    Grid grid = formGrid(inputBuffer, charCount, width);
    printf("row count = %d, col count = %d\n", grid.rowCount, grid.colCount);

    // Go down each column
    int runningColumn = 0;
    int scansAcross = 0;
    uint64_t total = 0;

    while (runningColumn < grid.colCount) {   
        // Capture nums in all rows
        int nums[grid.rowCount];
        int maxColWidth = 0;
        
        // Go down all rows except the last
        for (int j = 0; j < grid.rowCount - 1; j++) {
            int colWidth = 0;
            char numStr[10] = {0};
            char c = grid.map[j][runningColumn];
            bool haveSeenFirstChar = false;

            // Keep iterating across until first char
            // or non whitespace after first char
            while (!isspace(c) || !haveSeenFirstChar) {
                if (!isspace(c)) haveSeenFirstChar = true;
                numStr[colWidth] = c;
                colWidth++;
                c = grid.map[j][runningColumn + colWidth];
            }
            colWidth++;
            numStr[colWidth] = '\0';
            nums[j] = atoi(numStr);

            if (colWidth > maxColWidth) maxColWidth = colWidth;
        }

        // Get the operator
        char operator = grid.map[grid.rowCount-1][runningColumn];
        for (int i = 0; i < grid.rowCount - 1; i++) {
            printf("%d %c \n", nums[i], operator);
        } 
        printf("\n");
        uint64_t result = calculator(nums, grid.rowCount - 1, operator);
        printf("Result = %llu \n\n", result);
        total += result;

        runningColumn += maxColWidth;
        scansAcross++;
    }

    printf("Total = %llu \n", total);

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time %f seconds\n", time_spent);

    return 0;
}