#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "Reading_Words_From_File.h"


bool stricmp(const char * p1, const char * p2)
{
	bool equal = true;
	while(*p1 != '\0' && *p2 != '\0')
	{
		if(tolower(*p1) != tolower(*p2))
			equal = false;

		p1++;p2++;
	}

	return equal;
}


typedef struct Palavras
{
	char *chosenWord;
	char *chosenHint;
	char *hiddenWord;
	char *digitadas;
	int erros;

}Palavras;

void Print_Hidden_Word(const char *hiddenWord)
{
	while(*hiddenWord != '\0')
	{
		fprintf(stdout,"%c ",*hiddenWord);
		hiddenWord++;
	}
}

void InitializePalavras(Palavras *const palavras,const char *const fileName)
{
	Struct_Forca_Word *Forca_Word = Read_Words_From_File(fileName);
	srand(time(NULL));
	size_t random = (0 + rand()%(Forca_Word[0].my_arr_size - 0));

	palavras->chosenWord = (char *)malloc(sizeof(char)*(strlen(Forca_Word[random].word)+1));
	palavras->hiddenWord = (char *)malloc(sizeof(char)*(strlen(Forca_Word[random].word)+1));
	strcpy(palavras->chosenWord,Forca_Word[random].word);
	size_t aux = 0;
	for(; aux < strlen(Forca_Word[random].word); ++aux)
	{
		palavras->hiddenWord[aux] = (palavras->chosenWord[aux] == 32) ? 32 : '_';
	}
	palavras->hiddenWord[aux] = '\0';
	
	if(Forca_Word[random].hint != NULL)
	{
		palavras->chosenHint = (char *)malloc(sizeof(char)*(strlen(Forca_Word[random].hint)+1));
		strcpy(palavras->chosenHint,Forca_Word[random].hint);
	}
	else
	{
		palavras->chosenHint = (char *)malloc(sizeof(char)*10);
		strcpy(palavras->chosenHint,"Sem Dica!\0");
	
	}

	palavras->erros = 0;

	palavras->digitadas = (char *)malloc(sizeof(char)*60);
	for(aux = 0; aux < 60; ++aux)
	{
		palavras->digitadas[aux] = -1;
	
	}


	free(Forca_Word);
	


}


void Compare_Guess(Palavras *const palavras,char guess)
{
	size_t index = 0;
	bool errou = true;
	for(; palavras->chosenWord[index]!= '\0'; ++index)
	{
		if(tolower(palavras->chosenWord[index]) == tolower(guess))
		{
			palavras->hiddenWord[index] = (tolower(palavras->chosenWord[index]) == palavras->chosenWord[index]) ? tolower(guess) : toupper(guess);
			errou = false;
		}
	}

	if(errou)
	{
		palavras->erros++;
	}
	size_t aux = 0;
	for(;aux < strlen(palavras->digitadas);++aux)
	{
		if(palavras->digitadas[aux] == -1)
		{
			palavras->digitadas[aux] = guess;
			break;
		}
	}
	

}
void Print_Digitadas(const char* const digitadas)
{
	size_t i = 0;
	for(; digitadas[i] != -1;++i)
	{
		if(digitadas[i] != -1)
			fprintf(stdout,"%c, ",digitadas[i]);
		
	}
	fprintf(stdout, "\n");
}






typedef struct Forca
{	
	char corpo[7];

}Forca;

void InitializeForca(Forca *const forca)
{
	strcpy(forca->corpo,"      \0");
}
void Print_Forca(Forca *const forca, int erros)
{
	switch(erros)
	{
		case 1:
		forca->corpo[0] = '0';  break;
		case 2:
		forca->corpo[1] = '/';  break;
		case 3:
		forca->corpo[2] = '|';  break;
		case 4:
		forca->corpo[3] = '\\'; break;
		case 5:
		forca->corpo[4] = '/';  break;
		case 6:
		forca->corpo[5] = '\\'; break;
	}

	fprintf(stdout," ______\n");
	fprintf(stdout,"|    %c\n",forca->corpo[0]);
	fprintf(stdout,"|   %c%c%c\n",forca->corpo[1],forca->corpo[2],forca->corpo[3]);
	fprintf(stdout,"|   %c %c\n",forca->corpo[4],forca->corpo[5]);
	fprintf(stdout,"|\n");
	fprintf(stdout,"|\n\n");
}



void Game_Loop(const char *const fileName)
{
	Palavras palavras;    InitializePalavras(&palavras,fileName);
	Forca forca;		  InitializeForca(&forca);
	fprintf(stdout,"jogo teste...\n\n");
	char guess = 0;
	while(stricmp(palavras.chosenWord,palavras.hiddenWord) == false && palavras.erros < 6)
	{
		system("clear");
		fprintf(stdout,"\t********** Jogo Da Forca ***********\n\n");
		fprintf(stdout,"Dica: %s\n",palavras.chosenHint);
		Print_Forca(&forca,palavras.erros);
		fprintf(stdout,"Letras Digitadas: ");Print_Digitadas(palavras.digitadas);
		Print_Hidden_Word(palavras.hiddenWord);
		fscanf(stdin,"%c%*c",&guess); __fpurge(stdin);
		Compare_Guess(&palavras,guess);
	}
	system("clear");
	fprintf(stdout,"\t********** Jogo Da Forca ***********\n\n");
	fprintf(stdout,"Dica: %s\n",palavras.chosenHint);
	Print_Forca(&forca,palavras.erros);
	Print_Hidden_Word(palavras.hiddenWord);
	fprintf(stdout,"\n\t** %s %s! **\n",(palavras.erros < 6)? "Parabens voce acertou! a palavra era mesmo" : "Desculpe mas voce morreu. A palavra era",palavras.chosenWord);


}







const char *TreatArgument(int argc, char **argv);


// MAIN FUNCTION

int main(int argc,char **argv)
{
	if(argc < 2) // se nao ah argumento
	{
		fprintf(stdout,"\033[0;31mPasse o nome do arquivo das palavras como argumento\033[0m\n\033[0;32mExemplo: %s \"arquivo\" (sem aspas)\033[0m\n",argv[0]);
		exit(0);
	}

	const char *const fileName = TreatArgument(argc,argv);

	bool play = true;
	do
	{
		char input = 0;
		
		Game_Loop(fileName);
		fprintf(stdout,"\nContinuar Jogando? [S/n]: ");
		fscanf(stdin,"%c",&input); __fpurge(stdin);
		play = (tolower(input) == 's') ? true : false;

	}while(play);



}





const char *TreatArgument(int argc, char **argv)
{
	char *const fileName = (char*)malloc(sizeof(char)*20); 
	fileName[0] = '\0';
	if(argc >= 3) // se nome do arquivo conter espacos
	{
		int i = 1;
		for(; i < argc; ++i)
		{
			strcat(fileName,argv[i]);
			if(i < (argc-1))
				strcat(fileName," ");
		}
	}
	else if(argc == 2) // se nome do arquivo nao conter espacos
	{
		strcpy(fileName,argv[1]);
	}
	fileName[strlen(fileName)] = '\0';
	return fileName;
}

