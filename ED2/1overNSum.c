/*  The program calculates the sum:
    1 + 1/2 + 1/3 + ... + 1/n
*/

#include "stdio.h"
#include "stdlib.h"

float Sum (float n)
{

    if (n == 1) {return 1;} //because 1/1 = 1 and 1/0 doesn't make sense

    return 1/n + Sum(n-1);

}

float main ()
{
    float n;
    scanf("%f", &n);

    printf("%f\n", Sum(n));
    
    system("pause"); //remeber to comment
    return 0;
}