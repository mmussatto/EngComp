#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hash.h"

void cria_tabela(Elem* tabela[], int TABLE_SIZE)
{//faz com que todos os elementos da tabela apontem para NULL
    int i;

    for(i = 0; i < TABLE_SIZE; i++)
        tabela[i] = NULL;
}

void libera_tabela(Elem* tabela[], int TABLE_SIZE)
{//Libera a memoria alocada
    int i;
    Elem* aux;

    for(i = 0; i < TABLE_SIZE; i++)
    {
        while(tabela[i] != NULL)
        {
            aux = tabela[i];
            tabela[i] = tabela[i]->prox;
            free(aux);
        }
    }

}

void imprime_tabela(Elem* tabela[], int TABLE_SIZE)
{
    int i, num=0;
    Elem* aux;

    for (i = 0; i < TABLE_SIZE; i++)
    {
        aux = tabela[i];

        while (aux != NULL)
        {
            printf("%s ", aux->str);
            aux = aux->prox;

            if (aux == NULL) {
                num++;
                printf("\n");
            }
        }
    }

    printf ("Grupos totais: %d\n", num);
}



int funcao_hash(char v[], int TABLE_SIZE)
{
    int mult=1;
    int k, i;
    int dissipador=1; // variavel que vai aumentar a dispers�o caso TABLE_SIZE muito grande
    if(TABLE_SIZE>100)
        dissipador=10;
    if(TABLE_SIZE>1000)
        dissipador=100;

    for (i=0;i<5;i++)
    {
        k = v[i] - 96;
        mult = mult*k; // funcao hash multiplica os valores ascii correspondente a cada caracter da string
    }

    mult=mult*dissipador;

    return mult % TABLE_SIZE;
}

int funcao_rehash (int i, char str[], int TABLE_SIZE)
{
    int valor_rerash = (funcao_hash(str, TABLE_SIZE) + i)%TABLE_SIZE;
    return valor_rerash;
}


int insere_tabela_ordenada(Elem* tabela[], char str[], char ord[], int TABLE_SIZE)
{//insere os elementos na tabela de forma ordenada

    int endereco = funcao_hash(str, TABLE_SIZE);
    int i;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return ERRO;

    strcpy(no->str,str);
    strcpy(no->str_ordenada,ord);
    no->prox = NULL;

    if(tabela[endereco] == NULL)
    {//nao existe nenhum elemento naquele bucket
        tabela[endereco] = no;
        return OK;
    }
    else
    {//o bucket ja possui elementos
        Elem *atual = tabela[endereco];
        if(strcmp(tabela[endereco]->str_ordenada, ord) == 0)// as palavras sao anagramas entre si
        {
            while (atual->prox != NULL) {atual = atual->prox;}
            atual->prox = no; //insere na ultima posicao da lista
            return OK;
        }
        else //uso do overflow progressivo linear para tratar as colisoes das palavras nao anagramas com o mesmo valor hash
        {
            for (i=1;i<TABLE_SIZE - 1;i++) // incremento do 'i' ate encontrar um endereco vazio ou um endereco que seja seu anagrama
            {
                int novo_endereco = funcao_rehash(i, str, TABLE_SIZE);//funcao rerash para overflow progressivo

                if(tabela[novo_endereco] == NULL)
                {//nao existe nenhum elemento naquele bucket
                    tabela[novo_endereco] = no;
                    return OK;
                }
                else
                {//o bucket ja possui elementos
                    Elem *atual = tabela[novo_endereco];

                    if(strcmp(tabela[novo_endereco]->str_ordenada, ord) == 0)// as palavras sao anagramas entre si
                    {
                        while (atual->prox != NULL) { atual = atual->prox;}
                        atual->prox = no; // insere na ultiam posicao da lista
                        return OK;
                    }
                }
            }
        }
    }
    return OK;
}

void Ordenada_String(char v[], int T) //INT T = TAMANHO DO VETOR, 5 PRO TRABALHO
{
    int i, j, aux, troca = 1;

    for (i = 0; i < T-1 && troca; i++)
    {
        troca = 0;
        for (j = 0; j < T-i-1; j++)
            if (v[j] > v[j+1])
            {
                troca = 1;
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
    }
}
//JA MUDA A STRING POR REFERENCIA
