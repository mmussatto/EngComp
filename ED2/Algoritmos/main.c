#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Ordena.h"

int main()
{
    int v[10];
    int i;
    srand(time(0));
    int tamanho = sizeof(v)/sizeof(int);
    int cont;

    printf("Original: ");
    for(i=0;i<tamanho;i++)
    {
        v[i] = rand()%10;
        printf("%d ", v[i]);
    }
    printf("\n\n");

//------------- Bubble Sort -----------------------------
/*    
    printf("Bubble Sort: ");
    cont = Bubble_Sort(v,tamanho);
    for(i=0;i<10;i++)
    {
        printf("%d ", v[i]);
    }
    printf("\nOperacoes: %d\n", cont);
*/
//------------- Quick Sort ------------------------------

    printf("Quick Sort: ");
    Quick_Sort(v,0,tamanho);
    for(i=0;i<10;i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");


    system("pause");
    return 0;
}