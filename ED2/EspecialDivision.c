/*  The program calculates the sum:
    2/4 + 5/5 + 10/6 + ... + (n^2 + 1)/(n+3)
*/

#include "stdio.h"
#include "stdlib.h"

float Division (float n)
{

    if (n == 0) {return 0;}

    return ((n*n + 1)/(n+3)) + Division(n-1);

}

float main ()
{
    float n;
    scanf("%f", &n);

    printf("%f\n", Division(n));
    
    system("pause"); //remeber to comment
    return 0;
}