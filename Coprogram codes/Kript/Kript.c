#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const char key[9] = "axer13gu"; 



void Criptograph(const char* text)
{
	FILE *file = fopen("Cripted","w");
	if(file == NULL)
	{
		fprintf(stdout,"\033[0;31mError Opening File\033[0m");
		return ;
	} 
	size_t index = 0;
	size_t keyindex = 0;
	for(; index < strlen(text); ++index,++keyindex)
	{
		if(keyindex > 7)
			keyindex = 0;

		unsigned int criph = (text[index]*key[keyindex]);

		fprintf(file,"%i",criph);
		if(text[index+1]!='\0')
			fprintf(file, " ");
		
	}
	fclose(file);
}

void UncriptFile(const char* fileName)
{
	FILE *file = fopen(fileName,"r");
	if(file == NULL)
	{
		fprintf(stdout, "\033[0;31mError opening file!\033[0m"); return;
	}
	size_t keyindex = 0;
	fprintf(stdout,"O arquivo contem o seguinte texto:\n");
	while(!feof(file))
	{	
		if(keyindex > 7)
			keyindex = 0;
		unsigned int buffer_int;
		fscanf(file,"%i",&buffer_int);
	
		fprintf(stdout, "%c",(buffer_int/key[keyindex]));
		keyindex++;
	}
	fclose(file);
	fprintf(stdout, "\n\n\n\n");
}




int Menu()
{
	system("clear");
	char choice = 0;
	fprintf(stdout,"Bem-Vindo ao Kript, escolha uma opcao:\n");
	fprintf(stdout, "(1) Criptografar texto.\n(2) Descriptografar Arquivo.\nOpcao..:");
	fscanf(stdin,"%c",&choice);
	int x = atoi(&choice);
	if(x < 1 || x > 2)
	{
		Menu();
		return 0;
	}
	char buffer[128];
	switch(x)
	{
		case 1:
			
			fscanf(stdin,"%s[\n]",&buffer);
			Criptograph(buffer); 
			break;

		case 2:
			fprintf(stdout, "\n\n\033[0;34mInforme o nome do arquivo: \033[0m");
			fscanf(stdin,"%s",&buffer);
			UncriptFile(buffer);
			break;
	}
}




int main()
{

	Menu();
	


}
