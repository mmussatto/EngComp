#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Ordena.h"

int CopiaVet (int v[], int v2[], int tam)
{
    int i;
    for(i = 0; i < tam; i++)
    {
        v2[i] = v[i];
    }
}

int main()
{
    int v[30], v1[30];
    int i;
    srand(time(0));
    int tamanho = sizeof(v)/sizeof(int);
    int cont;

    printf("Original: ");
    for(i=0;i<tamanho;i++)
    {
        v[i] = rand()%100;
        printf("%d ", v[i]);
    }
    printf("\n\n");

//------------- Bubble Sort -----------------------------
 
    printf("Bubble Sort: ");
    CopiaVet(v, v1, tamanho);
    cont = Bubble_Sort(v1,tamanho);
    for(i=0;i<tamanho;i++)
    {
        printf("%d ", v1[i]);
    }
    printf("\nOperacoes: %d\n\n\n", cont);


//------------- Quick Sort ------------------------------

    printf("Quick Sort: ");
    CopiaVet(v, v1, tamanho);
    cont = Quick_Sort(v1,0,tamanho-1);
    for(i=0;i<tamanho;i++)
    {
        printf("%d ", v1[i]);
    }
    printf("\nOperacoes: %d\n\n\n", cont);


//-------------- Selection Sort ------------------------

    printf("Selection Sort: ");
    CopiaVet(v, v1, tamanho);
    cont = Selection_Sort(v1, tamanho);
    for(i=0;i<tamanho;i++)
    {
        printf("%d ", v1[i]);
    }
    printf("\nOperacoes: %d\n\n\n", cont);


//-------------- Insertion Sort ------------------------

    printf("Insertion Sort: ");
    CopiaVet(v, v1, tamanho);
    cont = Insertion_Sort(v1,tamanho);
    for(i=0;i<tamanho;i++)
    {
        printf("%d ", v1[i]);
    }
    printf("\nOperacoes: %d\n\n\n", cont);

    system("pause");
    return 0;
}