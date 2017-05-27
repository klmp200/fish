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

WordList * sliceWordList(WordList *list, int min_index, int max_index);

void addEndWordList(WordList *list, char *word); // Tested

void addBeginWordList(WordList *list, char *word);

void removeWordList(WordList *list); // Tested

void removeWordListElem(WordList *list, WordListElement *elem);

void freeWordList(WordList *list); // Tested

WordArray * wordListToWordArray(WordList *list); // Tested

WordList * wordArrayToWordList(WordArray * array); // Tested

WordList * splitWordList(WordList *list, char *regex);

char * splitWord(char * origin, int beginning_index, int size_to_delete); // Tested

WordList* concatWordList(WordList* list1, WordList* list2);

int stringContains(char* string, char charToTest);

WordList* concatWordList(WordList* list1, WordList* list2);

int stringContains(char* string, char charToTest);

#endif //FISH_FISH_UTILS_H
