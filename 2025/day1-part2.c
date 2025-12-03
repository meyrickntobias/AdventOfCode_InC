#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int getNextPosition(int position, int move) {
    // Wrapping around once the position gets to 99, and back to 99 once it gets past 0
    return ((position + (move % 100)) + 100) % 100;
}

int getCycles(int position, int move) {
    int deltaFromZero;
    int leftOverFromFirstMove;

    if (move > 0) {
        if (position == 0) {
            deltaFromZero = 99;
        } else {
            deltaFromZero = 99 - position;
        }
        leftOverFromFirstMove = move - deltaFromZero;
    } else if (move < 0) {
        if (position == 0) {
            deltaFromZero = 100;
        } else {
            deltaFromZero = position;
        }
        leftOverFromFirstMove = abs(move) - deltaFromZero;
    } else {
        return 0;
    }

    // printf("Delta from zero: %d, Left over: %d \n", deltaFromZero, leftOverFromFirstMove);
    if (leftOverFromFirstMove < 0) return 0;
	else if (leftOverFromFirstMove == 0) return 1;
	else
	{
        double cycles = ceil((double)leftOverFromFirstMove / 100.0);
        // printf("%f\n", cycles);
        return (int) cycles;
	}
}

int main() {
    int position = 50;

    
    FILE *input = fopen("input.txt", "r");
    char lineBuffer[10];

    // TODO: is there a way to not assume the length of the input?
    int moves[10000];
    int moveCount = 0;  

    
    while (fgets(lineBuffer, 10, input)) {
        char directionIndicator = lineBuffer[0];
        char moveBuffer[9];

        for (int i = 0; i < 9; i++) {
            if (isspace(lineBuffer[i + 1])) {
                moveBuffer[i] = '\0';
                break;
            }
            moveBuffer[i] = lineBuffer[i + 1];
        }

        int move = atoi(moveBuffer);
        if (directionIndicator == 'L') {
            move = -move;
        } 

        moves[moveCount] = move;
        moveCount++;
    }
    
    /*
    int moves[] = { -68, -30, 48, -5, 60, -55, -1, -99, 14, -82 };
    int moveCount = 10;
    */
    int cycles = 0;
    

    for (int i = 0; i < moveCount; i++) {
        printf("Starting position: %d \n", position);
        printf("Moving %d \n", moves[i]);
        cycles += getCycles(position, moves[i]);
        position = getNextPosition(position, moves[i]);
        printf("New Position: %d \n", position);
        printf("Cycles: %d \n", cycles);
        printf("\n");
    }

    printf("The number of cycles is...\n\n");
    printf("%d\n", cycles);

    return 0;
}