// hashset.h
#ifndef HASHSET_H
#define HASHSET_H
#include <stdint.h>
#include <stdbool.h>

typedef struct Node {
    uint64_t value;
    struct Node* next;
} UIntNode;

uint64_t getHashCode(uint64_t data);

bool addToHashSet(uint64_t item, UIntNode* items, int hashSetSize);

bool hashSetContains(uint64_t item, UIntNode* items, int hashSetSize);

#endif // HASHSET_H