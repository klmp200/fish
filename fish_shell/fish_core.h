//
// Created by Antoine Bartuccio on 11/05/2017.
//

#ifndef FISH_FISH_CORE_H
#define FISH_FISH_CORE_H


#include "fish_types.h"
#include "fish_commands.h"

/* WordArray functions */

WordArray * split(char *string, char *separator);
void freeWordArray(WordArray *array);

/* Settings functions */

Settings * getSettings();
void freeSettings(Settings *settings);


/* General purpose functions */

void fishLoop(Settings * settings);

char * fishReadLine();

int countSeparators(char *string, char *separators);

char * fishExpand(char* line);

int fishLoad(WordArray *array);

int fishExecute(WordArray *array);

#endif //FISH_FISH_CORE_H
