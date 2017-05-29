//
// Created by Antoine Bartuccio on 14/05/2017.
//

#ifndef FISH_FISH_TYPES_H
#define FISH_FISH_TYPES_H

#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

#define EXIT_SIGNAL -100
#define ERROR_STRING "\n"

/* Custom types */

typedef enum {
	NONE,
	PIPE,
	BACKGROUND_PROCESS,
	AND,
	OR,
	REVERSE_AND
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
	char *PS2;
	struct passwd* passwd;
} Settings;


typedef int (builtinCommand) (WordArray*);

#endif //FISH_FISH_TYPES_H
