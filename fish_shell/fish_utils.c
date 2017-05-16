//
// Created by Antoine Bartuccio on 15/05/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
			(char *) "Bolos !",
			(char *) "Mois aussi je sais écrire de la merde, pourtant je le fait pas !"
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

void addWordList(WordList *list, char *word) {
	WordListElement *newElement = (WordListElement*) malloc(sizeof(WordListElement));
	if (newElement == NULL) crash();
	else {
		newElement->next = NULL;
		newElement->previous = list->last;
		if (list->size == 0){
			list->first = newElement;
			list->last = newElement;
		} else {
			list->last->next = newElement;
			list->last = newElement;
		}
		newElement->word = strdup(word);
		list->size++;
	}
}

void removeWordList(WordList *list) {
	WordListElement *current = list->last;
	if (current != NULL){
		list->last = current->previous;
		if (current->previous != NULL)
			current->previous->next = NULL;
		if (current->word != NULL)
			free(current->word);
		free(current);
		list->size--;
	}
}

void freeWordList(WordList *list) {
	while (list->size != 0)
		removeWordList(list);
	free(list);
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
			array->words[i] = current->word;
			current->word = NULL;
			current = current->next;
			i++;
		}
		array->words[i] = NULL;
	}

	freeWordList(list);

	return array;
}

WordList *wordArrayToWordList(WordArray *array) {
	WordList *list = createWordList();
	int i = 0;

	for (i=0; i<array->size; i++)
		addWordList(list, array->words[i]);

	freeWordArray(array);

	return list;
}
