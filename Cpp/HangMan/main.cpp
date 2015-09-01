#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <ctime>
#include "read_file.h"

struct Palavras
{
	Words_Hints words_hints;
	std::string chosenWord;
	std::string hint;
	std::string hiddenWord;
	int erros{0};
	Palavras(const char *fileName) : words_hints(GetWordsAndHints(fileName))
	{
		std::srand(std::time(NULL));
		size_t random = (std::rand()%(words_hints.array_size));
		chosenWord.assign(words_hints.word_hint[random].word);
		hint.assign(words_hints.word_hint[random].hint);
		hiddenWord.resize(chosenWord.size());
		std::fill(hiddenWord.begin(),hiddenWord.end(),'_');
	}
	void Tryy(char guess)
	{
		if(std::any_of(chosenWord.begin(),chosenWord.end(),
        [&](char x){return (std::tolower(x) == std::tolower(guess));}))
		{
			std::transform(chosenWord.begin(),chosenWord.end(),hiddenWord.begin(),hiddenWord.begin(),
				[&](char x, char y){
                if(std::tolower(x)==std::tolower(guess)) 
                    return x;
                else if(y != '_') 
                    return y; 
                else return '_';});
		}
		else
			erros++;
	}
};

struct Forca
{
    
	std::string corpo;
    Forca() : corpo("      "){}
    void Print(int erros)
    {
        switch(erros)
        {
            case 1:
                corpo[0] = '0';  break;
            case 2:
                corpo[1] = '/';  break;
            case 3:
                corpo[2] = '|'; break;
            case 4:
                corpo[3] = '\\';  break;
            case 5:
                corpo[4] = '/'; break;
            case 6:
                corpo[5] = '\\'; break;
        }
        std::cout << " _______\n" <<
                     "|     "<< corpo[0] << std::endl <<
                     "|    " << corpo[1] << corpo[2] << corpo[3] << std::endl <<
                     "|    " << corpo[4] <<" "<< corpo[5] << std::endl << 
                     "|\n" <<
                     "|\n" << std::endl;    

    }
};

int main(int argc, char **argv)
{
	if(argc >= 2)
	{
		Palavras test(argv[1]);
		Forca forca;
        char guess{0};
        std::string digitadas;
		while(guess != '@' && test.erros <= 7 )
		{
			system("clear");
			std::cout << "\t******************** Hang Man C++ ***********************\n\n '@' exit\n\n";
            forca.Print(test.erros);    
           	std::cout << "Dica: " << test.hint << ".\n\n";
            std::cout << "Letras Digitadas: ";
            std::copy(digitadas.begin(),digitadas.end(),
                        std::ostream_iterator<char>(std::cout,", "));std::cout << "\n";
            

             std::copy(test.hiddenWord.begin(),test.hiddenWord.end(),
                        std::ostream_iterator<char>(std::cout," "));
	        if(test.erros == 6 || (test.chosenWord.compare(test.hiddenWord) == 0))
                break;
            std::cin.get(guess);if(guess == 32 || guess == 9 || guess == '\n') continue;
			digitadas.push_back(guess);
            std::cin.ignore(999,'\n');
			test.Tryy(guess);
		} 
        if(test.chosenWord.compare(test.hiddenWord) == 0)
            std::cout << "\n****Congrats the word was: " << test.chosenWord << "! ****\n";
        else
            std::cout << "\n****Sorry... the word was: " << test.chosenWord << "! ****\n";
		
	}
}
