#ifndef FISH_FISH_GLOBBING_H
#define FISH_FISH_GLOBBING_H

typedef struct dirent dirent;


WordList * fishExpand(WordList *wordArray);

WordArray* getFiles(char* path);

/*char1 is a string with characters such as '*', '.' or '?' having special meanings*/
int comparator(char* string1, char* string2);

#endif //FISH_FISH_GLOBBING_H
