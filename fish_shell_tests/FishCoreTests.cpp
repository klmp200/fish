//
// Created by Antoine Bartuccio on 15/05/2017.
//

#include "FishCoreTests.h"
#include "../fish_shell/fish_core.c"
#include "../fish_shell/fish_utils.c"
#include "../fish_shell/fish_commands.c"
#include "../fish_shell/fish_globbing.c"


//TEST_F(FishCoreTests, split){
//	ASSERT_TRUE(true);
//}

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
