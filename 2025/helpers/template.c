#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "input_processing.h"
#include "helpers/grid.h"

int main() {
    clock_t start, end;
    double time_spent;
    start = clock();
    
    /*
        Solutuon goes here
    */

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time %f seconds\n", time_spent);

    return 0;
}