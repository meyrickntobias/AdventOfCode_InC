#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "hashset.h"

uint64_t getHashCode(uint64_t data) {
    // The 64 bit offset basis
   uint64_t hash = 14695981039346656037llu;
   uint64_t prime = 1099511628211llu;

   uint8_t *p = (uint8_t*) &data;

   for (int i = 0; i < 8; i++) {
    hash ^= p[i];
    hash *= prime;
   }

   return hash;
}

bool addToHashSet(uint64_t item, UIntNode* items, int hashSetSize) {
    uint64_t hash = getHashCode(item);
    int index = hash % hashSetSize;
    
    if (items[index].value == 0) {
        UIntNode nodeToAdd = { .value = item, .next = NULL };
        items[index] = nodeToAdd;
        return true;
    }

    UIntNode* current = &items[index];

    while (1) {
        if (items[index].value == item) {
            // do nothing because item already exists in set
            return false;
        }

        if (current->next == NULL) {
            break;
        }

        current = current->next;
    }

    UIntNode* newNode = malloc(sizeof(UIntNode));
    if (newNode == NULL) return false; // Out of memory
    newNode->value = item;
    newNode->next = NULL;
    current->next = newNode;
    
    return true;
}

bool hashSetContains(uint64_t item, UIntNode* items, int hashSetSize) {
    uint64_t hash = getHashCode(item);
    int index = hash % hashSetSize;

    if (items[index].value == 0) return false;

    UIntNode* current = &items[index];

    while (1) {
        if (items[index].value == item) {
            return true;
        }

        if (current->next == NULL) {
            return false;
        }

        current = current->next;
    }
}
