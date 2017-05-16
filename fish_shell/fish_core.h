//
// Created by Antoine Bartuccio on 11/05/2017.
//

#ifndef FISH_FISH_CORE_H
#define FISH_FISH_CORE_H

#define FISH_BUFFER_SIZE 1024
#define FISH_TOKENS " \t\r\n\a"



#include "fish_types.h"
#include "fish_commands.h"
#include "fish_utils.h"

/* WordArray functions */

WordList * split(char *string, char *separator); // Tested

/* Settings functions */

Settings * getSettings();
void freeSettings(Settings *settings);


/* General purpose functions */

void fishLoop(Settings * settings);

char * fishReadLine();

int countSeparators(char *string, char *separators); // Tested

int fishLoad(WordArray *array);

int fishExecute(WordList *list);

WordList *parseWordList(WordList *list, shell_operator *an_operator);

int loadRightCommand(WordArray *array);

#endif //FISH_FISH_CORE_H
