/*  
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int max_at = 0;
int max_tt = 0;

int maior (int v[], int i, int x, int tam)
{
    if(i == tam){return 0;}

    if (x < max_at && v[i+1] < v[i]) {maior(v, i+1, v[i+1], tam);}

    else
    {
        max_at = x;
        if(max_at > max_tt) {max_tt = max_at;}
        maior (v, i+1, v[i]+v[i+1], tam);
    }


}

int main ()
{
    int v[6] = {-2, 11, -4, 13, -5, -2};
    //int v[7] = {5, 2, -1, 12, -10, 3, 1};
    //int v[8] = {-1,2,-4,2,-1,3,-4,5};
    int i;
    int tam = 6;
    //srand (time(NULL));

    printf("[ ");
    for ( i = 0; i < tam; i++)
    {
        //v[i] = rand() % 10;
        printf("%d, ", v[i]);
    }
    printf("]\n\n");

    maior(v, 0, v[0], tam);

    printf("-- %d --", max_tt);
    
    printf("\n");
    system("pause"); //remeber to comment
    return 0;
}