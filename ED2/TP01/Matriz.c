#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "Matriz.h"
#define TRUE 2

int cont = 0; //contagem do numero de operacoes

Matriz* cria_Matriz()
{//retorna um ponteiro para o comeco da matriz
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
    if(li == NULL) return ERRO; //lista nao foi criada

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
        Elem *aux; //ultimo no da linha
        aux = *li;

        while (aux->j != j-1){ aux = aux->direita;}//seleciona aux

        aux->direita = no;
        no->esquerda = aux;
        no->acima = NULL; //nenhum elemento acima pois eh a primeira linha
    }
    else //demais elementos
    {
        Elem *aux; //elemento na linha do novo e um espaco a esquerda
        aux = *li;

        while (aux->i != i){ aux = aux->abaixo;} //seleciona a linha do novo elemento
        while (aux->j != j-1){ aux = aux->direita;} //seleciona o elemento imediatamente a esquerda

        aux->direita = no;
        no->esquerda = aux;

        Elem *temp; //elemento imediatamente acima do novo
        temp = *li;

        while (temp->i != i-1){ temp = temp->abaixo;} //seleciona a linha acima do novo elemento
        while (temp->j != j){ temp = temp->direita;}  //seleciona a coluna do novo elemento

        temp->abaixo = no;
        no->acima = temp;

    }

    return OK;

}

void imprime_Matriz(Matriz *li)
{//percorre as linhas da esquerda para a direita
    Elem *linha = *li;
    Elem *no;

    if(li == NULL) return;

    while(linha != NULL) //imprime as linhas
    {
        no = linha;
        while (no != NULL) //imprime as colunas
        {
            printf("%d ", no->info);
            no = no->direita;
        }
        printf("\n");
        linha = linha->abaixo;
    }
}


void flood_fill(Lista* li, Matriz*mi, Elem* no, int i, int j, int visitado[i][j])
{
    cont ++;
    visitado[no->i][no->j] = TRUE; // marca a coordenda como ja visitada

    cont ++;
    if (no == NULL)
        return;
    
    cont ++;
    Elem* aux = no;

    cont ++;
    if (no->info == 0)
        printf ("1 nao encontrado\n");
    else {
        insere_lista_ordenada (li, no->i, no->j);

        // os if's a seguir verifica se a coordenda  esta na fronteira da matriz e se ha algum 1 em torno de si
        cont += 4;
        if ((no->esquerda) != NULL && (no->acima) != NULL  && ((no->esquerda)->acima)->info == 1 && visitado[(no->esquerda)->acima->i][(no->esquerda)->acima->j] != TRUE) { //canto superior esquerdo
            aux = (no->esquerda)->acima;
            cont ++;
            flood_fill(li, mi, aux, i, j, visitado);
        }

        cont += 3;
        if ((no->acima) != NULL  && (no->acima)->info == 1 && visitado[(no->acima)->i][(no->acima)->j] != TRUE) { //posicao acima
            aux = no->acima;
            cont ++;

            flood_fill(li, mi, aux, i, j, visitado);
        }


        cont += 4;
        if ((no->direita) != NULL && (no->acima) != NULL && ((no->direita)->acima)->info == 1 &&  visitado[((no->direita)->acima)->i][((no->direita)->acima)->j] != TRUE) { //canto superior direito
            aux = (no->direita)->acima;
            cont ++;

            flood_fill(li, mi, aux, i, j, visitado);
        }


        cont += 3;
        if ((no->esquerda) != NULL && (no->esquerda)->info == 1 && visitado[(no->esquerda)->i][(no->esquerda)->j] != TRUE) { //posicao esquerda
            aux = no->esquerda;
            cont ++;
            flood_fill(li, mi, aux, i, j, visitado);
        }


        cont += 3;
        if ((no->direita) != NULL  && (no->direita)->info == 1 && visitado[(no->direita)->i][(no->direita)->j] != TRUE){ //posicao direita
            aux = no->direita;
            cont ++;

            flood_fill(li, mi, aux, i, j, visitado);
        }


        cont += 4;
        if ((no->esquerda) != NULL && (no->abaixo) != NULL && ((no->esquerda)->abaixo)->info == 1 && visitado[((no->esquerda)->abaixo)->i][((no->esquerda)->abaixo)->j] != TRUE){ //canto inferior esquerdo
            aux = (no->esquerda)->abaixo;
            cont ++;

            flood_fill(li, mi, aux, i, j, visitado);
        }


        cont += 3;
        if ((no->abaixo) != NULL  && (no->abaixo)->info == 1 && visitado[(no->abaixo)->i][(no->abaixo)->j] != TRUE) {//posicao abaixo
            aux = no->abaixo;
            cont ++;

            flood_fill(li, mi, aux, i, j, visitado);
        }


        cont += 4;
        if ((no->direita) != NULL && (no->abaixo) != NULL && ((no->direita)->abaixo)->info == 1 && visitado[((no->direita)->abaixo)->i][((no->direita)->abaixo)->j] != TRUE){ //canto inferior direito
            aux = (no->direita)->abaixo;
            cont ++;

            flood_fill(li, mi, aux, i, j, visitado);
        }

    }
}

int RetornaCont ()
{
    return cont;
}