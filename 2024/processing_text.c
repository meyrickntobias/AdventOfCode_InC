#include <stdio.h>
#include <string.h>

int main() {
    // open file
    FILE *input = fopen("input.txt", "r");
    char c;
    int wordLength = 0;
    int wordCount = 0;
    char buffer[1024];
    char **words;

    while ((c = fgetc(input)) != EOF) {
        if (c == ',') {
            wordCount++;
            buffer[wordLength + 1] = "\0";
            printf("(%d)", wordLength);

            char *word = malloc(sizeof(buffer[0]) * wordLength + 1);
            strcpy(word, buffer);

            realloc(words, wordCount * sizeof(*word));

            wordLength = 0;
            printf("\n");
            continue;
        }
        
        buffer[wordLength] = c;

        printf("%c", c);
        wordLength++;
    }

    /* 
    words

    printf("Hello world");
    */

    return 0;
}