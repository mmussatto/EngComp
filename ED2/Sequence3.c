/*  The program generates the sequence:
    F(1) = 1; F(2) = 1, 2, 1; F(3) = 1, 2, 1, 3, 1, 2, 1
    F(n) = F(n-1), F(n), F(n-1)
*/

#include <stdio.h>
#include <stdlib.h>


int f (int n)
{
    if(n == 0){ return 0; }
    
    else
    { 
       f(n-1);
       printf("%d ", n);
       f(n-1);
    }
}

int main ()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i <= n; i++)
    {
        printf("n = %d --> ", i);
        f(i);
        printf("\n\n");
    }
      

    printf("\n");
    system("pause"); //remeber to comment
    return 0;
}