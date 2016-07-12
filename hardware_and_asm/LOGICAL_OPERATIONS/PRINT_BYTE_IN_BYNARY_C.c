#include <stdio.h>
#include <stdint.h>

// print byte in binary with C 


void byte_bin(uint8_t byte) // 0000 0001
{
    int i = 7;
    for ( ; i  >= 0 ; --i)
        if(byte & ( 1 << i))  //(1 << 7) == 1000 0000 
            printf("1");
        else
            printf("0");

}

int main()
{

 
    byte_bin(1); 

}
