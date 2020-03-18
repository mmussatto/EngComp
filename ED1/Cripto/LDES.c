#include <stdio.h>
#include <stdlib.h>

#include "LDES.h"

Lista* cria_lista ()
{
    Lista *li = (Lista*)malloc(sizeof(Lista));
    if (li != NULL)
    { 
        *li = NULL;
    }
    return li;
}

void libera_lista(Lista* li)
{
    if(li != NULL)
    {
        Elem *no;
        while (*li != NULL)
        {
            no = *li; 
            *li = (*li)->prox; 
            free(no);
        }
        free (li);
    }
}

int insere_lista_final(Lista* li, tipo_dado dt)
{
    if(li == NULL){return ERRO;}

    Elem *no;
    no = (Elem *)malloc (sizeof (Elem));
    if(no == NULL){return ERRO;}

    no->dado = dt;
    no->prox = NULL; //novo ultimo 
    
    if(*li == NULL){*li = no;}
    else
    {
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox; //acha o antigo ultimo
        }
        aux->prox = no; //antigo ultimo aponta para novo ultimo
    }
    return OK;   
}

int insere_apos(Elem *no_msg, Elem *no_chave, int contador)
{
    Elem *no;
    no = (Elem *)malloc (sizeof (Elem));
    if(no == NULL){return ERRO;}

    for (int i = 1; i <= contador; i++)
    {
       if (i == contador)
       {
            no->prox = no_msg->prox;
            no->dado = no_chave->dado;
            no_msg->prox = no;
       }
       no_msg = no_msg->prox;
       if(no_msg == NULL){return 0;} //restorna zero caso a mensagem tenha acabado 
       
    }
}

int remove_apos(Elem *no_msg, int contador)
{
    Elem *no;
    
    for (int i = 1; i <= contador; i++)
    {
        if (i == contador)
        {
            if(no_msg->prox == NULL){break;}
            no = no_msg->prox;
            no_msg->prox = no->prox;
            free(no);
        }
        no_msg = no_msg->prox;
        if(no_msg == NULL){return 0;} //restorna zero caso a mensagem tenha acabado 
    }
}

void imprime_lista(Lista* li)
{
    if(li == NULL){return;}

    Elem *no;
    no = *li;

    while (no != NULL)
    {
       printf("%c", no->dado);
        no = no->prox;
    }
    
}

int tamanho_lista(Lista* li)
{
    if(li == NULL){return 0;}
    int cont = 0;
    Elem *no = *li;
    while(no != NULL)
    {
        cont++;
        no = no->prox;
    }
    return cont;
}