#include <stdlib.h>
#include "fish_lib/fish_lib.h"

int main() {
    /* todo load config file */
    fishLoop(getSettings());

    return EXIT_SUCCESS;
}
