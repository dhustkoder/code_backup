#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** POINTER TO FUNCTION BUBBLE SORT pure _C_ *******/



int compare(const char *const word1, const char *const word2)
{
    if(word1[0]  > word2[0])
        return 1;
    else
        return (word1[0] == word2[0]) ? 0 : -1;
}




void SORT(char **words,int (*OrderFunc)(const char *const, const char *const))
{
    
    size_t number_of_words = 0, i,j;
    for(; words[number_of_words] != NULL ; ++number_of_words);



 
    for(j=0; j < number_of_words; ++j)
        for(i = 0; i < number_of_words-1; ++i)
            if(OrderFunc(words[i],words[i+1]) == 1)
            {
                char temp[strlen(words[i])+1]; strcpy(temp,words[i]);
                free(words[i]);
                words[i] = (char*)malloc(sizeof(char)*strlen(words[i+1])); strcpy(words[i],words[i+1]);
                free(words[i+1]);    
                words[i+1] = (char*)malloc(sizeof(char)*strlen(temp)+1); strcpy(words[i+1],temp);

            }
    
}

int main()
{
    const char words[][10] = 
    {
        {"Barco"},
        {"Carro"},
        {"Abelha"}

    };

    char *palavras[3];
    palavras[0] =  (char*)malloc(sizeof(char)*strlen(words[0])+1); strcpy(palavras[0],words[0]);
    palavras[1] =  (char*)malloc(sizeof(char)*strlen(words[1])+1); strcpy(palavras[1],words[1]);
    palavras[2] =  (char*)malloc(sizeof(char)*strlen(words[2])+1); strcpy(palavras[2],words[2]); 
    palavras[3] = NULL;
    SORT(palavras,&compare);
    int i;
    for(i=0; i < 3; ++i)
        fprintf(stdout,"%s.\n",palavras[i]);

    return 0;
}
