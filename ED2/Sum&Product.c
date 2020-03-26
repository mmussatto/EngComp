/*  The program generates the sequence:
    F(0) = 0 ; F(1) = 1 ; F(n) = F(n-1) + F(n-2)^2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int Sum (int v[10], int i)
{
    if(i < 10)
    {
        return Sum(v , i+1) + v[i] ;
    }

    else{ return 0; }


}

float Product (int v[10], int i)
{
    if(i < 10)
    {
        return Product(v , i+1) * v[i] ;
    }

    else{ return 1; }


}

int main ()
{

    printf(" The program generates a randomized vector pf size 10\n And calculates the product and the sum of its elements\n\n");

    int v[10];
    int i;
    srand (time(NULL));

    printf("[ ");
    for ( i = 0; i < 10; i++)
    {
        v[i] = rand() % 10;
        printf("%d, ", v[i]);
    }
    printf("]\n\n");

    printf(" Sum = %d \n", Sum(v, 0));
    printf(" Product = %.0f \n", Product(v, 0));
    
    printf("\n");
    system("pause"); //remeber to comment
    return 0;
}