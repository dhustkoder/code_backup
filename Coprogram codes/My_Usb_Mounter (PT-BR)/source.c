#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MOUNT 1
#define UMOUNT 2


bool is_already_mounted(FILE *file,const char *partition)
{
 // /dev/sdb  8

		char aux = 0;
		char buffer[strlen(partition)+2];
		buffer[strlen(partition)+1] = '\0';
		while((aux = fgetc(file))!=EOF)
		{
			if(aux == '/')
			{
				fseek(file,-1,SEEK_CUR);
				fgets(buffer,strlen(partition)+1,file);
				if(strcmp(buffer,partition) == 0)
				{

					rewind(file);
					return true;
				}
			
			}
		}
	
		rewind(file);
		return false;
}

void mount(const char *partition,int option)
{
	if(option == MOUNT)
	{
			char sentence[strlen(partition)+7];
			strcpy(sentence,"mount ");
			strcat(sentence,partition);
			system(sentence);
	}
	else if(option == UMOUNT)
	{
			char sentence[strlen(partition)+8];
			strcpy(sentence,"umount ");
			strcat(sentence,partition);
			system(sentence);
	}

	
	
}


int main(int argc,char *argv[])
{


	if(argc < 2)
	{
		fprintf(stdout,"\n\033[1;37mPasse Um Argumento Ex.:\033[0m\n\033[1;31m#%s  -m/dev/sdb\n\033[0m",argv[0]);
		exit(0);
	}

	else if(argv[1][0] != '-' || argv[1][1] == 'h' || (argv[1][1] != 'm' && argv[1][1] != 'u') || strlen(argv[1]) < 5)
	{
		fprintf(stdout,"\n\033[1;37mpasse um argumento:\n%s '-m<particao>' para montar particao.\n%s '-u<particao>' para desmontar particao.\033[0m\n",argv[0],argv[0]);
		exit(0);
	}


	if(geteuid() != 0)
	{
		fprintf(stdout,"\n\033[1;37mPrograma necessita de privilegios root:\033[0m\n\033[1;31m#sudo %s [args]\n\033[0m",argv[0]);
		exit(0);
	}


	if(argv[1][1] == 'm')
	{
		if(argv[1][2] != '/')
		{
			argv[1]+=2;
			fprintf(stdout,"Voce deve passar a particao nesse formato: /%s\n",argv[1]);
			exit(0);
		}
		argv[1]+=2;
		FILE *file = fopen("/etc/fstab","r+");
		
		if(is_already_mounted(file,argv[1]))
		{
			fprintf(stdout,"\n\033[1;31mEsta particao ja esta em fstab.\nChamando mount e fechando...\033[0m\n");
			mount(argv[1],MOUNT);
			fclose(file);
			exit(0);
		}


		{
			fseek(file,0,SEEK_END);
			size_t tam = ftell(file);
			rewind(file);
			char buffer[tam+1]; buffer[tam] = '\0';
			fprintf(stdout,"\033[1;31m Conteudo Em fstab antes das mudancas...:\033[0m\n");
			fread(buffer,1,tam,file);
			puts(buffer);
		}

		fseek(file,0,SEEK_END);
		fprintf(stdout,"\n\033[1;32mEscrevendo no fstab...\033[1;32m\n");
		fprintf(file,"%s /mnt/usb auto defaults 0 0",argv[1]);
		fprintf(stdout,"\n\033[1;32mPronto, mostrando mudancas...\033[0m\n");
		size_t tam = ftell(file);
		char buffer[tam+1]; buffer[tam] = '\0';
		rewind(file);
		fread(buffer,1,tam,file);
		puts(buffer);
		fclose(file);

		mount(argv[1],MOUNT);
	}
	else if(argv[1][1] == 'u')
	{
		if(argv[1][2] != '/')
		{
			argv[1]+=2;
			fprintf(stdout,"Voce deve passar a particao nesse formato: /%s\n",argv[1]);
			exit(0);
		}


		FILE *file = fopen("/etc/fstab","r+");
		argv[1]+=2;

		if(is_already_mounted(file,argv[1]) == false)
		{
			fprintf(stdout,"\n\033[1;31m%s nao esta incluido em fstab...\n Chamando umount e fechando...\033[0m\n",argv[1]);
			mount(argv[1],UMOUNT);
			fclose(file);
			exit(0);
		}

		mount(argv[1],UMOUNT);

		{
			fprintf(stdout,"\033[1;31mMostrando fstab antes das mudancas...:\033[0m\n");
			fseek(file,0,SEEK_END);
			size_t tam = ftell(file);
			char show_fstab[tam+1]; show_fstab[tam] = '\0';
			rewind(file);
			fread(show_fstab,1,tam,file);
			puts(show_fstab);
			fprintf(stdout,"\n\033[1;32mAplicando mudancas em fstab...\033[0m\n");
			rewind(file);
		}


		char buffer[strlen(argv[1])+1];
		buffer[strlen(argv[1])] = '\0';
		char aux;
		while((aux = fgetc(file)) != EOF)
		{
			if(aux == '/')
			{
				fseek(file,-1,SEEK_CUR);
				fgets(buffer,strlen(argv[1])+1,file);
				if(strcmp(buffer,argv[1]) == 0)
					break;
			}
		}
		fseek(file,-(strlen(buffer)),SEEK_CUR);


		size_t before_deleted_line_SIZE = ftell(file);

		char before_deleted_line_TEXT[before_deleted_line_SIZE]; 
		rewind(file);
		fread(before_deleted_line_TEXT,1,before_deleted_line_SIZE,file);		
		
		while((aux = fgetc(file)) != '\n' && aux != EOF)
			continue;	
		
		if(aux != EOF)
		{
			size_t after_deleted_line_SIZE = 0;
			while((aux = fgetc(file))!= EOF)
				after_deleted_line_SIZE++;

			char after_deleted_line_TEXT[after_deleted_line_SIZE+1];
			
			fseek(file,-after_deleted_line_SIZE,SEEK_END);

			fread(after_deleted_line_TEXT,1,after_deleted_line_SIZE,file);
			
			fclose(file);
			file = fopen("/etc/fstab","w");
			
			fwrite(before_deleted_line_TEXT,1,before_deleted_line_SIZE,file);
			fwrite(after_deleted_line_TEXT,1,after_deleted_line_SIZE,file);	
			
		
		}
		else
		{
			fclose(file);
			file = fopen("/etc/fstab","w+");
			fwrite(before_deleted_line_TEXT,1,before_deleted_line_SIZE,file);
		}


		fseek(file,0,SEEK_END);
		size_t tam = ftell(file);
		char show_fstab[tam+1]; show_fstab[tam]='\0';
		rewind(file);
		fread(show_fstab,1,tam,file);
		fprintf(stdout,"\033[1;32mMostrando mudancas...\033[0m\n");
		fprintf(stdout,"%s",show_fstab);


		fclose(file);
	}



	return 0;	
}
