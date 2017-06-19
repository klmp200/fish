#ifndef FISH_FISH_SETTINGS_H
#define FISH_FISH_SETTINGS_H

#include "fish_core.h"

#define FISH_RC_FILE "/.fishrc"
#define FISH_RC_FILE_SIZE 8

/* Get settings */
Settings * getSettings(); //TESTEDssssss

/* Free settings */
void freeSettings(Settings *settings); //TESTED

/* Extract a given variable from a given file */
char* extractVariable(char* filename, char* var);//TESTED

/* Correctly print PS1 and PS2 variable */
void printPS(char* PS, Settings* s);

#endif //FISH_FISH_SETTINGS_H

