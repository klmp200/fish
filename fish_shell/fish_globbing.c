// Created by Aethor
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "fish_core.h"
#include "fish_globbing.h"

WordList * fishExpand(WordList *wordArray) {

	wordArray = expandInDir("./", "*");

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

			/*if(dir->d_name != "." && dir->d_name != ".."){*/

				printf("%s\n", dir->d_name);
				files->words[i] = dir->d_name;
				i++;
				files->size++;

			//}
			
		}


	}

	return files;

}

int comparator(char* string1, char* string2){//TODO

	int i = 0;
	char tempIChar;
	int j = 0;

	if(string1 != NULL && string2 != NULL){

		while(string1[i] != '\0' && string2[j] != '\0'){

			if(string1[i] == '*'){

				tempIChar = string1[i+1];

				while(string2[j] != tempIChar){

					j++;

					if(string2[j] == '\0' && tempIChar == '\0'){
						return 1;
					}

				}
				i++;

			}

			if(string1[i] != string2[j] && string1[i] != '?'){

				return 0;

			}

			i++;
			j++;

		}

		if(string1[i] == '\0' && string2[j] == '\0'){

			return 1;

		}
		else{

			return 0;

		}


	}

	else{

		printf("warning : fuck you, strings are considered null");
		crash();
		return 0;

	}

}

WordList* expandInDir(char* dir, char* toExpand){

	int i = 0;
	WordList* list = createWordList();
	WordArray* files = getFiles(dir);

	for(i=0; i<files->size;i++){

		if(comparator(toExpand, files->words[i])){

			addWordList(list, files->words[i]);

		}

	}


	return list;

}


