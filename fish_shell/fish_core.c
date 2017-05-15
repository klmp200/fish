//
// Created by Antoine Bartuccio on 11/05/2017.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fish_core.h"

#define FISH_BUFFER_SIZE 1024
#define FISH_TOKENS " \t\r\n\a"

void fishLoop(Settings * settings){
	char * line = NULL;
	WordArray * splited = NULL;
	int status = 1;

	do {
		printf("%s", settings->PS1);
		line = fishReadLine();
		line = fishExpand(line);

		splited = split(line, FISH_TOKENS);

		status = fishExecute(splited);

		freeWordArray(splited);
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

WordArray * split(char *string, char *separator){
	int array_size = countSeparators(string, separator) + 1;
	WordArray *tokens = (WordArray*) malloc(sizeof(WordArray));
	char *to_delete = strdup(string);
	char *to_delete_bak = to_delete;
	char *token = NULL;
	int i = 0;

	if (tokens != NULL){
		tokens->words = (char **) malloc(sizeof(char*) * (array_size + 1));
		tokens->words[array_size] = NULL;
		tokens->size = array_size;
	}

	if (tokens == NULL || to_delete == NULL || tokens->words == NULL){
		crash();
	}

	while((token = strsep(&to_delete, separator)) != NULL){
		tokens->words[i] = strdup(token);
		i++;
	}

	free(to_delete_bak);

	return tokens;
}

void freeWordArray(WordArray *array) {
	int i;
	if (array != NULL) {
		for (i = 0; i < array->size; i++) {
			free(array->words[i]);
		}
		free(array->words);
		free(array);
	}

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

char *fishExpand(char *line) {
	return line;
}

Settings *getSettings() {
	Settings *s = (Settings*) malloc(sizeof(Settings));
	if (s == NULL){
		crash();
	}
	s->PS1 = strdup("\n~>");

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
