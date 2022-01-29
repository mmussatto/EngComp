#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

char* LerNomeArquivo(char* string, int tamanho) {
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

    printf("Digite o nome do arquivo: "); //TEM QUE ESCREVR .txt,  Ex(teste.txt)

    char nomearq[30];
    LerNomeArquivo(nomearq, sizeof(nomearq));

    FILE *arq;
    arq = fopen(nomearq,"r");

    if(arq==NULL)
	{
		printf("Problema em abrir o arquivo");
		return 0;
	}

    int TABLE_SIZE = 0;
	Elem **tabela;


	char aux[6], aux_ordenada[6];
	int num_palavras = 0;

	while(!feof(arq))
    {//conta o numero de palvras
        fscanf(arq,"%s",aux);
        num_palavras++;
    }

    fclose(arq);


    while(TABLE_SIZE < num_palavras)
    {//definir o tamanho da tabela
        TABLE_SIZE = TABLE_SIZE + 10;
        if(TABLE_SIZE > num_palavras)
            break;
    }


    tabela = (Elem **) malloc (TABLE_SIZE * sizeof(Elem*));
    cria_tabela(tabela, TABLE_SIZE);


    arq = fopen(nomearq,"r");

	while(fgets(aux, sizeof(aux), arq) != NULL )
	{
		if(aux[0] == '\n') {continue;}

		strcpy(aux_ordenada, aux);
		Ordenada_String(aux_ordenada, 5);
		insere_tabela_ordenada(tabela, aux, aux_ordenada, TABLE_SIZE);
	}


	imprime_tabela(tabela, TABLE_SIZE);

	//system("pause");

	fclose(arq);
	libera_tabela(tabela, TABLE_SIZE);
	free(tabela);

    return 0;


}
