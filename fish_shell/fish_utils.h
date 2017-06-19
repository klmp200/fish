//
// Created by Antoine Bartuccio on 15/05/2017.
//

#ifndef FISH_FISH_UTILS_H
#define FISH_FISH_UTILS_H

#include "fish_types.h"

/* Crash the application and throw a random error message in english */
void crash(); // Tested

/* Get a random french insult for the user */
char *getInsult(); // Tested

/* Free a WordArray */
void freeWordArray(WordArray *array); // Tested

/* Create a new WordList */
WordList * createWordList(); // Tested

/* Cut a WordList and throw every word contained between the two index */
WordList * sliceWordList(WordList *list, int min_index, int max_index);

/* Add a world at the end of a WordList */
void addEndWordList(WordList *list, char *word); // Tested

/* Add a word at the beginning of a WordList */
void addBeginWordList(WordList *list, char *word);


/* Delete an entire WordList */
void removeWordList(WordList *list); // Tested

/* Remove an element from a WordList */
void removeWordListElem(WordList *list, WordListElement *elem);

/* Free an entire WordList */
void freeWordList(WordList *list); // Tested

/* Convert a WordList into a WordArray */
WordArray * wordListToWordArray(WordList *list); // Tested

/* Convert a WordArray into a WordList */
WordList * wordArrayToWordList(WordArray * array); // Tested

/* Split a WordList according to a given regex */
WordList * splitWordList(WordList *list, char *regex);

/* Split a word from a given index removing parts according to the size to delete */
char * splitWord(char * origin, int beginning_index, int size_to_delete); // Tested

/* Put the second WordList into the first one */
void concatWordList(WordList* list1, WordList* list2);

/* Print a WordList for debug */
void printWordList(WordList* list);

/* Detect if a string contains a given character */
int stringContains(char* string, char charToTest);

/* Better than Strcat */
char* trueStrcat(char* string1, char* string2);

/* Check if the given path is a directory */
int isDirectory(char* path);


#endif //FISH_FISH_UTILS_H
