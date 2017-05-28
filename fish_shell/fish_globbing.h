#ifndef FISH_FISH_GLOBBING_H
#define FISH_FISH_GLOBBING_H

typedef struct dirent dirent;


WordList* fishExpand(WordList* wordArray);

WordList* getFiles(char* path, char* wildcardedString);

WordList* expandWord(char* word);

int wildcardedStringMatches(char* string1, char* string2);

#endif //FISH_FISH_GLOBBING_H
