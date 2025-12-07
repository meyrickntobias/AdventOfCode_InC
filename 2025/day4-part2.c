#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input_processing.h"
#include <time.h>

typedef struct {
    char** map;
    int rowCount;
    int colCount;
} Grid;

typedef struct {
    int row;
    int col;
} Coordinate;

bool isWithinBounds(int row, int col, int rowCount, int colCount) {
    if (row >= rowCount || row < 0) return false;
    if (col >= colCount || col < 0) return false;
    return true;
}

bool isRollAtPosition(Grid *input, int row, int col) {
    if (!isWithinBounds(row, col, input->rowCount, input->colCount)) {
        return false;
    }

    char c = input->map[row][col];
    if (c == '@') return true;
    return false;
}

int getAdjacentRolls(Grid *input, int row, int col) {
    int adjacentRolls = 0;

    int up = row + 1;
    int down = row - 1;
    int right = col + 1;
    int left = col - 1;

    adjacentRolls += isRollAtPosition(input, up, col);       // directly up
    adjacentRolls += isRollAtPosition(input, down, col);     // directly down
    adjacentRolls += isRollAtPosition(input, row, right);    // directly right
    adjacentRolls += isRollAtPosition(input, row, left);     // directly left
    adjacentRolls += isRollAtPosition(input, up, left);      // up and left
    adjacentRolls += isRollAtPosition(input, up, right);     // up and right
    adjacentRolls += isRollAtPosition(input, down, left);    // down and left
    adjacentRolls += isRollAtPosition(input, down, right);   // down and right

    return adjacentRolls;
}
    
int removeAccessibleRolls(Grid *input) {
    int accessibleRolls = 0;
    Coordinate rollsToRemove[2000];

    for (int i = 0; i < input->rowCount; i++)
    {
        for (int j = 0; j < input->colCount; j++) {
            if (!isRollAtPosition(input, i, j)) continue;
            if (getAdjacentRolls(input, i, j) < 4) {
                rollsToRemove[accessibleRolls].row = i;
                rollsToRemove[accessibleRolls].col = j;

                accessibleRolls++;
            }
        }
    }

    for (int i = 0; i < accessibleRolls; i++) {
        int row = rollsToRemove[i].row;
        int col = rollsToRemove[i].col;

        input->map[row][col] = '.';
    }

    return accessibleRolls;
}

Grid processInput(char* fileName) {
    char inputBuffer[30000];
    int charCount = readFile(fileName, inputBuffer);
    char **map = NULL;
    
    int rowIterator = 0;
    int colWidth = widthOfLine(inputBuffer, charCount);

    char rowBuffer[colWidth];
    char c;

    for (int i = 0; i < charCount; i++) {
        c = inputBuffer[i];

        if (c == '\n' || i == charCount - 1) {
            rowIterator++;

            map = realloc(map, sizeof(char*) * rowIterator);
            map[rowIterator-1] = malloc(sizeof(char) * colWidth);

            for (int j = 0; j < colWidth; j++) {
                map[rowIterator-1][j] = inputBuffer[((rowIterator - 1) * colWidth) + j];
            }
            continue;
        }
    }

    Grid inputData = {map, rowIterator, colWidth };

    return inputData;
}

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();
 
    Grid inputData = processInput("input/day4_input.txt");
    Grid *input = &inputData;

    int rollsRemoved = 0;
    int accessibleRolls = 0;

    do {
        accessibleRolls = removeAccessibleRolls(input);
        printf("Rolls removed - %d \n", accessibleRolls);
        rollsRemoved += accessibleRolls;
    } while (accessibleRolls != 0);

    for (int i = 0; i < input->rowCount; i++) {
        free(input->map[i]);
    }
    free(input->map);

    printf("Total rolls removed - %d \n", rollsRemoved);
    
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution time %f seconds\n", time_spent);

    return 0;   
}
