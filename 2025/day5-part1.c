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

    uint64_t highA = valA->high;
    uint64_t highB = valB->high;

    if (highA < highB) return -1;
    if (highA > highB) return 1;

    return 0;
}

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();

    InputData inputData = processInput();
    int freshIngredients = 0;

    // Sort the ingredients
    qsort(inputData.ingredients, inputData.ingredientCount, sizeof(uint64_t), compare64BitIntegers);

    // Sort the ranges by low
    qsort(inputData.ranges, inputData.rangeCount, sizeof(Range), compareRanges);

    // Verify the ranges
    for (int i = 0; i < inputData.rangeCount; i++) {
        if (inputData.ranges[i].low == inputData.ranges[i].high) {
            printf("MISMATCH RANGE");
        }
        printf("{ %20llu, %20llu } \n", inputData.ranges[i].low, inputData.ranges[i].high);
    }

    // Iterate over ingredients
    int ingredientCounter = 0;
    int rangePosition = 0;

    while (ingredientCounter < inputData.ingredientCount && rangePosition < inputData.rangeCount) {
        uint64_t currentIngredient = inputData.ingredients[ingredientCounter];
        Range currentRange = inputData.ranges[rangePosition];

        if (currentIngredient < currentRange.low) {
            // Ingredient is smaller than current range start.
            // Since ranges are sorted, it cannot be in ANY future range either.
            // So it is "Spoilt" / Not in range.
            // printf("%llu is spoilt \n", currentIngredient);
            ingredientCounter++;
        } else if (currentIngredient > currentRange.high) {
            // Ingredient is past this range.
            // This range is now useless. Discard it.
            // Do NOT increment ingredientCounter, we need to check this ingredient against the next range.
            rangePosition++;
        } else {
            // Match found! (rng.low <= ing <= rng.high)
            // printf("%llu is fresh \n", currentIngredient);
            freshIngredients++;
            ingredientCounter++;
        }
    }

    // Exhausted all ranges and all other ingredients must be higher (if sorted)
    printf("Stopped at ingredient count %d \n", ingredientCounter);
    for (int i = ingredientCounter; i < inputData.ingredientCount; i++) {
        printf("%llu \n", inputData.ingredients[i]);
    }

    printf("\n\n Fresh ingredients = %d \n", freshIngredients);

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time %f seconds\n", time_spent);

    return 0;
}