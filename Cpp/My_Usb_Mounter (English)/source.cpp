#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unistd.h>


bool details_on = false;
void Show_File_Before();
void Show_File_After();

std::string
	partition(""),
	dir("/mnt/default"),
	type("auto"),
	options("defaults"),
	full_line("");


void Mount();
void Umount();
bool CheckFile();


inline void Error(const char* error)
{
	std::cout << "\033[1;31merror: " << error << "\033[0m\n";
	exit(-1);
}
inline void Attention(const char* msg)
{
	std::cout << "\033[1;33m" << msg << "\033[0m\n";
}


void Validate_Args()
{
	if(partition[0] != '/')
		partition.insert(partition.begin(),'/');
	if(partition.size() < 5)
	{
		Error("Partition name is too short.");
		exit(0);
	}
	
	
}


int main(int argc, char **argv)
{
	
	if(argc < 2)
		Error("Program takes at least 1 argument -m<partition_name> or -u<partition_name>. Use -h for Help");
	else if(geteuid() != 0)
		Error("Need root privilegies");
	
	int i = 1;
	bool mount = false;
	for( ; i < argc; ++i)
		if(argv[i][0] == '-')
			switch(argv[i][1])
			{
				case 'm':
					if(partition.empty())
					{
						argv[i]+=2;
						partition.assign(&argv[i][0]);
						mount = true;
					}
					else
						Error("Each argument must be used once: -m -d -t -o");
					break;


				case 'u':
					if(mount == false && argc <=3)
					{	
						argv[i]+=2;
						partition.assign(&argv[i][0]);
					}
					if(i == 1){
						if(argv[2][1] != 'l')
							Error("-u must be used with -l only.");}
					
					else if(i == 2)
						if((argv[1][1]) != 'l')
							Error("-u must be used with -l only.");
					break;


				case 'd':
					if(dir.compare("/mnt/default") == 0)
					{
						argv[i]+=2;
						dir.assign(argv[i]);
					}
                    else
                      	Error("Use each argument one time: -m -d -t -o");
			        break;

            
                case 't':
                    if(type.compare("auto")==0)
                    {
                        argv[i]+=2;
                        type.assign(argv[i]);
                    }
                    else
                        Error("Use each argument one time: -m -d -t -o");
                    break;

				case 'l':
					details_on = true;
					break;
				

                default:
					Error("Bad argument syntax. use -h for help");
				    break;
			}	
	

	Validate_Args();
	if(mount)
	{
		if(!CheckFile())
			Mount();
		else
		{
			Error("Partition name already in /etc/fstab. Calling mount and exiting");
			//system(&std::string("mount "+partition)[0]);
			exit(0);
		}
	}
	else
	{
		if(CheckFile())
			Umount();
		else
		{
			Error("Partition name not fount in /etc/fstab. Calling umount and exiting");
			//system(&std::string("umount "+partition)[0]);
			exit(0);
		}

	}





}



void Show_File_Before()
{
	std::ifstream file("/etc/fstab");
	if(!file.good())
		Error("Cannot open /etc/file");

	Attention("Showing /etc/fstab before the changes...\n------------------------------\n");
	char buf;
	while((buf = file.get()) && !file.eof())
		std::cout << buf;
	Attention("\n------------------------------\n");

	file.close();
}
void Show_File_After()
{
	std::ifstream file("/etc/fstab");
	if(!file.good())
		Error("Cannot open /etc/file");

	Attention("Showing /etc/fstab After the changes...\n------------------------------\n");
	char buf;
	while((buf = file.get()) && !file.eof())
		std::cout << buf;
	Attention("\n------------------------------\n");
	file.close();
}




bool CheckFile()
{
	std::ifstream file("/etc/fstab");
	if(!file.good())
		Error("Cannot open '/etc/fstab'");
	std::string aux;
	while(file >> aux && !file.eof())
		if(aux == partition)
		{
			file.close();
			return true;
		}

	
	file.close();
	return false;	


}



void Mount()
{
	full_line = ("\n" + partition + " " + dir + " " + type + " " + options + " 0 0");
    
    if(details_on)
    {
        Attention("Your line is:");
        std::cout << full_line << "\n";
        Attention("Is this line you want to insert in fstab? [y/n]:");
        if(std::tolower(std::cin.get()) != 'y')
            {   Attention("exiting"); exit(0);   } 

    }



	std::ofstream file("/etc/fstab",std::ios::app);
	if(!file.good())
		Error("cannot open file '/etc/fstab'");
	if(details_on)
		Show_File_Before();

	file << full_line;

	file.close();
	
	if(details_on)
		Show_File_After();

	

}




void Umount()
{

	std::fstream file("/etc/fstab", std::ios::in);
	if(!file.good())
		Error("Cannot open /etc/fstab");

	if(details_on)
		Show_File_Before();

	file.seekg(0,file.end);
	size_t size = file.tellg();
	file.seekg(0,file.beg);

	std::string file_text;
	file_text.resize(size);
	file.read(&(*file_text.begin()),size);
	file.close();

	std::string::iterator del_begin, del_end;

	del_begin = std::search(file_text.begin(),file_text.end(),partition.begin(),partition.end());

	del_end = std::find_if(del_begin,file_text.end(),[](char x){return (x == '\n' || x == '\0');});
	if(*del_end == '\n')
		del_end++;
	file_text.erase(del_begin,del_end);

	file.open("/etc/fstab", std::ios::out | std::ios::trunc);

	file.write(&(*file_text.begin()),file_text.size());


	file.close();

	if(details_on)
		Show_File_After();


}
