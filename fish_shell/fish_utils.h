//
// Created by Antoine Bartuccio on 15/05/2017.
//

#ifndef FISH_FISH_UTILS_H
#define FISH_FISH_UTILS_H

#include "fish_types.h"

void crash();

char *getInsult();

void freeWordArray(WordArray *array);

WordList * createWordList();

void addWordList(WordList *list, char *word);

void removeWordList(WordList *list);

void freeWordList(WordList *list);

WordArray * wordListToWordArray(WordList *list);

WordList * wordArrayToWordList(WordArray * array);

#endif //FISH_FISH_UTILS_H
