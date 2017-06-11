//
// Created by Antoine Bartuccio on 14/05/2017.
//

#ifndef FISH_FISH_COMMANDS_H
#define FISH_FISH_COMMANDS_H

#include "fish_core.h"

/* Getters */

char ** getBuiltinCommandsStr ();
builtinCommand **getBuiltinCommands();
int getNbBuiltins();

/* Built in shell commands */

int fishCd(WordArray * args);

int fishHelp(WordArray * args);

int fishExit(WordArray * args);

int fishKek(WordArray *args);

int fishClear(WordArray *args);

void fishSignalHandler(int s);

#endif //FISH_FISH_COMMANDS_H
