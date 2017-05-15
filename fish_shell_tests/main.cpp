//
// Created by Antoine Bartuccio on 15/05/2017.
//



#include <gtest/gtest.h>

int main(int argc, char **argv){

	printf("Je mange des patates");
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();

	return ret;
}
