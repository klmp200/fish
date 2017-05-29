#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "fish_settings.h"
#include "fish_core.h"

Settings *getSettings() {
	Settings *s = (Settings*) malloc(sizeof(Settings));
	if (s == NULL){
		crash();
	}

	uid_t uid;
	struct passwd *user;
	char* filename = NULL;
	uid = getuid();
	user = getpwuid(uid);

	filename = (char*) malloc(sizeof(char*)*(strlen(user->pw_dir) + FISH_RC_FILE_SIZE + 1));

	if (filename == NULL) crash();

	filename[0] = '\0';
	filename = strcat(filename, user->pw_dir);
	filename = strcat(filename, (char*) FISH_RC_FILE);
	s->passwd = user;
	s->PS1 = extractVariable(filename, (char*) "PS1");
	if (s->PS1 == NULL) s->PS1 = strdup("->");
	s->PS2 = extractVariable(filename, (char*) "PS2");
	if (s->PS2 == NULL) s->PS2 = strdup("->");

	free(filename);
	return s;
}

void freeSettings(Settings *settings){
	if (settings != NULL){
		settings->PS1[0] = '\0';
		settings->PS2[0] = '\0';
		free(settings->PS1);
		free(settings->PS2);
		free(settings);
	}
}

char* extractVariable(char* filename, char* var){
	FILE *file = fopen ( filename, "r" );
	int var_size = strlen(var);
	char *tmp = NULL;
	char line[FISH_BUFFER_SIZE];
	int i = 0;

	if ( file != NULL ){

		while ( fgets ( line, FISH_BUFFER_SIZE, file ) != NULL ) {

			if (!strncmp(line, var, var_size)) {

				tmp = (char*) malloc(sizeof(char*)* (strlen(line)-var_size));
				if (tmp == NULL) crash();

				i = var_size + 1;
				while(line[i] != '\n' && line[i] != '\0'){
					tmp[i-var_size-1] = line[i];
					i++;
				}
				tmp[i-var_size-1]='\0';
			}
		}

		fclose(file);
		return tmp;
	}
	else {
		perror ( filename ); /* why didn't the file open? */
	}
	return tmp;
}


