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
    
    printf("Original: ");
    for(i=0;i<tamanho;i++)
    {
        v[i] = rand()%10;
        printf("%d ", v[i]);
    }
    printf("\n\n");

//------------- Bubble Sort -----------------------------
    printf("Bubble Sort: ");
    Bubble_Sort(v,tamanho);
    for(i=0;i<10;i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}