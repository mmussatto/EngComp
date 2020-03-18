/*  The program performs a multiplication of two natural numbers 
    by adding a, b times
*/

#include "stdio.h"
#include "stdlib.h"

int Soma (int a, int b)
{
    if(b == 0) { return 0; } //it's 0 becausse it is already adding one time in the first reccursion

    return a + Soma(a, b-1);
}

int main ()
{
    int a, b, aux;
    scanf("%d", &a);
    scanf("%d", &b);

    if (a < b) 
    { //makes b the smaller number in order to run the code faster since the number a is added b times.
        aux = a;
        a = b;
        b = aux;
    }
    
    printf("%d\n", Soma(a, b));
    
    system("pause"); //remeber to comment
    return 0;
}