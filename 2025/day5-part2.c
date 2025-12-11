#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include "input_processing.h"
#include "helpers/ranges.h"

#define INPUT_CHAR_LIMIT 1000000
#define RANGES_LIMIT 10000
#define INGREDIENTS_LIMIT 10000

typedef struct {
    Range *ranges;
    int rangeCount;
    uint64_t *ingredients;
    int ingredientCount;
} InputData;


InputData processInput(char* fileName) {
    // TODO is this bad practice, passing a stack variable into another function
    char inputBuffer[INPUT_CHAR_LIMIT];
    int charCount = readFile(fileName, inputBuffer);
    int emptyLineIndex = findFirstEmptyLine(inputBuffer, charCount);

    LineCollection lines = splitIntoLines(inputBuffer);
    Range *inputRanges = malloc(sizeof(Range) * RANGES_LIMIT);
    uint64_t *ingredients = malloc(sizeof(uint64_t) * INGREDIENTS_LIMIT);
    int rangeCount = 0;

    // Parse ranges
    for (int i = 0; i < emptyLineIndex; i++) {
        char *firstNum = strtok(lines.lines[i], "-");
        char *secondNum = strtok(NULL, "-");
        char *endPtr;
        Range range = { .low = strtoull(firstNum, &endPtr, 10), .high = strtoull(secondNum, &endPtr, 10) };
        inputRanges[rangeCount++] = range;
    }

    int ingredientCount = 0;

    // Parse ingredients
    for (int i = emptyLineIndex; i < lines.lineCount; i++) {
        char *endPtr;
        uint64_t ingredient = strtoll(lines.lines[i], &endPtr, 10);
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

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();

    InputData inputData = processInput("input/day5_input.txt");
    uint64_t freshIngredients = 0;

    // Sort the ranges by low
    qsort(inputData.ranges, inputData.rangeCount, sizeof(Range), compareRanges);
    qsort(inputData.ingredients, inputData.ingredientCount, sizeof(uint64_t), compare64BitIntegers);

    Ranges newRanges = mergeOverlappingRanges(inputData.ranges, inputData.rangeCount);

    for (int i = 0; i < newRanges.rangeCount; i++) {
        freshIngredients += newRanges.ranges[i].high - newRanges.ranges[i].low + 1; 
    }

    printf("Possible fresh ingredients = %llu \n", freshIngredients);

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time %f seconds\n", time_spent);

    return 0;
}