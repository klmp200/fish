//
// Created by Antoine Bartuccio on 14/05/2017.
//

#ifndef FISH_FISH_TYPES_H
#define FISH_FISH_TYPES_H

#define EXIT_SIGNAL -100

/* Custom types */

typedef enum {
	NONE,
	PIPE,
	BACKGROUND_PROCESS,
	AND,
	OR
} shell_operator ;

typedef struct {
	char ** words;
	int size;
} WordArray;

typedef struct elem {
	char * word;
	struct elem * previous;
	struct elem * next;
} WordListElement;

typedef struct {
	int size;
	WordListElement * first;
	WordListElement * last;
} WordList;

typedef struct {
	char *PS1;
} Settings;


typedef int (builtinCommand) (WordArray*);

#endif //FISH_FISH_TYPES_H
