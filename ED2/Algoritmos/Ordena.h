#include <stdio.h>
#include <stdlib.h>

int Bubble_Sort(int v[], int T);
/*O BubbleSort basicamente vai empurrando o elemento de maior valor para o
final do vetor, fazendo trocas sucessivas entre dois elementos próximos,
sendo que na proxima iteracao, ele nao precisa olhar a ultima posicao
ja que o maior elemento do vetor ja esta nela*/

int Quick_Sort(int v[], int b, int n);
/*O quick sort vai definir um pivot (no caso, o elemento central do vetor) e achar
a posicao final desse elemento no vetor ordenado. Entao, o quick sort sera aplicado nos
dois subvetores criados, a direita e a esquerda do pivot*/

int Selection_Sort(int v[], int T);
/*O Selection Sort escaneia o vetor procurando o maior elemento e apos acha-lo, o coloca
na ultima posicao do vetor. O algoritimo roda novamente sem levar em conta a ultima posicao
pois o maior elemento já está la*/

int Heap_Sort(int v[], int n);
void faz_Heap(int v[], int n);
void ajuste(int v[], int i, int n);


int Insertion_Sort(int v[], int n);
/*O Insertion Sort percorre todo o vetor, da esquerda para a direita, comparando um elemento
com todos os seus antecessores. Assim, caso um elemento esteja fora de lugar (seja menor que seu antecessor)
o algoritmo ira compara-lo com todos os seus antecessores ate achar um que seja menor que ele. Entao a troca sera feita*/