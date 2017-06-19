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

/* Main loop of the project */
void fishLoop(Settings * settings);

/* Get the user input */
char * fishReadLine();

/* Count the number of occurrences of a given regex pattern */
int countSeparators(char *string, char *regex); // Tested

/* Execute an external command */
int fishLoad(WordArray *array);

/* Handle operators in the user input */
int fishExecute(WordList *list);

/* Cut a WordList at the given operator regex pattern */
WordList *parseWordList(WordList *list, shell_operator *an_operator);

/* Choose between internal and external command */
int loadRightCommand(WordArray *array);

/* IN/OUT functions */

/* Get a global pipe_redirection structure */
pipe_redirection * getRedirection();

/* Free redirection structure DO NOT TRY TO GET REDIRECTION AFTER */
void freeRedirection();

#endif //FISH_FISH_CORE_H
