//
// Created by Antoine Bartuccio on 11/05/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pcre.h>
#include "fish_core.h"
#include "fish_globbing.h"
#include "fish_types.h"

pipe_redirection * getRedirection(){
	static pipe_redirection * redirection = NULL;

	if (redirection == NULL){
		redirection = (pipe_redirection*) malloc(sizeof(pipe_redirection));
		if (redirection == NULL) crash();
		redirection->files_name[0] = strdup((char*) "/tmp/fishXXXXXX");
		redirection->files_name[1] = strdup((char*) "/tmp/fishXXXXXX");
		redirection->tmp_files[0] = mkstemp(redirection->files_name[0]);
		redirection->tmp_files[1] = mkstemp(redirection->files_name[1]);
		redirection->to_use = 0;
		redirection->read = WRITE;
		redirection->nb = 0;
		redirection->nb_max = 0;
		redirection->file_use = 0;
	}

	return redirection;

}

void freeRedirection(){
	pipe_redirection * redirection = getRedirection();
	close(redirection->tmp_files[0]);
	close(redirection->tmp_files[1]);
	unlink(redirection->files_name[0]);
	unlink(redirection->files_name[1]);
	remove(redirection->files_name[0]);
	remove(redirection->files_name[1]);
	free(redirection->files_name[0]);
	free(redirection->files_name[1]);
	free(redirection);
}


void fishLoop(Settings * settings){
	char * line = NULL;
	WordList* splited = NULL;
	int status = 1;
	pipe_redirection *r = getRedirection();

    do {
        printf("%s", settings->PS1);
        line = fishReadLine();

		r->to_use = 0;
		r->nb = countSeparators(line, "\\|[^\\|]");
		r->nb_max = r->nb;
		splited = split(line, (char*) FISH_TOKENS);
		splited = fishExpand(splited);

		status = fishExecute(splited);

		free(line);

	} while(status != EXIT_SIGNAL);
}

int countSeparators(char *string, char *regex) {
	const char* error;
	int error_offset;
	int ovector[100];
	int nb = 0;
	int string_size = (int) strlen(string);
	int ovector_size = 100;
	int offset = 0;
	pcre *re = pcre_compile(regex, 0, &error, &error_offset, 0);

	if (!re) crash();

	while (pcre_exec(re, 0, string, string_size, offset, 0, ovector, ovector_size) >= 0){
		offset = ovector[1];
		nb++;
	}
	pcre_free(re);

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
		addEndWordList(list, token);

	free(to_delete_bak);

	return list;
}

char *fishReadLine() {
	struct sigaction signal_handler;
	size_t bufferSize = FISH_BUFFER_SIZE;
	int position = 0;
	char *line = (char*) malloc(sizeof(char*) * bufferSize);
	int c;

	if (line == NULL) crash();

	signal_handler.sa_handler = fishSignalHandler;
	sigemptyset(&signal_handler.sa_mask);
	signal_handler.sa_flags = 0;

	while (1){
		sigaction(SIGINT, &signal_handler, NULL);
		c = getchar();

		switch (c){
			case '\n':
				line[position] = '\0';
				return line;
			default:
				line[position] = (char) c;
		}

		position++;

		if ((size_t) position > bufferSize){
			bufferSize += bufferSize;
			line = (char*) realloc(line, bufferSize);
			if (line == NULL){
				crash();
			}
		}
	}

	return NULL;
}


int fishLoad(WordArray *array) {
	pid_t pid;
	int status = 1;
	pipe_redirection *redirection = getRedirection();

	pid = fork();
	if (pid == 0){
		if (redirection->to_use){
			if (redirection->read == READ){
				dup2(redirection->tmp_files[redirection->file_use], STDIN_FILENO);
			} else if (redirection->read == WRITE) {
				dup2(redirection->tmp_files[redirection->file_use], STDOUT_FILENO);
			} else {
				dup2(redirection->tmp_files[!redirection->file_use], STDIN_FILENO);
				dup2(redirection->tmp_files[redirection->file_use], STDOUT_FILENO);
			}
		}
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
	freeWordArray(array);

	return status;
}

int fishExecute(WordList *list) {
	WordList *splited = NULL;
	shell_operator op = NONE;
	WordArray *array = NULL;
	pipe_redirection *redirection = NULL;
	int pid;
	int signal = 1;

	splited = parseWordList(list, &op);
	switch (op) {
		case AND:
			signal = fishExecute(list);
			if (!signal) signal = fishExecute(splited);
			else {
				if (splited != NULL) freeWordList(splited);
				splited = NULL;
			}
			break;
		case REVERSE_AND:
			signal = fishExecute(list);
			if (signal && signal != EXIT_SIGNAL) signal = fishExecute(splited);
			else {
				if (splited != NULL) freeWordList(splited);
				splited = NULL;
			}
			break;
		case OR:
			signal = fishExecute(list);
			if (signal != EXIT_SIGNAL) signal = fishExecute(splited);
			break;
		case PIPE:
			redirection = getRedirection();

			if (redirection->nb == redirection->nb_max){
				redirection->read = WRITE;
				redirection->file_use = 0;
			} else if (redirection->nb > 0){
				redirection->read = READ_AND_WRITE;
				redirection->file_use = !redirection->file_use;
			} else {
				redirection->read = READ;
				redirection->file_use = !redirection->file_use;
			}
			redirection->to_use = 1;
			--redirection->nb;

			if (redirection->read == WRITE) ftruncate(redirection->tmp_files[redirection->file_use], 0);
			lseek(redirection->tmp_files[0], 0L, 0);
			lseek(redirection->tmp_files[1], 0L, 0);

			fishExecute(list);

			redirection->read = WRITE;
			if (redirection->nb > 0){
				redirection->read = READ_AND_WRITE;
			} else {
				redirection->read = READ;
			}
			if (redirection->read == WRITE) ftruncate(redirection->tmp_files[redirection->file_use], 0);
			lseek(redirection->tmp_files[0], 0L, 0);
			lseek(redirection->tmp_files[1], 0L, 0);

			signal = fishExecute(splited);

			redirection->to_use = 0;
			break;
		case BACKGROUND_PROCESS:
			printf("Exécution en tache de fond\n");
			pid = fork();
			if(pid == 0){
				exit(fishExecute(list));
			} else if (pid < 0){
				perror("fish");
			} else if (splited->size > 0) signal = fishExecute(splited);
			else {
				freeWordList(splited);
				splited = NULL;
				signal = EXIT_SUCCESS;
			}
			break;
		default:
			array = wordListToWordArray(list);
			signal = loadRightCommand(array);
			splited = NULL;
	}

	if (signal == EXIT_SIGNAL){
		if (splited != NULL) freeWordList(splited);
		if (array != NULL) freeWordArray(array);
	}

	return signal;

}

int loadRightCommand(WordArray *array){
	int i;
	if (array->size < 0)
		return 1;

	for (i=0; i < getNbBuiltins(); i++){
		if(array->words[0] != NULL){
			if (!strcmp(array->words[0], getBuiltinCommandsStr()[i])){
				return getBuiltinCommands()[i](array);
			}
		}
		else{
			crash();
		}
	}
	return fishLoad(array);
}

WordList * parseWordList(WordList *list, shell_operator *an_operator) {
	char *op_str[] = {
			(char*) ";",
			(char*) "\\|\\|",
			(char*) "&&",
			(char*) "\\|",
			(char*) "&"
	};
	shell_operator op[] = {
			OR,
			REVERSE_AND,
			AND,
			PIPE,
			BACKGROUND_PROCESS
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
