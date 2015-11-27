#ifndef READ_FILE_H
#define READ_FILE_H


struct Word_Hint
{
    std::string word;
    std::string hint;
    void clean_word()
    {
        bool space_hited{false};          
        std::string::iterator itr, deleter;
         for(itr = word.begin(); itr != word.end() ; itr++)
        {
            if(space_hited)
                if(*itr != 32 && *itr != 9)
                    space_hited = false;
                else
                    continue;

            
            else if(*itr == 32 || *itr == 9)
            {    
                space_hited = true;
                deleter = itr;
            }
        }
        if(space_hited)
            word.erase(deleter,itr);
   }
    void clean_hint()
    {
        bool space_hited{false};    
        std::string::iterator itr, deleter;
        for(itr = hint.begin(); itr != hint.end() ; itr++)
        {
            if(space_hited)
                if(*itr != 32 && *itr != 9)
                    space_hited = false;
                else
                    continue;

            
            else if(*itr == 32 || *itr == 9)
            {    
                space_hited = true;
                deleter = itr;
            }
        }
        if(space_hited)
            hint.erase(deleter,itr);
 
        
    }
};

struct Words_Hints
{
    Word_Hint *word_hint;
    size_t array_size;
    Words_Hints(size_t size) : array_size(size)
    {
        word_hint = new Word_Hint[array_size];
    }
    Words_Hints() : word_hint(nullptr){}

    void print_all()
    {
        for(size_t i{0}; i < array_size; ++i)
            std::cout << "Word is:" << word_hint[i].word << ".\n" << 
                         "Hint is:" << word_hint[i].hint << ".\n";
    }

    Words_Hints(Words_Hints&& old)
    {
        array_size = old.array_size;
        word_hint = old.word_hint;
        old.word_hint = nullptr;

        std::cout << " \n \n ||copiando &&|| \n \n";
    }
    
    Words_Hints& operator=(Words_Hints&& old)
    {
        array_size = old.array_size;
        word_hint = old.word_hint;
        old.word_hint = nullptr;

        std::cout << " \n \n ||copiando && =|| \n \n";

        return *this;
    }
    Words_Hints& operator=(const Words_Hints& old)
    {
        array_size = old.array_size;
        word_hint = new Word_Hint[array_size];
        for(size_t i{0}; i < array_size; ++i)
        {
            word_hint[i].word.assign(old.word_hint[i].word);
            word_hint[i].hint.assign(old.word_hint[i].hint);
        }
        std::cout << "||copiando =||";
        return *this;
    }        
    ~Words_Hints()
    {
        if(word_hint != nullptr)
            delete[] word_hint;
    }
    
};
Words_Hints GetWordsAndHints(const char *const fileName)
{
    

    std::ifstream file(fileName);

    std::string file_text;
    std::copy(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(),
              std::back_inserter(file_text));
    file.close();

    std::string temp(std::move(file_text));

    file_text.clear();
    
    // clean comments:
    {
        bool is_coment = false;
        

       
        for(char it : temp)
        {
            if(is_coment){
                if(it == '\n'){
                    is_coment = false;continue;}}
            else if(it == '#'){
                is_coment = true;continue;}
                    
            else
                file_text.push_back(it);
        }
    }
    
     //clean duplicates '\n':
        
       
    std::string::iterator itr;  
    do
    {
        itr = std::adjacent_find(file_text.begin(),file_text.end(),
                                [](char x,char y){return ((x=='\n') && (y == '\n'));});                                           
        if(itr != file_text.end())
            file_text.erase(itr,itr+1);

    }while(itr != file_text.end());
        
    
    
    size_t size = std::count(file_text.begin(),file_text.end(),'\n');
    Words_Hints words_hints(size);
    for(size_t i = 0,j = 0; i  < size && file_text[j] != '\0'; ++j)
    {
        if(file_text[j] != 32 &&  file_text[j] != 9 && file_text[j] != '\n')
        {
            for(; file_text[j] != '\n' && file_text[j] != '{' && file_text[j] != '\0'; ++j)
                    words_hints.word_hint[i].word.push_back(file_text[j]);    
           
            words_hints.word_hint[i].clean_word();
            

            if( file_text[j] == '{' )
            {
                j++;
                for(; file_text[j] != '\n' && file_text[j] != '}' && file_text[j] != '\0' ; ++j)
                    words_hints.word_hint[i].hint.push_back(file_text[j]);
           
                words_hints.word_hint[i].clean_hint(); 
            }
            
            i++;
        }
    }
  
    words_hints.print_all(); 
    return std::move(words_hints);         
}   

#endif