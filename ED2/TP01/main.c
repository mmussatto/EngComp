#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "Matriz.h"


char* LerArquivo(char* string, int tamanho) {
	if(fgets(string, tamanho, stdin) != NULL) { // Remove a nova linha (\n), caso ela tenha sido lida pelo fgets

		int UltimoCaractere = strlen(string) - 1;

		if(string[UltimoCaractere] == '\n')
        {
			string[UltimoCaractere] = '\0';
		}

		return string;
	}
	return NULL;
}

int main ()
{
    printf("Digite o nome do arquivo: "); //TEM QUE ESCREVR .TXT,  Ex(matrix.txt)

    char nomearq[30];
    LerArquivo(nomearq, sizeof(nomearq));

    FILE *arq;
    arq = fopen(nomearq,"r");

    if(arq==NULL)
        printf("Problema em abrir o arquivo");

    int linha,coluna;
    fscanf(arq,"%d %d",&linha, &coluna);

    char espaco;                        //variavel pular espa�o e /n
    fscanf(arq,"%c",&espaco);

    Matriz *pontmatriz = cria_Matriz();  //cria�ao da matriz e ponteiro da matriz

    int i,j;                            //controle de linha e coluna
    int valor;                          //valor lido que ser� inserido 1 ou 0

    for(i=0;i<linha;i++)               //coordenadas come�am no 0 0
    {
         for(j=0;j<coluna;j++)
         {
             fscanf(arq,"%d%c",&valor, &espaco);
             insere_Matriz(pontmatriz,i,j,valor);
         }

    }

    int cordx,cordy; //coordenadas da posi�ao inicial
    fscanf(arq,"%d %d",&cordx, &cordy);

    fclose(arq);

    int visitado[linha][coluna]; // matriz que guarda as posicoes que ja foram visitadas pela recursao
    for(i=0;i<linha;i++)
    {
         for(j=0;j<coluna;j++)
         {
             visitado[i][j] = 0;
         }

    }

    Lista* li = cria_lista();

    Elem *no = *pontmatriz;

    while (no->i != cordx) {no = no->abaixo;}
    while (no->j != cordy) {no = no->direita;} // no apontara para a coordenada passada

    flood_fill(li, pontmatriz, no, linha, coluna, visitado);

    printf ("Total: %d\n", tamanho_lista(li)); // numero de 1's conectados
    imprime_lista(li); // todas as coordendas dos 1's conectados em ordem crescente

    printf("Total Operacoes: %d\n", RetornaCont());
    system("pause");

    libera_lista(li);
    libera_Matriz(pontmatriz);

    return 0;

}
