#include "fish_core.h"

Settings * getSettings();
//char* convertPS(char* );
void freeSettings(Settings *settings);
char* extractVariable(char* filename, char* var);