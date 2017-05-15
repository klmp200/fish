//
// Created by Antoine Bartuccio on 15/05/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fish_types.h"

void crash(){
	fprintf(stderr, "fish: Error allocating fucking pointer !");
	exit(EXIT_FAILURE);
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
	WordListElement *new = (WordListElement*) malloc(sizeof(WordListElement));
	if (new == NULL) crash();
	else {
		new->next = NULL;
		new->previous = list->last;
		if (list->size == 0){
			list->first = new;
			list->last = new;
		} else {
			list->last->next = new;
			list->last = new;
		}
		new->word = strdup(word);
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
