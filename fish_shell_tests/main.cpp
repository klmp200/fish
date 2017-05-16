//
// Created by Antoine Bartuccio on 15/05/2017.
//

#include "gtest/gtest.h"
#include "../fish_shell/fish_core.c"
#include "../fish_shell/fish_utils.c"
#include "../fish_shell/fish_commands.c"
#include "../fish_shell/fish_globbing.c"

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
