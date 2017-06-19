#ifndef FISH_FISH_GLOBBING_H
#define FISH_FISH_GLOBBING_H

typedef struct dirent dirent;


/*send back a WordList containing every path correspnding to the different expand*/
WordList* fishExpand(WordList* wordArray);

/*return a WordList containing every file in a path corresponding to a bash-like regex*/
WordList* getFiles(char* path, char* wildcardedString);


/*return a WordList containing every path corresponding to the expand of a word ( in shell meaning )*/
WordList* expandWord(char* word);

/*Launch recursively the expand for every directory, and add each found path in listToExpand*/
void recursiveExpandWord(char* path, WordList* listToExpand);

/*function returning true or false, depending on the regex matching of string2 with string1*/
int wildcardedStringMatches(char* string1, char* string2);


/*transform a string in a word list by splitting on splitchar*/
WordList* splitWordIntoList(char* string, char splitchar);


/*Given a string, return only the corresponding filename, deleting the path*/
char* getFileName(char* string);

/*Given a string, return only the corresponding path, cutting the filename*/
char* getPath(char* string);

/*Transform a word list into a string by concatenating every element of the list*/
char* concatWordListToWord(WordList* list, int firstElemIndex, int lastElemIndex);

#endif //FISH_FISH_GLOBBING_H
