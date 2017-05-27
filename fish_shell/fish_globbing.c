// Created by Aethor
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "fish_core.h"
#include "fish_globbing.h"

WordList * fishExpand(WordList *wordList) {

	if(wordList->size > 1){

		int i;
		WordList* newWordList = createWordList();// creating the list to return

		if(newWordList == NULL){//crash when the allocation is unsuccessful
			crash();
    }

    addEndWordList(newWordList, wordList->first->word);//copy the command into the returning word list


		WordListElement* tempElement = wordList->first->next; //temporary nav element

		for(i=1; i<wordList->size; i++){

      //TODO : optimize the stringContains() function to test for a list of characters
      //test if we have to expand a string or not, for optimization purposes
      if(stringContains(tempElement->word, '*') || stringContains(tempElement->word, '?')){

        concatWordList(newWordList, expandWord(tempElement->word));

      }
      //If we dont have to expand, add the current word unchanged to the new list
      else{
        addEndWordList(newWordList, tempElement->word);
      }

			tempElement = tempElement->next;

    }

    freeWordList(wordList);
		return newWordList;

	}

	else return wordList;


}

WordList* expandWord(char* word){

  WordList* wordList = createWordList();
  addEndWordList(wordList, word);
  return wordList;

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

			if(!strcmp(dir->d_name, ".") && !strcmp(dir->d_name, "..")){

				printf("%s\n", dir->d_name);
				files->words[i] = dir->d_name;
				i++;
				files->size++;

			}
			
		}


	}

	return files;

}

