//
// Created by Antoine Bartuccio on 11/05/2017.
//

#ifndef FISH_FISH_LIB_H
#define FISH_FISH_LIB_H

typedef struct {
    char * word;
    size_t size;
} Word;

void fishLoop();

char * fishReadLine();

Word * split(char *string, char *separator);

int countSeparator(char *string, char separator);

void freeWordArray(Word *array, int size);

#endif //FISH_FISH_LIB_H
