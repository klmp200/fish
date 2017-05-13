//
// Created by Antoine Bartuccio on 11/05/2017.
//

#ifndef FISH_FISH_LIB_H
#define FISH_FISH_LIB_H

typedef struct {
    char ** words;
    int size;
} WordArray;

typedef struct {
    char *PS1;
} Settings;

/* WordArray functions */

WordArray * split(char *string, char *separator);
void freeWordArray(WordArray *array);

/* Settings functions */

Settings * getSettings();


/* General purpose functions */

void fishLoop(Settings * settings);

char * fishReadLine();

int countSeparators(char *string, char *separators);

char * fishExpand(char* line);

#endif //FISH_FISH_LIB_H
