//
// Created by Antoine Bartuccio on 15/05/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pcre.h>
#include <dirent.h>
#include <errno.h>
#include "fish_utils.h"
#include "fish_types.h"

void crash(){
	char *crashErrors[] = {
			(char *) "fish: Fucking malloc always returning NULL pointer !",
			(char *) "fish: Error allocating fucking pointer !",
			(char *) "fish: C language exploding again",
			(char *) "fish: It's not you're fault for this time"
	};
	int picked = 0;

	srand((unsigned int) time(NULL));
	picked = rand() % (sizeof(crashErrors) / sizeof(char*));

	fprintf(stderr, "%s\n", crashErrors[picked]);
	exit(EXIT_FAILURE);
}

char *getInsult(){
	static int init = 0;
	int picked = 0;
	char *insults[] = {
			(char *) "Apprend à écrire crétin !",
			(char *) "Boloss !",
			(char *) "Mois aussi je sais écrire de la merde, pourtant je le fait pas !",
			(char *) "Oh ! Une erreur ! Comme ta vie en fait...",
			(char *) "Nul !",
			(char *) "Pense à aller à l'école un jour",
			(char *) "Et après on dit que c'est la faute de l'ordinateur..."
	};
	if (!init){
		srand((unsigned int) time(NULL));
		init = 1;
	}

	picked = rand() % (sizeof(insults) / sizeof(char*));
	return insults[picked];
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


WordList *createWordList() {
	WordList *list = (WordList*) malloc(sizeof(WordList));
	if (list == NULL) crash();
	else {
		list->size = 0;
		list->first = NULL;
		list->last = NULL;
	}

	return list;
}

void addEndWordList(WordList *list, char *word) {
	WordListElement *new_element = (WordListElement*) malloc(sizeof(WordListElement));
	if (new_element == NULL) crash();
	else {
		new_element->next = NULL;
		new_element->previous = list->last;
		if (list->size == 0){
			list->first = new_element;
			list->last = new_element;
		} else {
			list->last->next = new_element;
			list->last = new_element;
		}
		new_element->word = strdup(word);
		list->size++;
	}
}

void addBeginWordList(WordList *list, char *word) {
	WordListElement *new_element = (WordListElement*) malloc(sizeof(WordListElement));
	if (new_element == NULL) crash();
	else {
		new_element->next = list->first;
		new_element->previous = NULL;
		if (list->size == 0){
			list->first = new_element;
			list->last = new_element;
		} else {
			list->first->previous = new_element;
			list->first = new_element;
		}
		new_element->word = strdup(word);
		list->size++;
	}
}

void removeWordList(WordList *list) {
	if (list != NULL) removeWordListElem(list, list->last);
}

void freeWordList(WordList *list) {
	while (list != NULL && list->size != 0)
		removeWordList(list);
	free(list);
}

void concatWordList(WordList* list1, WordList* list2){//return a single list containing all elements of both lists

  if(list1 == NULL || list2 == NULL){
    crash();
  }
  else if(list2->size != 0){

    WordListElement* tempElement = list2->first;

    for(int i = 0; i < list2->size; i++){

      addEndWordList(list1, tempElement->word);
      tempElement = tempElement->next;

    }

    freeWordList(list2);

  }
  else{
    freeWordList(list2);
  }

}

WordArray *wordListToWordArray(WordList *list) {
	WordArray *array = (WordArray*) malloc(sizeof(WordArray));
	WordListElement *current = list->first;
	int i = 0;

	if (array == NULL) crash();
	else {
		array->size = list->size;
		array->words = (char **) malloc(sizeof(char *) * (list->size + 1));
		if (array->words == NULL) crash();

		while (current != NULL){
			array->words[i] = strdup(current->word);
			current = current->next;
			i++;
		}
		array->words[array->size] = NULL;
	}

	freeWordList(list);

	return array;
}

WordList *wordArrayToWordList(WordArray *array) {
	WordList *list = createWordList();
	int i;

	for (i=0; i<array->size; i++)
		addEndWordList(list, array->words[i]);

	freeWordArray(array);

	return list;
}

void removeWordListElem(WordList *list, WordListElement *elem) {
	if (list != NULL && elem != NULL){

		if (list->first == elem && list->last == elem){
			list->first = NULL;
			list->last = NULL;

		} else if (list->first == elem){
			list->first = elem->next;
			elem->previous = NULL;

		} else if (list->last == elem){
			list->last = elem->previous;
			elem->previous->next = NULL;

		} else {
			elem->next->previous = elem->previous;
			elem->previous->next = elem->next;
		}

		list->size--;

		if (elem->word != NULL)
			free(elem->word);

		free(elem);
	}
}

WordList *sliceWordList(WordList *list, int min_index, int max_index) {
	WordList *newList = createWordList();
	WordListElement *elem = NULL;
	WordListElement *tmp = NULL;
	int i=0;

	if (list == NULL || min_index > list->size || max_index > list->size) return newList;
	else {
		elem = list->first;
		while (i < max_index){

			tmp = elem->next;
			if (i >= min_index){
				addEndWordList(newList, elem->word);
				removeWordListElem(list, elem);
			}

			elem = tmp;

			i++;
		}
	}
	return newList;
}

char * splitWord(char * origin, int beginning_index, int size_to_delete){
	char * new_word = strdup(origin + beginning_index + size_to_delete);

	if (new_word == NULL) crash();
	else {
		origin[beginning_index] = '\0';
	}

	return new_word;
}

WordList *splitWordList(WordList *list, char *regex) {
	const char* error;
	int error_offset;
	int ovector[100];
	int i = 0;
	int rc;
	WordList * new_list = NULL;
	WordListElement * current = list->first;
	pcre *re = pcre_compile(regex, 0, &error, &error_offset, 0);
	char *tmp_word = NULL;

	if (!re) crash();

	while (current != NULL){
		rc = pcre_exec(re,
					   0,
					   current->word,
					   (int) strlen(current->word),
					   0,
					   0,
					   ovector,
					   sizeof(ovector)
		);

		if(rc >= 0){
			new_list = sliceWordList(list, i + 1, list->size);
			tmp_word = splitWord(current->word, ovector[0], ovector[1] - ovector[0]);

			if (tmp_word[0] != '\0') addBeginWordList(new_list, tmp_word);
			if (current->word[0] != '\0') addEndWordList(list, current->word);

			removeWordListElem(list, current);
			current = NULL;
			free(tmp_word);
		}

		else current = current->next;
		i++;
	}

	pcre_free(re);

	return new_list;
}

//for debugging purposes
void printWordList(WordList* list){


  if(list != NULL){

    printf("--- list ---\n");
    printf("size : %i\n", list->size);

    int i = 0;
    WordListElement* tempElement = list->first;

    for(i=0; i<list->size; i++){

      printf("element %i : %s\n",i, tempElement->word);
      tempElement = tempElement->next;

    }

    printf("--- end ---\n");

  }
  else{
    fprintf(stderr, "fish : Warning : list is null. Are you stupid ?\n");
  }

}

int stringContains(char * string, char charToTest){

	int i = 0;

	while(string[i] != '\0'){

		if(string[i] == charToTest){
			return 1;
		}
		i++;
	}

	return 0;

}

//dont read this, and if you do, do not complain, it's strcat's fault. you've been warned.
char* trueStrcat(char* string1, char* string2){

  char* newString = (char*) malloc(sizeof(char) * (strlen(string1) + strlen(string2)) + 1);
  if(newString == NULL) crash();
  newString[0] = '\0';
  strcat(newString, string1);
  strcat(newString, string2);
  return newString;

}

int isDirectory(char* path){

  DIR* directory = opendir(path);

  //printf("testing %s\n", path);

  if(directory != NULL){
    closedir(directory);
    return 1;
  }
  else if(errno == ENOTDIR){
    return 0;
  }
  else{
    fprintf(stderr, "fish : Warning : %s is an invalid path you stupid human\n", path);
    return 0; //hihi
  }
}
