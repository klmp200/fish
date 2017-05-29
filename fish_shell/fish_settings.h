#ifndef FISH_FISH_SETTINGS_H
#define FISH_FISH_SETTINGS_H

#include "fish_core.h"

#define FISH_RC_FILE "/.fishrc"
#define FISH_RC_FILE_SIZE 8

Settings * getSettings(); //TESTEDssssss
void freeSettings(Settings *settings); //TESTED
char* extractVariable(char* filename, char* var);//TESTED

#endif //FISH_FISH_SETTINGS_H