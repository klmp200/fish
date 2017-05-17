//
// Created by Antoine Bartuccio on 14/05/2017.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fish_core.h"
#include "fish_types.h"

/* Necessary global variables */
char * builtinCommandsStr[] = {
		(char *) "cd",
		(char *) "help",
		(char *) "exit"
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
	freeWordArray(args);
	return EXIT_SUCCESS;
}

int fishHelp(WordArray *args) {
	int i;
	printf("Bartuccio Antoine, Amalvy Arthur, Yann Chevanton\n");
	printf("Tape tes putains de noms de programmes et tes arguments de merde et tabasse ENTER !\n");
	printf("Les commandes suivantes sont internes :\n");
	for (i=0; i < getNbBuiltins(); i++){
		printf("\t%s\n", builtinCommandsStr[i]);
	}
	printf("Et sinon pour le reste, RTFM !");
	freeWordArray(args);
	return EXIT_SUCCESS;
}

int fishExit(WordArray *args) {
	freeWordArray(args);
	return EXIT_SIGNAL;

}

int getNbBuiltins() {
	return sizeof(builtinCommandsStr) / sizeof(char*);
}
