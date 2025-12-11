#include <stdlib.h>
#include "ranges.h"

int compareRanges(const void* a, const void* b) {
    const Range *valA = a;
    const Range *valB = b;

    if (valA->low < valB->low) return -1;
    if (valA->low > valB->low) return 1;
    return 0;
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
            uint64_t high;
            if (currentRange.high > nextRange.high) {
                high = currentRange.high;
            } else {
                high = nextRange.high;
            }
    
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

int numbersInRange(uint64_t* numbers, int countOfNumbers, Range* ranges, int rangeCount) {
    int total = 0;
    int i = 0;
    int rangePos = 0;

    while (i < countOfNumbers && rangePos < rangeCount) {
        uint64_t currentIngredient = numbers[i];
        Range currentRange = ranges[rangePos];

        if (currentIngredient < currentRange.low) {
            i++;
        } else if (currentIngredient > currentRange.high) {
            rangePos++;
        } else {
            total++;
            i++;
        }
    }

    return total;
}