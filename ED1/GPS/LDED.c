#include <stdio.h>
#include <stdlib.h>

#include "LDED.h"

Lista* cria_lista()
{
    Lista *li = (Lista*) malloc (sizeof(Lista));

    if(li != NULL) { *li = NULL;}
    
      
    return li;
}

void libera_lista(Lista* li)
{
    if (li != NULL)
    {
        Elem *no;
        
        while(*li != NULL)
        {
            no = *li;
            *li = (*li)->prox; 
            free (no);
        }

        free (li);
    }
}

void imprime_lista(Lista* li)
{
    Elem *no = *li;

    if(li == NULL) return;

    while (no != NULL)
    {
        printf("%.6lf %.6lf %d %.6lf %.6lf \n", no->Latitude, no->Longitude, no->Tempo, no->Velocidade, no->Dist_Percorrida);
        no = no->prox;
    }

    //printf("-------------- FIM LISTA -----------------\n");
}

/*int tamanho_lista(Lista* li)
{
    if(li == NULL) return ERRO;

    int cont = 0;
    Elem *no = *li;

    while(no != NULL)
    {
        cont++;
        no = no->prox;
    }

    return cont;
}*/

int insere_lista_final(Lista* li, Tipo_Dado lati, Tipo_Dado longi, int tempo)
{
    if(li == NULL) return ERRO;

    Elem *no;
    no = (Elem*) malloc (sizeof(Elem));
    if(no == NULL) return ERRO;

    no->Latitude = lati;
    no->Longitude = longi;
    no->Tempo = tempo;
    no->prox = NULL;

    if((*li) == NULL) //lista esta vazia
    {
        no->ant = NULL;
        *li = no;
    }
    else
    {
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }

    return OK;
}

/*int remove_lista_final(Lista* li)
{
    if(li == NULL) return ERRO;//lista nao criada

    if(*li == NULL) return ERRO; //lista vazia

    Elem *no;
    no = *li;

    while (no->prox != NULL) no=no->prox;

    if(no->ant == NULL) *li = no->prox; //so tem um no
    else no->ant->prox = NULL;

    free (no);
    return OK;
}

int insere_lista_inicio(Lista* li, Tipo_Dado dt)
{
    if(li == NULL) return ERRO; //lista nao iniciada

    Elem *no;
    no = (Elem*) malloc (sizeof(Elem));
    if(no == NULL) return ERRO;

    no->dado = dt;
    no->prox = *li;
    no->ant = NULL;
    
    if (*li != NULL) {(*li)->ant = no;}

    *li = no;

    return OK;
}

int remove_lista_inicio(Lista* li)
{
    if(li == NULL) return ERRO;//lista no criada

    if(*li == NULL) return ERRO; //lista vazia

    Elem *no;
    no = *li;

    *li = no->prox;

    if(no->prox != NULL) //lista tem mais de um no
    {
        no->prox->ant = NULL;
    }

    free (no);
    return OK;
}*/

/*int consulta_lista_pos(Lista* li, int pos, Tipo_Dado *dt)
{
    if(li == NULL || pos<=0) return ERRO;

    Elem *no;
    no = *li;

    int i = 1;

    while (no != NULL && i < pos)
    {
        no = no->prox;
        i++;
    }

    if(no == NULL) return ERRO;
    else
    {
        *dt = no->dado;
        return OK;
    }
}

int consulta_lista_dado(Lista* li, Tipo_Dado dt, Elem **el)
{
    if(li == NULL) return ERRO;

    Elem *no;
    no = *li;

    while(no != NULL && no->dado != dt)
    {
        no = no->prox;
    }

    if(no == NULL) return ERRO;
    else
    {
        *el = no;
        return OK;
    }
}*/