#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "input_processing.h"

typedef struct {
    int a;
    int b;
    int c;
} ThreeDCoordinate;

double euclideanDistance(ThreeDCoordinate p, ThreeDCoordinate q) {
    double A = pow((p.a - q.a), 2);
    double B = pow((p.b - q.b), 2);
    double C = pow((p.c - q.c), 2);

    return sqrt(A + B + C);
}

ThreeDCoordinate* processInput(char *fileName) {
    char *inputBuffer[1000];
    int charCount = readFile(fileName, inputBuffer);
    ThreeDCoordinate *coordinates = NULL;
    ThreeDCoordinate currentCoordinate;
    
    int coordinateCount = 0;
    int dimensionCount = 0;
    char numBuffer[10];
    int numCount = 0;
    
    for (int i = 0; i < charCount; i++) {
        char c = inputBuffer[i];
        if (c == '\n') {
            coordinates = realloc(coordinates, sizeof(ThreeDCoordinate) * (coordinateCount + 1));
            coordinates[coordinateCount] = currentCoordinate;

            coordinateCount++;
            dimensionCount = 0;
        } else if (c == ',') {
            numBuffer
            

        }
    }
}

int main() {
    ThreeDCoordinate a = { 162, 817, 812 };
    ThreeDCoordinate b = { 425, 690, 689 };
    double result = euclideanDistance(a, b);
    printf("%f \n", result);

    return 0;
}