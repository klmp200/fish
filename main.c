#include <stdlib.h>
#include "fish_shell/fish_core.h"
#include "fish_shell/fish_types.h"

int main() {
	/* todo load config file */
	Settings *s = getSettings();
	fishLoop(s);
	freeSettings(s);

	return EXIT_SUCCESS;
}
