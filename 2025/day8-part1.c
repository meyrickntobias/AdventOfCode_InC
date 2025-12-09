#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "input_processing.h"
#include <string.h>
#include <ctype.h>

typedef struct {
    int a;
    int b;
    int c;
} ThreeDCoordinate;

typedef struct {
    ThreeDCoordinate* coordinates;
    int count;
} Input;

typedef struct Junction {
    ThreeDCoordinate coordinate;
    struct Junction* circuit;
    int connectedJunctionBoxes;
} JunctionBox;

typedef struct {
    ThreeDCoordinate other;
    double distance;
} DistanceMap;

typedef struct {
    ThreeDCoordinate myself;
    DistanceMap* distances; 
} DistanceMapCollection;

double euclideanDistance(ThreeDCoordinate p, ThreeDCoordinate q) {
    double A = pow((p.a - q.a), 2);
    double B = pow((p.b - q.b), 2);
    double C = pow((p.c - q.c), 2);

    return sqrt(A + B + C);
}

int compare(const void *a, const void *b) {
    const DistanceMap *valA = a;
    const DistanceMap *valB = b;
    double difference = valA->distance - valB->distance;
    
    if (difference > 0) {
        return 1;
    } else if (difference < 0) {
        return -1;
    } else {
        return 0;
    }
}


Input processInput(char *fileName) {
    char inputBuffer[1000];
    readFile(fileName, inputBuffer);
    ThreeDCoordinate coordinates[1000];
    ThreeDCoordinate currentCoordinate;

    int coordinateCount = 0;

    LineCollection inputLines = splitIntoLines(inputBuffer); 

    for (int i = 0; i < inputLines.lineCount; i++) {
        char* token = strtok(inputLines.lines[i], ",");
        if (isDigit(token)) currentCoordinate.a = atoi(token);

        token = strtok(NULL, ",");
        if (isDigit(token)) currentCoordinate.b = atoi(token);

        token = strtok(NULL, ",");
        if (isDigit(token)) currentCoordinate.c = atoi(token);

        coordinates[coordinateCount] = currentCoordinate;
        coordinateCount++;
    }

    Input input = { coordinates, coordinateCount };
    return input;
}

int main() {
    Input input = processInput("input/day8_sample.txt");

    /*
        Store distance between each coordinate {162,817,812} - ({57,618,57}, 123.58), ...
        Connect coordinate with shortest distance to other coordinate, maintain a list of connections

        Maintain a list of JunctionBoxes, each has:
         - A coordinate
         - A pointer to other connected coordinates
         - A count of connected coordinates
    */
    DistanceMapCollection map[input.count];

    for (int i = 0; i < input.count; i++) {
        DistanceMapCollection distances;
        distances.myself = input.coordinates[i];
        distances.distances = malloc(sizeof(DistanceMap) * (input.count - 1));
        int distanceCount = 0;

        for (int j = 0; j < input.count; j++) {
            if (i == j) continue; 
            double distance = euclideanDistance(input.coordinates[i], input.coordinates[j]);
            DistanceMap distanceFromMyself = { input.coordinates[j], distance };
            distances.distances[distanceCount++] = distanceFromMyself;
        }

        map[i] = distances;
    }

    for (int i = 0; i < input.count; i++) {
        printf("{ %d, %d, %d } -> ", map[i].myself.a, map[i].myself.b, map[i].myself.c);
        qsort(map[i].distances, input.count - 1, sizeof(DistanceMap), compare);
        for (int j = 0; j < input.count - 1; j++) {
            ThreeDCoordinate other = map[i].distances[j].other;
            printf("({%d,%d,%d}, d = %f), ", other.a, other.b, other.c, map[i].distances[j].distance);
        }
        printf("\n\n");
    }



    return 0;
}