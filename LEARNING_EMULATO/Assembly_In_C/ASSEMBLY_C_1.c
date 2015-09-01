#include <stdio.h>





int main()
{
    int A = 0,C;

    
    if(A == 0)
    {
        asm("movl  $666,%eax\nmovl %%eax,%0;\n" : "=r" (A));
    }


    printf("%i",A);


}
