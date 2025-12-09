#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "input_processing.h"
#include "helpers/grid.h"

typedef struct {
    int low;
    int high;
} Range;

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();

    Range ranges[4] = { { .low = 3, .high = 5 }, { .low= 10, .high = 14 }, { .low = 16, .high = 20}, { .low = 12, .high = 18 } };
    int ingredients[6] = { 1, 5, 8, 11, 17, 32 }; 
    int spoiled[6];
    int spoilCount = 0;

    // Naive method

    for (int i = 0; i < 6; i++) {
        int ingredient = ingredients[i];
        int isSpoiled = true;
        for (int r = 0; r < 4; r++) {
            for (int j = ranges[r].low; j <= ranges[r].high; j++) {
                if (ingredient == j) isSpoiled = false;
            }
        }
        if (isSpoiled) spoiled[spoilCount++] = ingredient;
    }

    printf("Spoil count is %d \n", spoilCount);    

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time %f seconds\n", time_spent);

    return 0;
}