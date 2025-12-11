#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "input_processing.h"
#include <ctype.h>

/*
    Function that reads a file into an array of characters

    Other common uses:
     - Splitting up into lines

*/

// TODO: this should take in the buffer length and not overflow
int readFile(char *fileName, char *text) {
    FILE *input = fopen(fileName, "r");
    char c;
    int i = 0;
    
    while ((c = fgetc(input)) != EOF) {
        text[i++] = c;
    }

    text[i++] = '\0';
    return i;
}

LineCollection splitIntoLines(char *text) {
    char** lines = NULL;
    int lineCount = 0;

    char* token = strtok(text, "\n");

    while (token != NULL) {
        lineCount++;

        char** temp = realloc(lines, sizeof(char*) * lineCount);
        if (temp == NULL) break;
        lines = temp;

        lines[lineCount - 1] = malloc(strlen(token) + 1); // shouldn't this use sizeof()?
        strcpy(lines[lineCount - 1], token);

        token = strtok(NULL, "\n");
    }

    LineCollection collection = { lines, lineCount };
    return collection;
}

int widthOfLine(char *text, int maxLength) {
    for (int i = 0; i < maxLength; i++) {
        if (text[i] == '\n') return i + 1; 
    }
    return maxLength;
}

bool isDigit(char* str) {
    char c = str[0];
    int i = 1;

    while (c != '\0') {
        if (!isdigit(c)) return false;
        c = str[i++]; 
    }

    return true;
}

int findFirstEmptyLine(char* text, int length) {
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