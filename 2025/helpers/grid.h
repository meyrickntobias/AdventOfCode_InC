// grid.h
#ifndef GRID_H
#define GRID_H
#include <stdbool.h>

typedef struct {
    int row;
    int col;
} Coordinate;

typedef struct {
    char** map;
    int rowCount;
    int colCount;
} Grid;

// Forms a 2D grid from a character array
Grid formGrid(char *text, int charCount, int width);

// Checks if a coordinate is within the bounds of the grid
bool isWithinBounds(Grid *grid, Coordinate c);

// Gets the first position (row, col) of a given character
Coordinate getFirstPosition(Grid *grid, char c);

void printGrid(Grid *grid);

void freeGrid(Grid *grid);

#endif // INPUT_PROCESSING_H