//
// Created by Antoine Bartuccio on 15/05/2017.
//

#ifndef FISH_FISH_UTILS_H
#define FISH_FISH_UTILS_H

#include "fish_types.h"

void crash(); // Tested

char *getInsult(); // Tested

void freeWordArray(WordArray *array); // Tested

WordList * createWordList(); // Tested

void addWordList(WordList *list, char *word); // Tested

void removeWordList(WordList *list); // Tested

void freeWordList(WordList *list); // Tested

WordArray * wordListToWordArray(WordList *list); // Tested

WordList * wordArrayToWordList(WordArray * array); // Tested

#endif //FISH_FISH_UTILS_H
