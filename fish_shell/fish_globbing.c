// Created by Arthur Amalvy
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

    //TODO : move this in recursion in case multiples commands are in the same line
    if(newWordList->size == 1){
      addEndWordList(newWordList, (char*) ERROR_STRING);
    }
		return newWordList;

	}

  else return wordList;

}

WordList* expandWord(char* word){

  if(!stringContains(word, '/')){

    return getFiles((char*) "./", word);

  }

  else{

    WordList* testList = splitWordIntoList(word, '/');
    printWordList(testList);
    freeWordList(testList);

    return getFiles(word, (char*) "*");//temporary
    //return();

  }


}




WordList* getFiles(char* path, char* wildcardedString){

	DIR* directory;
	dirent* dir;

	WordList* files = createWordList();


	if((directory = opendir(path)) != NULL){

		while((dir = readdir(directory)) != NULL){

			if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..") && wildcardedStringMatches(wildcardedString, dir->d_name)){//sorry strcmp but I dont like you :(

        //dont read this, and if you do, do not complain, it's strcat's fault. you've been warned.
        char* filePath = (char*) malloc(sizeof(char) * (strlen(path) + strlen(dir->d_name)) + 1);
        if(filePath == NULL) crash();
        filePath[0] = '\0';
        strcat(filePath, path);
        strcat(filePath, dir->d_name);
        addEndWordList(files, filePath);
        free(filePath);

			}

		}

    closedir(directory); //YY U LEAK MEMORY ? NOT ON MY WATCH


	}

	return files;

}


int wildcardedStringMatches(char* string1, char* string2){//TODO

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

		printf("fish : Warning : fuck you, strings are considered null");
		crash();
		return 0;

	}

}

//beware : will purposedly ignore the first occurence of the character
WordList* splitWordIntoList(char* string, char splitChar){

  if(stringContains(string, '/')){

    int i = 0;
    int mark = 0;
    int finished = 0;
    int firstEncounter = 0;
    WordList* newWordList = createWordList();

    while(!finished){

      if(string[i] == splitChar || string[i] == '\0'){

        if(!firstEncounter){

          firstEncounter = 1;

        }

        else{

          char* tempStr = strndup(string + mark, i - mark);

          if(tempStr == NULL){
            crash();
          }

          addEndWordList(newWordList, tempStr);
          free(tempStr);
          mark = i;
          if(string[i] == '\0'){
            finished = 1;
          }
        }

      }
      i++;

    }

    return newWordList;

  }
  else{
    WordList* newWordList = createWordList();
    addEndWordList(newWordList, string);
    return newWordList;
  }

}
