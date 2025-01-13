#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constants
int indexSize = 0;

// Normalize a word: convert to lowercase and remove punctuation
void normalizeWord(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        word[i] = tolower(word[i]);
        if (ispunct(word[i])) {
            word[i] = '\0';
            break;
        }
    }
}