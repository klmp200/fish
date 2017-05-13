//
// Created by Antoine Bartuccio on 11/05/2017.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fish_lib.h"

#define FISH_BUFFER_SIZE 1024
#define FISH_TOKENS " \t\r\n\a"

void fishLoop(Settings * settings){
    char * line = NULL;
    WordArray * splited = NULL;
    int exited = 0;
    int i;

    while (!exited) {
        printf("%s", settings->PS1);
        line = fishReadLine();
        line = fishExpand(line);

        splited = split(line, FISH_TOKENS);
        for (i = 0; i < splited->size; i++) {
            printf("%s\n", splited->words[i]);
            if(!strcmp(splited->words[i], "exit"))
                exited = 1;
        }

        freeWordArray(splited);
        free(line);
    }
}

int countSeparators(char *string, char *separators) {
    int nb = 0;
    int i = 0;
    int k = 0;
    while (string[i] != '\0'){
        while (separators[k] != '\0'){
            if (string[i] == separators[k]){
                nb++;
            }
            k++;
        }
        i++;
        k = 0;
    }
    return nb;
}

WordArray * split(char *string, char *separator){
    int array_size = countSeparators(string, separator) + 1;
    WordArray *tokens = (WordArray*) malloc(sizeof(WordArray));
    char *to_delete = strdup(string);
    char *token = NULL;
    int i = 0;

    if (tokens != NULL){
        tokens->words = (char **) malloc(sizeof(char*) * array_size);
        tokens->size = array_size;
    }

    if (tokens == NULL || to_delete == NULL || tokens->words == NULL){
        fprintf(stderr, "fish: Error allocating fucking pointer !");
        exit(EXIT_FAILURE);
    }

    while((token = strsep(&to_delete, separator)) != NULL){
        tokens->words[i] = strdup(token);
        i++;
    }

    free(to_delete);

    return tokens;
}

void freeWordArray(WordArray *array) {
    int i;
    if (array != NULL) {
        for (i = 0; i < array->size; i++) {
            free(array->words[i]);
        }
        free(array);
    }

}

char *fishReadLine() {
    size_t bufferSize = FISH_BUFFER_SIZE;
    int position = 0;
    char *line = malloc(sizeof(char*) * bufferSize);
    int c;

    if (line == NULL){
        fprintf(stderr, "fish: Error allocating fucking buffer shit !");
        exit(EXIT_FAILURE);
    }

    while (1){
        c = getchar();

        if (c == EOF || c == '\n'){
            line[position] = '\0';
            return line;
        } else {
            line[position] = (char) c;
        }

        position++;

        if ((size_t) position > bufferSize){
            bufferSize+=bufferSize;
            line = realloc(line, bufferSize);
            if (line == NULL){
                fprintf(stderr, "fish: Error allocating fucking buffer shit !");
                exit(EXIT_FAILURE);
            }
        }
    }


    return NULL;
}

char *fishExpand(char *line) {
    return line;
}

Settings *getSettings() {
    Settings *s = (Settings*) malloc(sizeof(Settings));
    if (s == NULL){
        fprintf(stderr, "fish: Error allocating fucking settings");
        exit(EXIT_FAILURE);
    }
    s->PS1 = strdup("~>");

    return s;
}

