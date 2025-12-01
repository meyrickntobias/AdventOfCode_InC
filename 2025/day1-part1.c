#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int getNextPosition(int position, int move) {
    return ((position + (move % 100)) + 100) % 100;
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

    int hits = 0;

    for (int i = 0; i < moveCount; i++) {
        position = getNextPosition(position, moves[i]);
        if (position == 0) {
            hits++;
        }
    }

    printf("The number of hits is...\n\n");
    printf("%d\n", hits);

    return 0;
}