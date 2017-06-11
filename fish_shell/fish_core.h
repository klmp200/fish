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
#include "fish_settings.h"

/* WordArray functions */

WordList * split(char *string, char *separator); // Tested



/* General purpose functions */

void fishLoop(Settings * settings);

char * fishReadLine();

int countSeparators(char *string, char *regex); // Tested

int fishLoad(WordArray *array);

int fishExecute(WordList *list);

WordList *parseWordList(WordList *list, shell_operator *an_operator);

int loadRightCommand(WordArray *array);

/* IN/OUT functions */

/* Get a global pipe_redirection structure */
pipe_redirection * getRedirection();

/* Free redirection structure DO NOT TRY TO GET REDIRECTION AFTER */
void freeRedirection();

#endif //FISH_FISH_CORE_H
