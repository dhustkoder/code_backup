#include <iostream>
#include <iomanip>
#include <bitset>
/*
							  LOGICAL OR : '|'		 |	   LOGICAL AND : '&' 
													 |
					           x	 y	 RESULT	     |	      x     y    RESULT   
							   0     0     0         |	 	  0     0      0
							   0     1     1      	 |		  0     1      0
							   1     0     1 	 	 |		  1     0      0
							   1     1     1         |        1     1      1
													 |
*/
void Logical_AND(uint8_t BYTE = 18) // 0001 0010
{
	uint8_t BYTE_2 = 21;  // 0001 0101

	uint8_t RESULT = BYTE & BYTE_2; /* 0001 0010
									   0001 0101
									   0001 0000   */

	 std::cout << unsigned(RESULT) << "  | HEX: " << std::hex << unsigned(RESULT) << "  | BIN: " << std::bitset<8>(RESULT);
	 			//           16                                            10                             0001 0000
}

void Logical_OR(uint8_t BYTE = 18) // 0001 0010
{
	uint8_t BYTE_2 = 21;  // 0001 0101

	uint8_t RESULT = BYTE | BYTE_2; /* 0001 0010
									   0001 0101
									   0001 0111   */

	 std::cout << unsigned(RESULT) << "  | HEX: " << std::hex << unsigned(RESULT) << "  | BIN: " << std::bitset<8>(RESULT);
	 			//           23                                            17                             0001 0000
}

int main()
{
	std::cout << std::bitset<8>(23) << std::endl;
	Logical_AND();
	std::cout << std::endl;
	std::cout.unsetf(std::ios::hex | std::ios::basefield);
	Logical_OR();
	std::cout << std::endl;
}