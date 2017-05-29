#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "fish_core.h"

Settings *getSettings() {
	Settings *s = (Settings*) malloc(sizeof(Settings));
	if (s == NULL){
		crash();
	}

	uid_t uid;
	struct passwd *user;
	char* file = (char*)malloc(sizeof(char*)*50);
	uid = getuid();
	user = getpwuid(uid);

	file = "\0";
	file = strcat(user->pw_dir, "/.fishrc");
	s->user1 = user;
	s->PS1 = extractVariable(file, "PS1");
	s->PS2 = extractVariable(file,"PS2");
	return s;
}

// char* convertPS(char* s){
// 	if(s != NULL){
// 		printf("Quelque chose à convertir\n");
// 		int i=0;
// 		char* PS = (char*) malloc(sizeof(char*)* 20);
// 		PS[0] = '\0';
// 		while(s[i] != '\0'){
// 			if(s[i]=='\\'){
// 			 	i++;
// 			 	 switch (s[i]){
// 			 	 case '\\' : PS[i-1] = '\\';
// 			 	 case 'u' : PS[i-1] = '?';
// 			 	 default : PS[i] = s[i];
					
// 			 	}
// 			 	i++;
// 			 }else{
// 				PS[i] = s[i];
// 				i++;
				
// 			}
// 		printf("Prompt %i: %s ! %s traiter: %c donne: %c \n",i,PS, s, s[i-1], PS[i-1] );
			
// 		}
// 		return PS;
// 		PS = NULL;
// 		free(PS);
// 	}else{
// 		printf("Void argument, try again Ame\n");
// 		return strdup(">");
// 	}
// }

void freeSettings(Settings *settings){
	if (settings != NULL){
		free(settings->PS1);
		free(settings->PS2);
		free(settings);
	}
}

char* extractVariable(char* filename, char* var){
	FILE *file = fopen ( filename, "r" );
   if ( file != NULL )
   {
      char line [ 128 ]; /* or other suitable maximum line size */
 
		while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
		{
		 	printf("Ligne : %s", line); /* write the line */
			if (strncmp(line, var, strlen(var)-1) == 0)
			{
				int i=0;
				char* tmp = (char*) malloc(sizeof(char*)* (strlen(line)-strlen(var)));
				//tmp = "\0";
				while(var[i] != '\0')
				{
					i++;
				}
				i= i+1;
				while(line[i] != '\n' && line[i] != '\0')
				{
					printf("ici: %s\n", tmp);
					tmp[i-strlen(var)-1] = line[i];
					i++;
				}
				tmp[i-strlen(var)-1]='\0';
				printf("Result: %s\n",tmp);
				return tmp;
				free(tmp);
		    }
		}
      fclose ( file );
      printf("Variable doesn't exit\n");
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
   }
   return NULL;
}


