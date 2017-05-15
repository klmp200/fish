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

#define FISH_BUFFER_SIZE 1024
#define FISH_TOKENS " \t\r\n\a"

void fishLoop(Settings * settings){
	char * line = NULL;
	WordList* splited = NULL;
	WordArray* array = NULL;
	int status = 1;

    do {
        printf("%s", settings->PS1);
        line = fishReadLine();

        splited = split(line, FISH_TOKENS);
		splited = fishExpand(splited);

		array = wordListToWordArray(splited);
		status = fishExecute(array);

		freeWordArray(array);
		free(line);
	} while(status);
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
	char *line = malloc(sizeof(char*) * bufferSize);
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
			line = realloc(line, bufferSize);
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
	int status;

	pid = fork();
	if (pid == 0){
		/* Executes only in the child process */
		if (execvp(array->words[0], array->words) == -1){
			/* Error during system call */
			perror("fish");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0){
		/* Fork failed */
		perror("fish");
	} else {
		/* Handle parent process */

		/* Wait for the child process to finish */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int fishExecute(WordArray *array) {
	int i;
	if (array->size < 0)
		return 1;

	for (i=0; i < getNbBuiltins(); i++){
		if (!strcmp(array->words[0], getBuiltinCommandsStr()[i])){
			return getBuiltinCommands()[i](array);
		}
	}

	return fishLoad(array);
}
