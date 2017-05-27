#ifndef FISH_FISH_GLOBBING_H
#define FISH_FISH_GLOBBING_H

typedef struct dirent dirent;


WordList * fishExpand(WordList *wordArray);

WordArray* getFiles(char* path);

WordList* expandWord(char* word);

#endif //FISH_FISH_GLOBBING_H
