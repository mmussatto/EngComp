#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "Matriz.h"

Lista* cria_lista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
{
    if(li != NULL){
        Coord* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}


int insere_lista_ordenada(Lista* li, int cordx, int cordy)
{
    if(li == NULL)
        return 0;
    Coord *no = (Coord*) malloc(sizeof(Coord));
    if(no == NULL)
        return 0;

    no->linha = cordx;
    no->coluna = cordy;

    if((*li) == NULL){ //lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Coord *ant, *atual = *li;

        while(atual != NULL && atual->linha < cordx){
            ant = atual;
            atual = atual->prox;
        }

        if (atual != NULL && atual->linha == cordx) // caso  ja tenha uma coordenda com o mesmo "i"
        {
            // procedimento que ira encontrar a posicao correta da coordenda
            while (atual != NULL && atual->linha == cordx && atual->coluna < cordy){
                ant = atual;
                atual = atual->prox;
            }
            if(atual == *li){ //insere início
                no->prox = (*li);
                *li = no;
            }
            else{
                no->prox = atual;
                ant->prox = no;
            }
        }
        else if(atual == *li){ //insere início
            no->prox = (*li);
            *li = no;
        }
        else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}


void imprime_lista(Lista* li)
{
    if(li == NULL)
        return;
    Coord* no = *li;
    while(no != NULL){
        printf("%d %d\n", no->linha, no->coluna);
        no = no->prox;
    }
}


int tamanho_lista(Lista* li)
{
    if(li == NULL)
        return 0;
    int cont = 0;
    Coord* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

