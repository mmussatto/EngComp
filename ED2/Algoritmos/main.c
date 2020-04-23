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


    printf("Original: ");
    for(i=0;i<10;i++)
    {
        v[i] = rand()%10;
        printf("%d ", v[i]);
    }
    printf("\n\n");

    printf("Bubble Sort: ");
    Bubble_Sort(v,10);
    for(i=0;i<10;i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}