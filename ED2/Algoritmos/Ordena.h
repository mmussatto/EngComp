#include <stdio.h>
#include <stdlib.h>

int Bubble_Sort(int v[], int T);
/*O BubbleSort basicamente vai empurrando o elemento de maior valor para o
final do vetor, sendo que na proxima iteracao, ele nao precisa olhar a ultima posicao
ja que o maior elemento do vetor ja esta nela*/

int Quick_Sort(int v[], int b, int n);
/*O quick sort vai definir um pivot (no caso, o elemento central do vetor) e achar
a posicao final desse elemento no vetor ordenado. Entao, o quick sort sera aplicado nos
dois subvetores criados, a direita e a esquerda do pivot*/

