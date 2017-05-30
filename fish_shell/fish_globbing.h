#ifndef FISH_FISH_GLOBBING_H
#define FISH_FISH_GLOBBING_H

typedef struct dirent dirent;


WordList* fishExpand(WordList* wordArray);

WordList* getFiles(char* path, char* wildcardedString);

WordList* expandWord(char* word);

void recursiveExpandWord(char* path, WordList* listToExpand);

int wildcardedStringMatches(char* string1, char* string2);

WordList* splitWordIntoList(char* string, char splitchar);

char* getFileName(char* string);

char* getPath(char* string);

char* concatWordListToWord(WordList* list, int firstElemIndex, int lastElemIndex);

#endif //FISH_FISH_GLOBBING_H
