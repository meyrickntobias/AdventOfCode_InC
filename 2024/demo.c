#include <stdio.h>

int main() {
  FILE *input = fopen("sample_input.txt", "r");

  char c;
  char **words;
  char delimiter = ',';
  int wordIndex = 0;
  int charIndex = 0;
  char *currentWord = 0;

  while ((c = fgetc(input)) != EOF) {
    if (c == delimiter) {
      words[wordIndex] = currentWord;
    } else {
      currentWord[charIndex] = c;
    }
    printf("%c", c);
  }

  // Iterate over all characters, adding each word to an array of words

  words[0] = "Hello";
  words[1] = "World";

  for (int i = 0; i < 2; i++) {
    printf(words[i]);
  }
}
