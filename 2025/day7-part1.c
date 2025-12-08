#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input_processing.h"
#include "helpers/grid.h"

typedef struct {
    Coordinate *coordinates;
    int count;
} SplitterCoordinates;

bool hasBeenVisited(Grid *grid, SplitterCoordinates *splitterCoordinates, Coordinate coordinate) {
    for (int i = 0; i < splitterCoordinates->count; i++) {
        int row = splitterCoordinates->coordinates[i].row;
        int col = splitterCoordinates->coordinates[i].col;
        if (coordinate.row == row && coordinate.col == col) return true;
    }
    return false;
}

int splitter(Grid *grid, Coordinate position, int currentSplitCount, SplitterCoordinates *splitterCoordinates) {
    if (!isWithinBounds(grid, position)) {
        return currentSplitCount;
    }
    
    if (grid->map[position.row][position.col] == '^') {
        if (hasBeenVisited(grid, splitterCoordinates, position))
        {
            return currentSplitCount;
        }
        Coordinate left = { position.row, position.col - 1 };
        Coordinate right = { position.row, position.col + 1 };
        currentSplitCount += 1;

        splitterCoordinates->coordinates[splitterCoordinates->count] = position;
        splitterCoordinates->count += 1;

        currentSplitCount = splitter(grid, left, currentSplitCount, splitterCoordinates);
        currentSplitCount = splitter(grid, right, currentSplitCount, splitterCoordinates);
    } else if (grid->map[position.row][position.col] == '|') {
        position.row++;
        currentSplitCount = splitter(grid, position, currentSplitCount, splitterCoordinates);
    } else {
        grid->map[position.row][position.col] = '|';
        position.row++;
        currentSplitCount = splitter(grid, position, currentSplitCount, splitterCoordinates);
    }

    return currentSplitCount;
}

Grid processInput(char* fileName) {
    char inputBuffer[30000];
    int charCount = readFile(fileName, inputBuffer);
    int rowWidth = widthOfLine(inputBuffer, charCount);

    return formGrid(inputBuffer, charCount, rowWidth);
}

int main() {
    Grid gridInput = processInput("input/day7_input.txt");
    Grid* grid = &gridInput;

    Coordinate startingPos = getFirstPosition(grid, 'S');
    printf("Starting pos = { %d, %d } \n", startingPos.row, startingPos.col);
    
    // Call recursive splitter function
    Coordinate coordinatesArr[10000];
    SplitterCoordinates coordinates = { coordinatesArr, 0 };

    int finalSplitCount = splitter(grid, startingPos, 0, &coordinates);
    printf("Final split count = %d \n", finalSplitCount);

    printGrid(grid);
    freeGrid(grid);

    return 0;
}