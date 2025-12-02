#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    char c;
    char buffer[1024];
    int wordLength = 0;
    char **words = NULL;
    int wordCount = 0;

    while ((c = fgetc(input)) != EOF) {
        if (c == ',' || c == '\n') {
            buffer[wordLength] = '\0';

            words = realloc(words, (wordCount + 1) * sizeof(char*));
            words[wordCount] = malloc(strlen(buffer) + 1);
            strcpy(words[wordCount], buffer);

            wordCount++;
            wordLength = 0;
        } else {
            buffer[wordLength++] = c;
        }
    }

    fclose(input);

    for (int i = 0; i < wordCount; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }

    free(words);

    return 0;
}