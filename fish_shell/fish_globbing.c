// Created by Aethor
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "fish_core.h"
#include "fish_globbing.h"

WordArray* fishExpand(WordArray *wordArray) {

	int i;
	WordArray* expandedParameters = (WordArray*) malloc(sizeof(WordArray));

	for(i=0; i<wordArray->size; i++){


	}

	return wordArray;

}



WordArray * getFiles(char* path){

	DIR* directory;
	dirent* dir;
	int i = 0;

	WordArray* files = (WordArray*) malloc(sizeof(WordArray));


	if((directory = opendir(path)) != NULL){

		while((dir = readdir(directory)) != NULL){

			i++;

		}

		files->words = (char **) malloc(sizeof(char*) * (i + 1));

		closedir(directory);
		directory = opendir(path);
		i = 0;

		while((dir = readdir(directory)) != NULL){

			files->words[i] = dir->d_name;

		}


	}

	return files;

}

bool comparator(char* string1, char* string2){//TODO

	return true;

}


