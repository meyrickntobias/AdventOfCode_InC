// input_processing.h
#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include <stdbool.h>

typedef struct {
    char** lines;
    int lineCount;
} LineCollection;

int readFile(char *fileName, char *text);

LineCollection splitIntoLines(char *text);

int widthOfLine(char *text, int maxLength);

bool isDigit(char* str);

int findFirstEmptyLine(char* str, int length);

#endif // INPUT_PROCESSING_H