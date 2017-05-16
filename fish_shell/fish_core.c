//
// Created by Antoine Bartuccio on 11/05/2017.
// Dont forget that Antoine Bartuccio is a faggot since 1784 (tm)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fish_core.h"
#include "fish_globbing.h"
#include "fish_types.h"

void fishLoop(Settings * settings){
	char * line = NULL;
	WordList* splited = NULL;
	int status = 1;

    do {
        printf("%s", settings->PS1);
        line = fishReadLine();

		splited = split(line, (char*) FISH_TOKENS);
		splited = fishExpand(splited);

		status = fishExecute(splited);

		free(line);

	} while(status != EXIT_SIGNAL);
}

int countSeparators(char *string, char *separators) {
	int nb = 0;
	int i = 0;
	int k = 0;
	while (string[i] != '\0'){
		while (separators[k] != '\0'){
			if (string[i] == separators[k]){
				nb++;
			}
			k++;
		}
		i++;
		k = 0;
	}
	return nb;
}

WordList * split(char *string, char *separator){
	WordList *list = createWordList();
	char *to_delete = strdup(string);
	char *to_delete_bak = to_delete;
	char *token = NULL;

	if (to_delete == NULL){
		crash();
	}

	while((token = strsep(&to_delete, separator)) != NULL)
		addWordList(list, token);

	free(to_delete_bak);

	return list;
}

char *fishReadLine() {
	size_t bufferSize = FISH_BUFFER_SIZE;
	int position = 0;
	char *line = (char*) malloc(sizeof(char*) * bufferSize);
	int c;

	if (line == NULL){
		crash();
	}

	while (1){
		c = getchar();

		switch (c){
			case '\n':
				line[position] = '\0';
				return line;
			case EOF:
				exit(EXIT_SUCCESS);
			default:
				line[position] = (char) c;
		}

		position++;

		if ((size_t) position > bufferSize){
			bufferSize+=bufferSize;
			line = (char*) realloc(line, bufferSize);
			if (line == NULL){
				crash();
			}
		}
	}


	return NULL;
}

Settings *getSettings() {
	Settings *s = (Settings*) malloc(sizeof(Settings));
	if (s == NULL){
		crash();
	} else {
		s->PS1 = strdup("\n~>");
	}

	return s;
}

void freeSettings(Settings *settings){
	if (settings != NULL){
		free(settings->PS1);
		free(settings);
	}
}

int fishLoad(WordArray *array) {
	pid_t pid;
	int status = 1;

	pid = fork();
	if (pid == 0){
		/* Executes only in the child process */
		if (execvp(array->words[0], array->words) == -1){
			/* Error during system call */
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	} else if (pid < 0){
		/* Fork failed */
		perror("fish");
	} else {
		/* Handle parent process */

		/* Wait for the child process to finish */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (status) fprintf(stderr, "%s\n", getInsult());
	}
	return status;
}

int fishExecute(WordList *list) {
	WordList *splited = NULL;
	shell_operator op = NONE;
	WordArray *array = NULL;
	int signal = 1;

	splited = parseWordList(list, &op);
	array = wordListToWordArray(list);

	signal = loadRightCommand(array);
	if (signal == EXIT_SIGNAL){
		if (splited != NULL) freeWordList(splited);
		if (array != NULL) freeWordArray(array);
		return signal;
	}
	switch (op) {
		case AND:
			if (!signal) signal = fishExecute(splited);
			else {
				if (splited != NULL) freeWordList(splited);
			}
			break;
		case OR:
			signal = fishExecute(splited);
			break;
		default:
			break;
	}
	return signal;

}

int loadRightCommand(WordArray *array){
	int i;
	if (array->size <= 0) return 1;
	for (i = 0; i < getNbBuiltins(); i++) {
		if (!strcmp(array->words[0], getBuiltinCommandsStr()[i])) {
			return getBuiltinCommands()[i](array);
		}
	}
	return fishLoad(array);
}

WordList * parseWordList(WordList *list, shell_operator *an_operator) {
	char *op_str[] = {
			(char*) "||",
			(char*) "&&"
	};
	shell_operator op[] = {
			OR,
			AND
	};
	WordList *newList = NULL;
	int max = sizeof(op_str) / sizeof(char*);
	int i = 0;

	while (i < max && newList == NULL){
		newList = splitWordList(list, op_str[i]);
		i++;
	}

	if (newList != NULL) *an_operator = op[i-1];
	else *an_operator = NONE;

	return newList;
}
