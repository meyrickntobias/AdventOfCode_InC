#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input_processing.h"

typedef struct {
    char **map;
    int rowCount;
    int colCount;
} Grid;

typedef struct {
    int row;
    int col;
} Coordinate;

bool isWithinBounds(Coordinate c, int rowCount, int colCount) {
    if (c.row >= rowCount || c.row < 0) return false;
    if (c.col >= colCount || c.col < 0) return false;
    return true;
}

Coordinate getStartingPosition(Grid *grid, char startingChar) {
    // Assume it's on the first line
    for (int i = 0; i < grid->colCount; i++) {
        if (grid->map[0][i] == startingChar) {
            Coordinate startingPos = { 0, i };
            return startingPos;
        }
    }

    Coordinate notFoundPos = { -1, -1 };
    return notFoundPos;
}

int splitter(Grid *grid, Coordinate position, int currentSplitCount) {
    printf("Called with position { %d, %d } \n", position.row, position.col);
    // Terminating condition
    while (isWithinBounds(position, grid->rowCount, grid->colCount)) {
        // If char at position is splitter, then call splitter
        if (grid->map[position.row][position.col] == '^') {
            Coordinate left = { position.row, position.col - 1 };
            Coordinate right = { position.row, position.col + 1 };
            currentSplitCount += 1;

            splitter(grid, left, currentSplitCount);
            splitter(grid, right, currentSplitCount);
        } else {
            position.row++;
        }
    }

    return currentSplitCount;
}

Grid processInput(char* fileName) {
    char inputBuffer[30000];
    int charCount = readFile(fileName, inputBuffer);
    char **map = NULL;
    
    int rowIterator = 0;
    int colIterator = 0;
    int colWidth = widthOfLine(inputBuffer, charCount);

    char rowBuffer[300];
    char c;

    for (int i = 0; i < charCount; i++) {
        c = inputBuffer[i];

        if (c == '\n' || i == charCount - 1) {
            rowIterator++;

            map = realloc(map, sizeof(char*) * rowIterator);
            map[rowIterator-1] = malloc(sizeof(char) * colWidth);

            for (int j = 0; j < colWidth; j++) {
                map[rowIterator-1][j] = rowBuffer[j]; 
            }
            colIterator = 0;
            continue;
        }
        
        rowBuffer[colIterator++] = inputBuffer[i];
    }

    Grid inputData = {map, rowIterator, colWidth };

    return inputData;
}


int main() {
    // Read input into char matrix
    Grid gridInput = processInput("input/day7_sample.txt");
    Grid* grid = &gridInput;

    for (int i = 0; i < grid->rowCount; i++) {
        for (int j = 0; j < grid->colCount; j++) {

            printf("%c", grid->map[i][j]);
        }
        printf("\n");
    }
    
    // Find starting position
    Coordinate startingPos = getStartingPosition(grid, 'S');
    printf("Starting pos = { %d, %d } \n", startingPos.row, startingPos.col);
    
    // Call recursive splitter function
    int finalSplitCount = splitter(grid, startingPos, 0);
    printf("Final split count = %d \n", finalSplitCount);

    for (int i = 0; i < grid->rowCount; i++) {
        free(grid->map[i]);
    }
    free(grid->map);

    return 0;
}