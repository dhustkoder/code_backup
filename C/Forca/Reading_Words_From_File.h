#ifndef READING_WORDS_FROM_FILE_H
#define READING_WORDS_FROM_FILE_H
#define MAX_LINES 128
#define MAX_CHAR 128

//----------------------------------------------------------Struct_Valid_Lines
typedef struct Struct_Valid_Lines
{
	int max_lines;
	bool *lines;
}Struct_Valid_Lines;


void Initialize_Bool_Array(bool arr[],int size)
{
	int i;
	for(i = 0; i < size;++i)
		arr[i] = false;
}

Struct_Valid_Lines* Initialize_Valid_Lines(const char *const fileName)
{
	FILE *file  =  fopen(fileName,"r"); 
	if(file == NULL)
	{
		fprintf(stdout,"nao foi possivel abrir arquivo \033[0;31m%s\033[0m\n",fileName); exit(0);
	}
	
	

	bool valid_lines[MAX_LINES]; Initialize_Bool_Array(valid_lines,MAX_LINES);


	fprintf(stdout,"\033[0;32mEscaneando Arquivo...:\033[0m\n");

	char buffer;
	int current_line = 0; 
	while((buffer = fgetc(file)) != EOF && current_line < MAX_LINES)
	{
		if(buffer == '#') //comment lines
		{
			do
			{
				fprintf(stdout, "%c",buffer);
				buffer = fgetc(file);
				
			}while(buffer != '\n');
			current_line++;
		}

		else if(buffer == '\n')
		{
			current_line++;
		}
		else if(buffer != 32  && buffer!= '\n' && buffer != 9)
		{
			valid_lines[current_line] = true;
			do
			{
				if(buffer != EOF)
					fprintf(stdout,"%c",buffer);
				buffer = fgetc(file);

				if(buffer == EOF || buffer == '\n')
					break;
			}while(buffer != EOF && buffer != '\n');
			current_line++;
			

		}

		fprintf(stdout,"%c",buffer);

	}
	fclose(file);
	
	// mount structure Valid Lines, nao esquecer de liberar memoria

	Struct_Valid_Lines *ValLines = (Struct_Valid_Lines*)malloc(sizeof(Struct_Valid_Lines));
	ValLines->max_lines = current_line;
	ValLines->lines = (bool*)malloc(sizeof(bool)*current_line);
	Initialize_Bool_Array(ValLines->lines,current_line);
	int i = 0;
	for(; i < current_line; ++i)
	{
		if(valid_lines[i] == true)
		{
			fprintf(stdout,"linha %i eh valida\n",i);
			ValLines->lines[i] = true;
		}
	}
	fprintf(stdout,"\n");
	return ValLines;

}





//------------------------------------------------------------- Struct_Forca_Word

typedef struct Struct_Forca_Word
{
	char* word;
	char* hint;
	size_t my_arr_size; 

}Struct_Forca_Word;


Struct_Forca_Word* Initialize_Struct_Forca_Word(Struct_Valid_Lines* valid_lines)
{
	int array_size_to_be = 0;
	int i = 0;
	for(; i < valid_lines->max_lines;++i)
	{
		if(valid_lines->lines[i] == true)
			array_size_to_be++;
		
	}
//	fprintf(stdout,"\n\n\n -- %i -- \n\n\n",array_size_to_be);
	Struct_Forca_Word *forca_Word = (Struct_Forca_Word*)malloc(sizeof(Struct_Forca_Word)*array_size_to_be);

	for(i = 0; i < array_size_to_be; ++i )
	{
		forca_Word[i].word = NULL;
		forca_Word[i].hint = NULL;
		forca_Word[i].my_arr_size = array_size_to_be;
	}

	return forca_Word;
}





//----------------------------------------------------------Capture_Words_And_Hints

void Capture_Words_And_Hints(Struct_Forca_Word *forca_Word, Struct_Valid_Lines *valid_lines, FILE *file)
{
	char buffer = 0; int forca_Word_index = 0, current_line = 0;

	fprintf(stdout,"\033[0;33mCapturando Palavras...\n");
	for(; current_line < valid_lines->max_lines; ++current_line)
	{
		if(valid_lines->lines[current_line] == true) // if line is a valid line
		{
			forca_Word[forca_Word_index].word = (char*)malloc(sizeof(char)*MAX_CHAR);

			int word_index = 0; // charactere array indexer

			do
			{
				buffer = fgetc(file); // get character

				if(buffer == '{') // if hint begin 
					break;


				if(buffer != '\n' && buffer != EOF)
				{
					forca_Word[forca_Word_index].word[word_index] = buffer;
					word_index++;
				}

			}while(buffer != '\n' && buffer != EOF);


			forca_Word[forca_Word_index].word[word_index] = '\0'; // end of string

			if(buffer == '{')
			{
				word_index = 0;
				forca_Word[forca_Word_index].hint = (char*)malloc(sizeof(char)*MAX_CHAR);
				do
				{
					buffer = fgetc(file);
					
					if(buffer == '}')
					{
					 	do
					 	{
					 		buffer = fgetc(file);
					 	}while(buffer != '\n' && buffer != EOF);
					 	break;
					}



					else if(buffer != '\n' && buffer != EOF)
					{
						forca_Word[forca_Word_index].hint[word_index] = buffer;
						word_index++;
					}

					
				}while(buffer != '\n' && buffer != EOF);

				forca_Word[forca_Word_index].hint[word_index] = '\0';
			}

			forca_Word_index++;
		}

		else // if line isnt valid 
		{
			do
			{
				buffer = fgetc(file);
			}while(buffer != '\n' && buffer != EOF);
		}

	}
	fprintf(stdout,"\n...Pronto!\n\033[0m");

}



// ----------------------------------------------------------- Erase_Empty_Spaces
void Erase_Empty_Spaces(Struct_Forca_Word* forca_Word)
{
	size_t max_size = forca_Word[0].my_arr_size;
	size_t i = 0; int index = 0;
	for(; i < max_size; ++i)
	{
		if(forca_Word[i].word != NULL)
		{
			int blank_point_test = 0;
			for(index = 0; forca_Word[i].word[index] != '\0'; ++index)
			{
				if(forca_Word[i].word[index] == 32 || forca_Word[i].word[index] == 9)
				{
					blank_point_test = index;
					bool is_right_blank_point = true;
					do
					{
						if(forca_Word[i].word[blank_point_test] != 32 && forca_Word[i].word[blank_point_test] != 9)
						{
							is_right_blank_point = false;
							break;
						}

						blank_point_test++;
					}while(forca_Word[i].word[blank_point_test] != '\0');

					if(is_right_blank_point == true)
					{
						forca_Word[i].word[index] = '\0';
					}
				}

			}
		}
	}
}

//---------------------------------------------------

Struct_Forca_Word* Constructor(const char *const fileName, Struct_Valid_Lines* valid_lines)
{

	

	Struct_Forca_Word *forca_Word = Initialize_Struct_Forca_Word(valid_lines); // inicializa Forca_Word


	FILE *file = fopen(fileName,"r"); // abre arquivo
	if(file == NULL) {printf("erro no arquivo \033[0;31m%s\033[0m\n",fileName);exit(0);}

	Capture_Words_And_Hints(forca_Word,valid_lines,file); // captura palavras e dicas

	fclose(file); // fecha arquivo

	Erase_Empty_Spaces(forca_Word); // apaga espacos vazios entre a palavra e a dica

	free(valid_lines->lines); // libera memoria aloca para lines
	free(valid_lines); // libera memoria alocada para valid_lines

	return forca_Word;
}

Struct_Forca_Word* Read_Words_From_File(const char *const fileName)
{
	return Constructor(fileName,Initialize_Valid_Lines(fileName));


}






#endif


























