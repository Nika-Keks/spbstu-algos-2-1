#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./structure.h"

// Assuming that words are not longer than 128 characters
#define MAX_WORD_LENGTH 128

Node* readFile(char const* fileName) {
    FILE* fileStream = fopen(fileName, "r");

    if (!fileStream) {
        printf("Could not open the file %s", fileName);
        exit(0);
    }

    const int wordSize = sizeof(char) * MAX_WORD_LENGTH;
    Node* wordsArray = listCreate();
    char* buffer = malloc(wordSize);
    char* currentWord = malloc(wordSize);

    while (fscanf(fileStream, "%s", buffer) != EOF) {
        memcpy(currentWord, buffer, wordSize);
        listPush(wordsArray, currentWord);
        currentWord = malloc(wordSize);
    }

    fclose(fileStream);

    return wordsArray;
}

Node* mergeArrays(Node* firstArray, Node* secondArray) {
    Node* mergedArray = listCreate();

    for (Node* node = firstArray; node != NULL; node = node->next) {
        listPush(mergedArray, node->value);
    }

    for (Node* node = secondArray; node != NULL; node = node->next) {
        listPush(mergedArray, node->value);
    }

    return mergedArray;
}

void insertionSort(Node* array) {
    char* word;
    int i = 1;
    int j;

    for (Node* node = array->next; node != NULL; node = node->next) {
        word = node->value;
        j = i - 1;

        while (j >= 0 && strcmp(listAt(array, j)->value, word) > 0) {
            listAt(array, j + 1)->value = listAt(array, j)->value;
            j -= 1;
        }

        listAt(array, j + 1)->value = word;
        i += 1;
    }
}