//
// Created by Antoine Bartuccio on 16/05/2017.
//

#include "gtest/gtest.h"
#include "../fish_shell/fish_utils.h"
#include "../fish_shell/fish_types.h"

TEST(crash_test, crash){
	ASSERT_DEATH(crash(), "[A-z]+");
}

TEST(get_an_insult, getInsult){
	ASSERT_EQ(typeid(char*), typeid(getInsult()));
}

TEST(word_list_init, createWordList){
	WordList *list = createWordList();
	ASSERT_FALSE(list == NULL);
	ASSERT_TRUE(list->first == NULL);
	ASSERT_TRUE(list->last == NULL);
	ASSERT_TRUE(list->size == 0);
}

TEST(word_list_add, addWordList){
	WordList *list = createWordList();
	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addWordList(list, test1);
	ASSERT_TRUE(list->size == 1);
	ASSERT_TRUE(list->first != NULL);
	ASSERT_TRUE(list->last != NULL);
	ASSERT_TRUE(list->first == list->last);
	ASSERT_TRUE(list->first->word != NULL);
	ASSERT_FALSE(strcmp(list->first->word, test1));
	ASSERT_FALSE(list->first->word == test1);

	addWordList(list, test2);
	ASSERT_TRUE(list->size == 2);
	ASSERT_TRUE(list->first != list->last);
	ASSERT_FALSE(strcmp(list->last->word, test2));
	ASSERT_FALSE(strcmp(list->first->word, test1));
	ASSERT_TRUE(strcmp(list->first->word, test2));

	addWordList(list, test3);
	ASSERT_TRUE(list->size == 3);
	ASSERT_TRUE(list->first != list->last);
	ASSERT_FALSE(strcmp(list->first->word, test1));
	ASSERT_FALSE(strcmp(list->last->word, test3));
	ASSERT_TRUE(strcmp(list->last->word, test2));

	freeWordList(list);
}

TEST(word_list_remove, removeWordList){
	WordList *list = createWordList();
	char word[] = "lel";

	addWordList(list, word);
	addWordList(list, word);
	addWordList(list, word);

	ASSERT_TRUE(list->size == 3);

	removeWordList(list);

	ASSERT_TRUE(list->size == 2);

	removeWordList(list);

	ASSERT_TRUE(list->size == 1);

	freeWordList(list);

}

TEST(word_list_free, freeWordList){
	WordList *list = createWordList();
	char word[] = "lel";
	addWordList(list, word);
	addWordList(list, word);
	addWordList(list, word);

	freeWordList(list);

	list = createWordList();

	freeWordList(list);
}

TEST(word_list_to_word_array, wordListToWordArray){
	WordList *list = createWordList();
	WordListElement *elem = NULL;
	WordArray *array = NULL;
	int i = 0;

	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addWordList(list, test1);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test2);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test1);
	addWordList(list, test1);

	array = wordListToWordArray(list);
	ASSERT_FALSE(array == NULL);
	ASSERT_FALSE(array->words == NULL);

	list = createWordList();
	addWordList(list, test1);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test2);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test1);
	addWordList(list, test1);

	ASSERT_EQ(list->size, array->size);

	elem = list->first;

	for (i=0; i<array->size; i++){
		ASSERT_FALSE(strcmp(array->words[i], elem->word));
		elem = elem->next;
	}

	ASSERT_TRUE(array->words[array->size] == NULL);

	freeWordList(list);
	freeWordArray(array);
}

TEST(word_array_to_word_list, wordArrayToWordList){
	WordList *list = createWordList();
	WordList *list2 = NULL;
	WordListElement *elem = NULL;
	WordArray *array = NULL;
	int i = 0;

	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addWordList(list, test1);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test2);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test1);
	addWordList(list, test1);

	array = wordListToWordArray(list);
	list2 = wordArrayToWordList(array);

	list = createWordList();
	addWordList(list, test1);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test2);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test1);
	addWordList(list, test1);
	array = wordListToWordArray(list);

	ASSERT_TRUE(list2 != NULL);
	ASSERT_EQ(array->size, list2->size);

	elem = list2->first;

	for (i=0;i<array->size;i++){
		ASSERT_FALSE(strcmp(array->words[i], elem->word));
		elem = elem->next;
	}

	freeWordList(list2);
	freeWordArray(array);

}

TEST(word_array_free, freeWordArray){
	WordList *list = createWordList();
	WordArray *array = NULL;

	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addWordList(list, test1);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test2);
	addWordList(list, test2);
	addWordList(list, test3);
	addWordList(list, test1);
	addWordList(list, test1);

	array = wordListToWordArray(list);

	freeWordArray(array);
}