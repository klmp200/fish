//
// Created by Antoine Bartuccio on 16/05/2017.
//

#include "gtest/gtest.h"
#include "../fish_shell/fish_utils.h"
#include "../fish_shell/fish_types.h"

TEST(crash_crash_Test, crash){
	ASSERT_DEATH(crash(), "[A-z]+");
}

TEST(get_getInsult_Test, getInsult){
	ASSERT_EQ(typeid(char*), typeid(getInsult()));
}

TEST(create_createWordList_Test, createWordList){
	WordList *list = createWordList();
	ASSERT_FALSE(list == NULL);
	ASSERT_TRUE(list->first == NULL);
	ASSERT_TRUE(list->last == NULL);
	ASSERT_TRUE(list->size == 0);
}

TEST(add_addBegin__Test, addBeginWordList){
	WordList *list = createWordList();
	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addBeginWordList(list, test1);
	ASSERT_EQ(list->size, 1);
	ASSERT_FALSE(list->first == NULL);
	ASSERT_FALSE(list->last == NULL);
	ASSERT_EQ(list->first, list->last);
	ASSERT_FALSE(list->first->word == NULL);
	ASSERT_STREQ(list->first->word, test1);
	ASSERT_FALSE(list->first->word == test1);

	addBeginWordList(list, test2);
	ASSERT_EQ(list->size, 2);
	ASSERT_FALSE(list->first == list->last);
	ASSERT_STREQ(list->first->word, test2);
	ASSERT_STREQ(list->last->word, test1);
	ASSERT_STRNE(list->first->word, test1);

	addBeginWordList(list, test3);
	ASSERT_EQ(list->size, 3);
	ASSERT_FALSE(list->first == list->last);
	ASSERT_STREQ(list->last->word, test1);
	ASSERT_STREQ(list->first->next->word, test2);
	ASSERT_STREQ(list->first->word, test3);

	freeWordList(list);

}

TEST(add_addEndWordList_Test, addEndWordList){
	WordList *list = createWordList();
	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addEndWordList(list, test1);
	ASSERT_TRUE(list->size == 1);
	ASSERT_TRUE(list->first != NULL);
	ASSERT_TRUE(list->last != NULL);
	ASSERT_TRUE(list->first == list->last);
	ASSERT_TRUE(list->first->word != NULL);
	ASSERT_FALSE(strcmp(list->first->word, test1));
	ASSERT_FALSE(list->first->word == test1);

	addEndWordList(list, test2);
	ASSERT_TRUE(list->size == 2);
	ASSERT_TRUE(list->first != list->last);
	ASSERT_FALSE(strcmp(list->last->word, test2));
	ASSERT_FALSE(strcmp(list->first->word, test1));
	ASSERT_TRUE(strcmp(list->first->word, test2));

	addEndWordList(list, test3);
	ASSERT_TRUE(list->size == 3);
	ASSERT_TRUE(list->first != list->last);
	ASSERT_FALSE(strcmp(list->first->word, test1));
	ASSERT_FALSE(strcmp(list->last->word, test3));
	ASSERT_TRUE(strcmp(list->last->word, test2));

	freeWordList(list);
}

TEST(remove_removeWordList_Test, removeWordList){
	WordList *list = createWordList();
	char word[] = "lel";

	addEndWordList(list, word);
	addEndWordList(list, word);
	addEndWordList(list, word);

	ASSERT_TRUE(list->size == 3);

	removeWordList(list);

	ASSERT_TRUE(list->size == 2);

	removeWordList(list);

	ASSERT_TRUE(list->size == 1);

	freeWordList(list);

}

TEST(free_freeWordList_Test, freeWordList){
	WordList *list = createWordList();
	char word[] = "lel";
	addEndWordList(list, word);
	addEndWordList(list, word);
	addEndWordList(list, word);

	freeWordList(list);

	list = createWordList();

	freeWordList(list);
}

TEST(word_wordListToWordArray_Test, wordListToWordArray){
	WordList *list = createWordList();
	WordListElement *elem = NULL;
	WordArray *array = NULL;
	int i = 0;

	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addEndWordList(list, test1);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test2);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test1);
	addEndWordList(list, test1);

	array = wordListToWordArray(list);
	ASSERT_FALSE(array == NULL);
	ASSERT_FALSE(array->words == NULL);

	list = createWordList();
	addEndWordList(list, test1);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test2);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test1);
	addEndWordList(list, test1);

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

TEST(word_wordArrayToWordList_Test, wordArrayToWordList){
	WordList *list = createWordList();
	WordList *list2 = NULL;
	WordListElement *elem = NULL;
	WordArray *array = NULL;
	int i = 0;

	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addEndWordList(list, test1);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test2);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test1);
	addEndWordList(list, test1);

	array = wordListToWordArray(list);
	list2 = wordArrayToWordList(array);

	list = createWordList();
	addEndWordList(list, test1);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test2);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test1);
	addEndWordList(list, test1);
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

TEST(free_freeWordArray_Test, freeWordArray){
	WordList *list = createWordList();
	WordArray *array = NULL;

	char test1[] = "Test1";
	char test2[] = "Test2";
	char test3[] = "Test3";

	addEndWordList(list, test1);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test2);
	addEndWordList(list, test2);
	addEndWordList(list, test3);
	addEndWordList(list, test1);
	addEndWordList(list, test1);

	array = wordListToWordArray(list);

	freeWordArray(array);
}

TEST(split_splitWord__Test, slpitWord){
	char test1[] = "ls&&ls";
	char test2[] = "&&";
	char *splited = splitWord(test1, 2, 2);

	ASSERT_STREQ(test1, "ls");
	ASSERT_STREQ(splited, "ls");

	free(splited);

	splited = splitWord(test2, 0, 2);

	ASSERT_STREQ(test2, "");
	ASSERT_STREQ(splited, "");

	free(splited);
}