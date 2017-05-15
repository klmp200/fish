//
// Created by Antoine Bartuccio on 15/05/2017.
//

#include <stdio.h>
#include <stdlib.h>

void crash(){
	fprintf(stderr, "fish: Error allocating fucking pointer !");
	exit(EXIT_FAILURE);
}
