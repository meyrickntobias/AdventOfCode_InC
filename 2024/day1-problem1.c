#include <stdio.h>
#include <stdlib.h>

// TODO: what sorting algorithm is this?
int *sort(int list[], int sizeOfList) {
  // iterate over list and sort
  for (int i = 0; i < sizeOfList; i++) {
    int min = list[i];
    int minIndex = i;

    for (int j = i; j < sizeOfList; j++) {
      if (list[j] < min) {
        min = list[j];
        minIndex = j;
      }
    }

    // Swap the min value
    int valueAtI = list[i];
    list[i] = min;
    list[minIndex] = valueAtI;
  }

  return list;
}

int main() {
  // TODO: parse text input file
  FILE *input = fopen("sample_input.txt", "r");

  if (input == NULL) {
    printf("File would not open!\n");
    return -1;
  }

  char c;
  int i = 0;

  while ((c = fgetc(input)) != EOF) {
    printf("%c", c);
  }

  fclose(input);

  /*

  int listA[] = {3, 4, 2, 1, 3, 3};
  int listB[] = {4, 3, 5, 3, 9, 3};

  int sizeOfListA = sizeof(listA) / sizeof(listA[0]);

  int *sortedListA = sort(listA, sizeOfListA);
  int *sortedListB = sort(listB, sizeOfListA);

  int totalDistance = 0;
  for (int i = 0; i < sizeOfListA; i++) {
    int diff = abs(sortedListA[i] - sortedListB[i]);
    // printf("%d ", diff);
    totalDistance += diff;
  }

  printf("%d ", totalDistance);

  */
  return 0;
}
