/*  The program performs an addition of two natural numbers 
    by incrementing one at a time.
*/

#include <stdio.h>
#include <stdlib.h>

int Soma (int a, int b)
{
    if(b == 0) { return a; } //return a after all the additions 

    return Soma(a+1, b-1); //adds one to a at the same time it takes one from b
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