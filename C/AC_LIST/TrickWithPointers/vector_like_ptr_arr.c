#include <stdio.h>
#include <stdlib.h>
typedef struct Test
{
	const char* m_name;
	int m_type;

}Test;


int main()
{
	
	Test** ptrArr = (Test**) malloc(sizeof(Test*)* 3);
	int i;
	for( i = 0; i < 3; ++i){
		ptrArr[i] = (Test*) malloc(sizeof(Test));
	}
	
	ptrArr[0]->m_name = "Maniac";
	ptrArr[0]->m_type = 0;
	
	
	ptrArr[1]->m_name = "Alucard";
	ptrArr[1]->m_type = 1;
	
	
	ptrArr[2]->m_name = "THE END";
	ptrArr[2]->m_type = 2;
	
	
	Test** itr = ptrArr;
	
	
	
	for( i = 0; i < 3; ++i){
		printf("NAME %s\nType: %d\n", (*itr)->m_name, (*itr)->m_type);
		free((*itr));
		itr = &(*itr)+1;
	}
	
	

}