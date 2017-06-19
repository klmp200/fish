//
// Created by Antoine Bartuccio on 14/05/2017.
//

#ifndef FISH_FISH_COMMANDS_H
#define FISH_FISH_COMMANDS_H

#include "fish_core.h"

/* Getters */

/* Getter for global variable in external files */
char ** getBuiltinCommandsStr ();

/* Getter for global variable in external files */
builtinCommand **getBuiltinCommands();

/* Get size of the two global variable array */
int getNbBuiltins();

/* Built in shell commands */

/* Change Dir internal command */
int fishCd(WordArray * args);

/* Help internal command */
int fishHelp(WordArray * args);

/* Exit internal command */
int fishExit(WordArray * args);

/* Kek internal command */
int fishKek(WordArray *args);

/* Clear the terninal (internal command) */
int fishClear(WordArray *args);

/* Handle signal from the user (such as ctrl+c */
void fishSignalHandler(int s);

#endif //FISH_FISH_COMMANDS_H
