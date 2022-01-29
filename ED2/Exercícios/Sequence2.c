/*  The program generates the sequence:
    F(0) = 0 ; F(1) = 1 ; F(n) = F(n-1) + F(n-2)^2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Sequence (int n)
{
    if (n == 0)
    {
        return 0;
    }

    else if (n == 1)
    {
        return 1;
    }

    else 
    {
        return Sequence(n-1) + pow(Sequence(n-2), 2);
    }
}

int main ()
{
    printf(" The program generates the sequence:\n F(0) = 0 ; F(1) = 1 ; F(n) = F(n-1) + F(n-2)^2\n");
    printf(" Which n do you want to find ?\n\n");

    int n;
    int i;
    scanf("%d", &n);

    printf("\n\n F(%d) = %.0lf\n\n",n ,Sequence (n));

    for ( i = 0; i <= n; i++)
    {
        printf("%.0lf, ", Sequence(i));
    }
    
    printf("\n");
    system("pause"); //remeber to comment
    return 0;
}