//
// Created by Antoine Bartuccio on 11/05/2017.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fish_lib.h"

void fishLoop(){
    printf("banana");
}

int countSeparator(char *string, char separator) {
    int nb = 0;
    int i = 0;
    while (string[i] != '\0'){
        if (string[i] == separator){
            nb++;
        }
        i++;
    }
    return nb;
}

Word * split(char *string, char *separator){
    int array_size = countSeparator(string, separator[0]) + 1;
    Word *tokens = malloc(sizeof(Word) * array_size);
    char *to_delete = strdup(string);
    char *token = NULL;
    int i = 0;

    if (tokens == NULL || to_delete == NULL){
        fprintf(stderr, "fish: Error allocating fucking pointer !");
        exit(EXIT_FAILURE);
    }

    while((token = strsep(&to_delete, separator)) != NULL){
        printf("%s\n", token);
        tokens[i].word = strdup(token);
        tokens[i].size = strlen(token);
    }

    free(to_delete);

    return tokens;
}

void freeWordArray(Word *array, int size) {
    int i;
    for (i=0;i<size;i++){
        free(array + i);
    }
    free(array);

}

char *fishReadLine() {
    return NULL;
}

