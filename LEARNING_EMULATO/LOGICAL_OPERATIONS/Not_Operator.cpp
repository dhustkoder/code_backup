#include <iostream>
#include <bitset>

// MASK UTILIZANDO NOT OPERATOR '~' PARA AUXILIAR

int main()
{
	char BYTE = 0; //  0000 0000

	// ligar o setimo bit de BYTE
	BYTE = BYTE | 0x40;  
/* 							
						  BYTE 	 == 0000 0000
						  0x40   == 0100 0000

						  RESULT == 0100 0000 
*/
	std::cout << std::bitset<8>(BYTE) << std::endl; // 0100 0000 


	// Desligando o mesmo bit usando o not operator para auxiliar
	BYTE = BYTE & ~0x40;
/* 							
						  BYTE 	 == 0000 0000
						  ~0x40  == 1011 1111

						  RESULT == 0100 0000 
*/

	std::cout << std::bitset<8>(BYTE) << std::endl; // 0000 0000

}