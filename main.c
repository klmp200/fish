#include <stdlib.h>
#include "fish_shell/fish_core.h"

int main() {
    /* todo load config file */
    fishLoop(getSettings());

    return EXIT_SUCCESS;
}
