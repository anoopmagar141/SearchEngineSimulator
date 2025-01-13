#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_FILES 10
#define MAX_WORD_LENGTH 50
#define MAX_FILENAME_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    char files[MAX_FILES][MAX_FILENAME_LENGTH];
    int occurrences[MAX_FILES];
    int fileCount;
} InvertedIndex;

InvertedIndex index[MAX_WORDS];
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

// Add a word to the index
void addWordToIndex(const char *word, const char *fileName) {
    for (int i = 0; i < indexSize; i++) {
        if (strcmp(index[i].word, word) == 0) {
            for (int j = 0; j < index[i].fileCount; j++) {
                if (strcmp(index[i].files[j], fileName) == 0) {
                    index[i].occurrences[j]++;
                    return;
                }
            }
            // Add new file entry for the word
            strcpy(index[i].files[index[i].fileCount], fileName);
            index[i].occurrences[index[i].fileCount] = 1;
            index[i].fileCount++;
            return;
        }
    }
       // Add a new word to the index
    strcpy(index[indexSize].word, word);
    strcpy(index[indexSize].files[0], fileName);
    index[indexSize].occurrences[0] = 1;
    index[indexSize].fileCount = 1;
    indexSize++;
}
// Parse a file and add its words to the index
void parseFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", fileName);
        return;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%49s", word) == 1) {
        normalizeWord(word);
        if (strlen(word) > 0) {
            addWordToIndex(word, fileName);
        }
    }

    fclose(file);
    printf("File '%s' indexed successfully.\n", fileName);
}
// Search for a word in the index
void searchWord(const char *word) {
    for (int i = 0; i < indexSize; i++) {
        if (strcmp(index[i].word, word) == 0) {
            printf("Word '%s' found in:\n", word);
            for (int j = 0; j < index[i].fileCount; j++) {
                printf("  File: %s (Occurrences: %d)\n", index[i].files[j], index[i].occurrences[j]);
            }
            return;
        }
    }
    printf("Word '%s' not found.\n", word);
}
// Display the complete index
void displayIndex() {
    if (indexSize == 0) {
        printf("Index is empty.\n");
        return;
    }

    printf("\n--- Index Content ---\n");
    for (int i = 0; i < indexSize; i++) {
        printf("Word: %s\n", index[i].word);
        for (int j = 0; j < index[i].fileCount; j++) {
            printf("  File: %s (Occurrences: %d)\n", index[i].files[j], index[i].occurrences[j]);
        }
    }
}
