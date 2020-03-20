/*  The program generates the sequence:
    F(1) = 1 ; F(2) = 2 ; F(n) = 2*F(n-1) + 3*F(n-2)
*/

#include "stdio.h"
#include "stdlib.h"

int Sequence (int n)
{
    if (n == 1)
    {
        return 1;
    }

    else if (n == 2)
    {
        return 2;
    }

    else 
    {
        return 2*Sequence(n-1) + 3*Sequence(n-2);
    }
}

int main ()
{
    printf(" The program generates the sequence:\n F(1) = 1 ; F(2) = 2 ; F(n) = 2*F(n-1) + 3*F(n-2)");
    
    printf("Which n do you want to find ?\n");

    int n;
    scanf("%d", &n);

    printf(" %d\n",Sequence (n));
    
    system("pause"); //remeber to comment
    return 0;
}