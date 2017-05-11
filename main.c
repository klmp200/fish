#include <stdio.h>
#include <stdlib.h>
#include "fish_lib/fish_lib.h"

int main() {
    /* todo load config file */

    split("I love eating bananas", " ");
    fishLoop();

    return EXIT_SUCCESS;
}