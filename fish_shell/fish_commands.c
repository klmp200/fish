//
// Created by Antoine Bartuccio on 14/05/2017.
//
#include <stdio.h>
#include <unistd.h>
#include "fish_core.h"

/* Necessary global variables */
char * builtinCommandsStr[] = {
		"cd",
		"help",
		"exit"
};


builtinCommand *builtinCommands[] = {
		&fishCd,
		&fishHelp,
		&fishExit
};

char ** getBuiltinCommandsStr(){
	return builtinCommandsStr;
}

builtinCommand **getBuiltinCommands(){
	return builtinCommands;
}

int fishCd(WordArray *args) {
	if (args->size < 2){
		fprintf(stderr, "fish: Où sont les arguments de ta commande \"cd\" connard ?!\n");
	} else {
		if (chdir(args->words[1]) != 0){
			perror("fish");
		}
	}
	return 1;
}

int fishHelp(WordArray *args) {
	int i;
	printf("Bartuccio Antoine, Amalvy Arthur, Yann Chevanton\n");
	printf("Tape tes putains de noms de programmes et tes arguments de merde et tabasse ENTER !\n");
	printf("Les commandes suivantes sont internes :\nls");
	for (i=0; i < getNbBuiltins(); i++){
		printf("\t%s\n", builtinCommandsStr[i]);
	}
	printf("Et sinon pour le reste, RTFM !");
	if (args->size > 0)
		return 1;
	return 1;
}

int fishExit(WordArray *args) {
	if (args->size != 1)
		return 1;
	else
		return 0;
}

int getNbBuiltins() {
	return sizeof(builtinCommandsStr) / sizeof(char*);
}
