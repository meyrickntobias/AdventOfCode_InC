#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

// Forms a 2D grid from a character array
Grid formGrid(char *text, int charCount, int width) {
    char **map = NULL;
    int rowIterator = 0;

    char c;

    for (int i = 0; i < charCount; i++) {
        c = text[i];

        if (c == '\n' || i == charCount - 1) {
            rowIterator++;

            map = realloc(map, sizeof(char*) * rowIterator);
            map[rowIterator-1] = malloc(sizeof(char) * width);

            for (int j = 0; j < width; j++) {
                map[rowIterator-1][j] = text[((rowIterator - 1) * width) + j];
            }
            continue;
        }
    }

    Grid inputData = { map, rowIterator, width };

    return inputData;
}

// Checks if a coordinate is within the bounds of the grid
bool isWithinBounds(Grid *grid, Coordinate c) {
    bool isWithinHeight = c.row < grid->rowCount && c.row >= 0;
    bool isWithinWidth = c.col < grid->colCount && c.col >= 0;
    return isWithinHeight && isWithinWidth;
}

// Gets the first position (row, col) of a given character
Coordinate getFirstPosition(Grid *grid, char c) {
    for (int i = 0; i < grid->rowCount; i++) {
        for (int j = 0; j < grid->colCount; j++) {
            if (grid->map[i][j] == c) {
                Coordinate pos = { i, j };
                return pos;
            }
        }
    }

    Coordinate notFound = { -1, -1 };

    return notFound;
}

void printGrid(Grid *grid) {
    for (int i = 0; i < grid->rowCount; i++) {
        for (int j = 0; j < grid->colCount; j++) {
            printf("%c", grid->map[i][j]);
        }
    }
}

void freeGrid(Grid *grid) {
    for (int i = 0; i < grid->rowCount; i++) {
        free(grid->map[i]);
    }
    free(grid->map);
}