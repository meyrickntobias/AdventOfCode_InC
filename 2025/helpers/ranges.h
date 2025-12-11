// ranges.h
#ifndef RANGES_H
#define RANGES_H
#include <stdint.h>

typedef struct {
    uint64_t low;
    uint64_t high;
} Range;

typedef struct {
    Range *ranges;
    int rangeCount;
} Ranges;

Ranges mergeOverlappingRanges(Range* ranges, int rangeCount);

int compareRanges(const void* a, const void* b);

int numbersInRange(uint64_t* numbers, int countOfNumbers, Range* ranges, int rangeCount);

#endif // RANGES_H