//
// Created by Antoine Bartuccio on 15/05/2017.
//

#include "gtest/gtest.h"
#include "../fish_shell/fish_types.h"
#include "../fish_shell/fish_core.h"

TEST(command_split, split){
	char input[] = "git push --force";
	char *output[] = {
			(char *) "git",
			(char *) "push",
			(char *) "--force"
	};
	WordList *list = split(input, (char *) FISH_TOKENS);
	WordListElement *current = list->first;
	int i = 0;

	ASSERT_FALSE(current == NULL);
	while(current != NULL){
		ASSERT_STREQ(current->word, output[i]);
		current = current->next;
		i++;
	}

	freeWordList(list);

}

TEST(count_tokens, countSeparators){
	ASSERT_TRUE(countSeparators((char*) "Ceci est un super \n test", (char*) " ") == 5);
	ASSERT_TRUE(countSeparators((char*) "patate | patate| patatine", (char*) "\\|") == 2);
	ASSERT_TRUE(countSeparators((char*) "patate | patate| patatine |", (char*) "\\|") == 3);
	ASSERT_TRUE(countSeparators((char*) "patate | patate|| patatine |", (char*) "\\|[^\\|]") == 2);
}
