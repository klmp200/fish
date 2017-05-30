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

WordList* expandWord(char* path){

  if(!stringContains(path, '/')){

    return getFiles((char*) "./", path);

  }

  else{

    WordList* expandedList = createWordList();
    recursiveExpandWord(path, expandedList);
    return expandedList;

  }


}

void recursiveExpandWord(char* path, WordList* listToExpand){

  int lastToExpand = 1;
  int i = 0;
  int indexToExpand = -1;

  //TODO : free
  WordList* pathToList = splitWordIntoList(path, '/');
  WordListElement* tempElement; //beware of the size, should be checked before anyway
  tempElement = pathToList->first;


  while(i < pathToList->size - 1 && indexToExpand == -1){

    if(stringContains(tempElement->word, '*') || stringContains(tempElement->word, '?')){
      indexToExpand = i;
      lastToExpand = 0;
    }

    i++;
    tempElement = tempElement->next;

  }


  if(lastToExpand){
    concatWordList(listToExpand, getFiles(getPath(path), getFileName(path)));
    free(pathToList);
  }
  else{

    char* correctedPath = concatWordListToWord(pathToList,0, indexToExpand);
    WordList* foundFiles = getFiles(getPath(correctedPath), getFileName(correctedPath));

    if(foundFiles->size > 0){

      tempElement = foundFiles->first;
      char* concatenedEndOfPath = concatWordListToWord(foundFiles, indexToExpand + 1, foundFiles->size - 1);

        for(i=0; i < foundFiles->size; i++){

          tempElement->word = trueStrcat(tempElement->word, concatenedEndOfPath);
          recursiveExpandWord(tempElement->word, listToExpand);

          tempElement = tempElement->next;

        }

      free(concatenedEndOfPath);

    }

    freeWordList(pathToList);
    free(correctedPath);
    freeWordList(foundFiles);

  }


}

char* concatWordListToWord(WordList* list,int firstElemIndex, int lastElemIndex){

  if(list->size == 0 || list == NULL) crash();

  int i;
  char* concatenedString = (char*) malloc(sizeof(char));
  if(concatenedString == NULL) crash();

  if(lastElemIndex > list->size -1){
    lastElemIndex = list->size - 1;
    fprintf(stderr, "fish : Warning : you are a miserable failure, your element is beyond the list. pfff. I corrected it for you.");
  }
  if(firstElemIndex > lastElemIndex){
    firstElemIndex = lastElemIndex;
    fprintf(stderr, "fish : Warning : how are you so bad ? your inferior index is superior to your superior index. pfff. I corrected it for you.");
  }

  WordListElement* tempElement = list->first;
  for(i=0; i < firstElemIndex; i++){

    tempElement = tempElement->next;

  }
  for(i=firstElemIndex; i < lastElemIndex; i++){

    trueStrcat(concatenedString, tempElement->word);
    tempElement = tempElement->next;

  }

  return concatenedString;

}

char* getFileName(char* string){

  if(!stringContains(string, '/')){
    return string;
  }
  else{
    int i = 0;
    while(string[i] != '/'){
      i++;
    }

    return strndup(string + i + 1, strlen(string) - i);
  }
}


//get path of a file
char* getPath(char* string){

  if(!stringContains(string, '/')){
    return string;
  }
  else{

    int i = strlen(string) - 1;

    while(i != -1 && string[i] != '/'){

      i = i-1;

    }

    return strndup(string, i + 1);

  }

}


WordList* getFiles(char* path, char* wildcardedString){

	DIR* directory;
	dirent* dir;

	WordList* files = createWordList();
  if(files == NULL) crash();


	if((directory = opendir(path)) != NULL){

		while((dir = readdir(directory)) != NULL){

			if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..") && wildcardedStringMatches(wildcardedString, dir->d_name)){//sorry strcmp but I dont like you :(

        char* filePath = trueStrcat(path, dir->d_name);
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
    int finished = 0; //boolean
    int firstEncounter = 0; //boolean
    WordList* newWordList = createWordList();
    if(newWordList == NULL) crash();

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
