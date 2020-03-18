#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBin.h"

ArvBin* cria_ArvBin()
{

    ArvBin *raiz = (ArvBin*) malloc (sizeof(ArvBin));

    if(raiz != NULL) *raiz = NULL;

    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL) return; //no nao existe

    libera_NO(no->esq);  //<----- recursive
    libera_NO(no->dir);

    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL) return; //arvore nao criada

    libera_NO(*raiz); //libera cada no
    free(raiz); //libera raiz

}

int insere_ArvBin(ArvBin *raiz, char Tipo_NO, int Ident, char *Inf, float Valor_Teste, char Pai_Tipo_No, int Pai_Ident, char conex, float Nivel_ctz)
{
    if(raiz == NULL) return 0;

    struct NO *novo;
    novo = (struct NO*) malloc (sizeof(struct NO));
    if(novo == NULL) return 0;

    novo->NO_Atual.Tipo_NO = Tipo_NO;
    novo->NO_Atual.Ident = Ident;
    strcpy(novo->Info, Inf);
    novo->Valor_Teste = Valor_Teste;
    novo->Lado_Conex = conex;
    novo->NO_Pai.Tipo_NO = Pai_Tipo_No;
    novo->NO_Pai.Ident = Pai_Ident;
    novo->Nivel_Certeza = Nivel_ctz;

    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL) *raiz = novo;
    else
    {
        struct NO *atual = *raiz;
            
        struct NO *result = NULL;
        result = Procura_NO(atual, result, Pai_Tipo_No, Pai_Ident);

        if(conex == 'E') result->esq = novo;
        if(conex == 'D') result->dir = novo;
    }
}

struct NO* Procura_NO(struct NO *NO, struct NO *result, char Tipo_NO, int Ident)
{
    if(NO == NULL) return result;

    //percorre a arvore inteira ate achar o no desejado;

    if(NO->NO_Atual.Tipo_NO == Tipo_NO && NO->NO_Atual.Ident == Ident)
    {
        result = NO;
        return result;
    }
    else
    {
        result = Procura_NO(NO->dir, result, Tipo_NO, Ident);
        if (result != NULL){return result;} //para a recursao quando acha o nodo
        
        result = Procura_NO(NO->esq, result, Tipo_NO, Ident);
        if (result != NULL){return result;} //para a recursao quando acha o nodo
    }
    
}

struct NO* Maior_Ctz(struct NO *atual, struct NO *maior_no, float *maior_ctz)
{
    if(atual == NULL) return maior_no;

    if(atual->NO_Atual.Tipo_NO == 'C' && atual->Nivel_Certeza > *maior_ctz)
    {
        maior_no = atual;
        *maior_ctz = atual->Nivel_Certeza;
    }
    
    maior_no = Maior_Ctz(atual->dir, maior_no, maior_ctz);
    maior_no = Maior_Ctz(atual->esq, maior_no, maior_ctz);

    return maior_no;
}