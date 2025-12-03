#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
    Function that reads a file into an array of characters

    Other common uses:
     - Splitting up into lines

*/

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
