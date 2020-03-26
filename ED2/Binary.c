/*  Writes a natural number in binary
    Just input the natural number you want to transform
*/

#include <stdio.h>
#include <stdlib.h>

int Bin (int n)
{
    if(n == 0) { return; }

    else{ Bin(n/2); }
    
    printf("%d", n%2);
}

int main ()
{
    int n;
    scanf("%d", &n);

    if (n == 0){ printf("%d", 0);}
    else{ Bin(n); }
    
    printf("\n");
    
    system("pause");
    return 0;
}