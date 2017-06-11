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
	REVERSE_AND,
	REDIRECT_STDOUT_ERASE,
	REDIRECT_STDOUT_APPEND,
	REDIRECT_STDERR_ERASE,
	REDIRECT_STDERR_APPEND,
	REDIRECT_STDIN
} shell_operator ;

typedef enum {
	READ,
	WRITE,
	READ_AND_WRITE
} redirection_mode ;

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

typedef struct {
	int to_use;
	int nb;
	int nb_max;
	int file_use;
	int tmp_files[2];
	char * files_name[2];
	redirection_mode read;
} pipe_redirection;

typedef int (builtinCommand) (WordArray*);

#endif //FISH_FISH_TYPES_H
