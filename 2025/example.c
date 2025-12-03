#include <stdio.h>

int getNextPosition(int position, int move) {
    // Wrapping around once the position gets to 99, and back to 99 once it gets past 0
    // 50 + (-99) = -49 + 100 = 149
    // 50 + 99 
    return (position + (move % 100)) % 100;
}

int main() {
    int someNumbers[] = { 10, 50, -10, -50, 100, 99, -99, 199, -199, -299 };
    int count = sizeof(someNumbers) / sizeof(int);
    for (int i = 0; i < count; i++) {
        int nextPosition = getNextPosition(50, someNumbers[i]);
        printf("50 + %d = %d\n", someNumbers[i], nextPosition);
    }

    return 0;
}
