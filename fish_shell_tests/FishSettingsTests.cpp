#include "gtest/gtest.h"
#include "../fish_shell/fish_types.h"
#include "../fish_shell/fish_settings.h"

TEST(free_settings_Test, freeSettings){
	Settings *s = getSettings();

	ASSERT_STREQ(s->PS1, "->");

	freeSettings(s);

	ASSERT_STRNE(s->PS1, "->");
}

TEST(extract_variable_Test, extractVariable){
	ASSERT_TRUE(extractVariable((char*) "P4T3", (char*) "PS1") == NULL);
	ASSERT_STREQ(extractVariable((char*) "../fish_shell_tests/fishrc", (char*) "PS1"), "sli->");
	ASSERT_TRUE(extractVariable((char*) "../fish_shell_tests/fishrc", (char*) "P1ZZ4") == NULL);

}

TEST(get_settings_Test, getSettings){
	Settings* s = getSettings();
	ASSERT_FALSE(s ==NULL);
	ASSERT_FALSE(s->passwd == NULL);
	freeSettings(s);
}
