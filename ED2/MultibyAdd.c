/*  The program performs a multiplication of two natural numbers 
    by incrementing one at a time.
*/

#include <stdio.h>
#include <stdlib.h>

int Soma (int a, int b)
{
    if(b == 0) { return a; } //return a after all the additions 

    return Soma(a+1, b-1); //adds one to a at the same time it takes one from b
}

int Incremento (int a, int b)
{
    if(b == 1) {return 0 ;} //iquals one  because it has to exclude one time and then add one time at the return
                            // ex. 5*4 = 5 + (5+5+5). diminui o b e para com 1 para tirar o 5 fora dos parenteses
                            // e o que esta sendo incrementado no return

    return  a + Incremento(a, b-1);
}

int main ()
{
    int a, b, aux, i;
    scanf("%d", &a);
    scanf("%d", &b);

    if (a < b) 
    { //makes b the smaller number in order to run the code faster since the number a is added b times.
        aux = a;
        a = b;
        b = aux;
    }

    
    aux = Incremento(a, b); //computes the increment ex. 5*4 = 5 + 5*3 = 5 + 15. 15 is the increment
                            // the increment then will be used to add, one at a time, by function Soma
    
    printf("%d\n", Soma(a, aux));
    
    system("pause"); //remeber to comment
    return 0;
}