#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>






int main(int argc, char *argv[])
{
	

	const char *homedir = getpwuid(getuid())->pw_dir;//.pw_dir;//pw->pw_dir;
	if(argc == 1)
	{
		fprintf(stdout,"de um comando: %s <session>\n\n",argv[0]);
		return 0;
	}
	const char *xinitrc = "/.xinitrc";
	char *home = (char*)malloc(sizeof(char)*(strlen(homedir)+strlen(xinitrc))+1);
	strcpy(home,homedir);
	strcat(home,xinitrc);


	FILE *file = fopen(home,"w");
	if(file == NULL)
	{
		fprintf(stdout,"\033[0;31m Error Creating File .xinitrc\033[0m\n\n");
		return 1;
	
	}
	int i = 0;
	for(i = 1; i <=argc;++i)
	{
		if(argv[i] != NULL)
			fprintf(file, "%s ", argv[i]);
	}
	

	fclose(file);
	
	system("startx");


	
	return 0;
}




