#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include "input_processing.h"
#include "helpers/grid.h"
#include "helpers/hashset.h"

typedef struct {
    uint64_t low;
    uint64_t high;
} Range;

typedef struct {
    Range *ranges;
    int rangeCount;
    uint64_t *ingredients;
    int ingredientCount;
} InputData;

typedef struct {
    Range *ranges;
    int rangeCount;
} Ranges;

int findEmptyLine(char* text, int length) {
    int lineCount = 0;
    int charsInBetween = 0;

    for (int i = 0; i < length; i++) {
        if (text[i] == '\n' && charsInBetween == 0) {
            return lineCount;
        } else if (text[i] == '\n') {
            lineCount++;
            charsInBetween = 0;
        } else {
            charsInBetween++;
        }
    }

    // Could not find empty line
    return -1;
}

InputData processInput() {
    char inputBuffer[1000000];
    int charCount = readFile("input/day5_input.txt", inputBuffer);
    int emptyLineIndex = findEmptyLine(inputBuffer, charCount);
    printf("First empty line = %d \n", emptyLineIndex);

    LineCollection lines = splitIntoLines(inputBuffer);
    Range *inputRanges = malloc(sizeof(Range) * 10000);
    uint64_t *ingredients = malloc(sizeof(uint64_t) * 10000);
    int rangeCount = 0;

    // Parse ranges
    for (int i = 0; i < emptyLineIndex; i++) {
        char *firstNum = strtok(lines.lines[i], "-");
        char *secondNum = strtok(NULL, "-");
        char *endPtr;
        Range range = { .low = strtoull(firstNum, &endPtr, 10), .high = strtoull(secondNum, &endPtr, 10) };
        inputRanges[rangeCount++] = range;

        // printf("{ %llu, %llu } \n", range.low, range.high);
    }

    int ingredientCount = 0;

    // Parse ingredients
    for (int i = emptyLineIndex; i < lines.lineCount; i++) {
        char *endPtr;
        uint64_t ingredient = strtoll(lines.lines[i], &endPtr, 10);
        // printf("%llu \n", ingredient);
        ingredients[ingredientCount++] = ingredient;
    }

    InputData inputData = { 
        .ranges = inputRanges,
        .rangeCount = rangeCount,
        .ingredients = ingredients,
        .ingredientCount = ingredientCount 
    };

    return inputData;
}

int compare64BitIntegers(const void* a, const void* b) {
    uint64_t arg1 = *(const uint64_t*)a;
    uint64_t arg2 = *(const uint64_t*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compareRanges(const void* a, const void* b) {
    const Range *valA = a;
    const Range *valB = b;

    uint64_t lowA = valA->low;
    uint64_t lowB = valB->low;

    if (lowA < lowB) return -1;
    if (lowA > lowB) return 1;
    return 0;
}

uint64_t highest(uint64_t a, uint64_t b) {
    if (a > b) return a;
    return b;
}

// Takes an array of ranges a count, merges overlapping ranges and replaces ranges pointer
Ranges mergeOverlappingRanges(Range* ranges, int rangeCount) {
    Range* newRanges = malloc(rangeCount * sizeof(Range));
    int mergedRangeCount = 0;

    Range currentRange = ranges[0];
    newRanges[mergedRangeCount++] = currentRange;

    for (int i = 0; i < rangeCount-1; i++) {
        Range nextRange = ranges[i+1];

        if (nextRange.low <= currentRange.high) {
            uint64_t high = highest(currentRange.high, nextRange.high);
            Range mergedRange = { .low = currentRange.low, .high = high };
            newRanges[mergedRangeCount - 1] = mergedRange;
            
            currentRange = mergedRange;
        } else {
            newRanges[mergedRangeCount++] = nextRange;
            currentRange = nextRange;
        }
    }

    Ranges rangesCollection = { newRanges, mergedRangeCount };
    return rangesCollection;
}

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();

    InputData inputData = processInput();
    uint64_t freshIngredients = 0;

    // Sort the ingredients
    qsort(inputData.ingredients, inputData.ingredientCount, sizeof(uint64_t), compare64BitIntegers);

    // Sort the ranges by low
    qsort(inputData.ranges, inputData.rangeCount, sizeof(Range), compareRanges);

    Ranges newRanges = mergeOverlappingRanges(inputData.ranges, inputData.rangeCount);

    // Verify the ranges
    for (int i = 0; i < newRanges.rangeCount; i++) {
        freshIngredients += newRanges.ranges[i].high - newRanges.ranges[i].low + 1; 
    }

    printf("Possible fresh ingredients = %llu \n", freshIngredients);

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time %f seconds\n", time_spent);

    return 0;
}