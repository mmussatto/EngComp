#include <stdio.h>
#include <stdlib.h>

#include "Matriz.h"

Matriz* cria_Matriz()
{
    Matriz *li = (Matriz*) malloc (sizeof(Matriz));

    if(li != NULL){ *li = NULL;}

    return li;
}
void libera_Matriz(Matriz *li)
{//procedimento: limpar a linha apartira da coluna (j=1) e depois limpar o primeiro elemento da linha;
 //fazer isso para todas as linhas, de cima para baixo;
    if(li != NULL)
    {
        Elem *linha; 
        Elem *no; 

        while(*li != NULL) //limpa a coluna
        {
            linha = (*li)->direita; //comeca na segunda coluna (j=1)
            while(linha != NULL) //limpa a linha
            {   
                no = linha;
                linha = linha->direita;
                free(no);
            }
            linha = *li; //primeiro elemento da linha
            *li = (*li)->abaixo; //proxima linha 
            free(linha);
        }
        
        free(li);
    }
    
}

int insere_Matriz (Matriz *li, int i, int j, Tipo_Dado info)
{
    if(li == NULL) return ERRO;

    Elem *no;
    no = (Elem*) malloc (sizeof(Elem));
    if(no == NULL) return ERRO;


    no->i = i;
    no->j = j;
    no->info = info;
    no->direita = NULL;   //Matriz eh preenchida da esquerda para a direita
    no->abaixo = NULL;    // e de cima para baixo

    if((*li) == NULL) //Matriz vazia; elemento (0,0)
    {
        no->acima = NULL;
        no->esquerda = NULL;
        *li = no;
    }
    else if (j == 0) //primeira coluna 
    {
        Elem *aux; //ultimo no da coluna, acima do novo
        aux = *li;

        while (aux->i != i-1){ aux = aux->abaixo;} //seleciona aux
            
        aux->abaixo = no;
        no->acima = aux;
        no->esquerda = NULL; //primeira coluna toda a esquerda eh NULL
    }
    else if (i == 0) //primeira linha
    {
        Elem *aux;
        aux = *li;

        while (aux->j != j-1){ aux = aux->direita;}

        aux->direita = no;
        no->esquerda = aux;
        no->acima = NULL;
    }
    else //demais itens
    {
        Elem *aux; //no na linha do novo e um espaco a esquerda
        aux = *li;

        while (aux->i != i){ aux = aux->abaixo;} //seleciona a linha do novo no
        while (aux->j != j-1){ aux = aux->direita;} //seleciona o no imediatamente a esquerda

        aux->direita = no;
        no->esquerda = aux;

        Elem *temp; //no imediatamente acima do novo
        temp = *li;

        while (temp->i != i-1){ temp = temp->abaixo;} //seleciona a linha acima do novo no
        while (temp->j != j){ temp = temp->direita;}  //seleciona a coluna do novo no

        temp->abaixo = no;
        no->acima = temp;

    }
    
    return OK;

}

void imprime_Matriz(Matriz *li)
{
    Elem *linha = *li;
    Elem *no;

    if(li == NULL) return;

    while(linha != NULL)
    {
        no = linha;
        while (no != NULL)
        {
            printf("%d ", no->info);
            no = no->direita;
        }
        printf("\n");
        linha = linha->abaixo;    
    }
}