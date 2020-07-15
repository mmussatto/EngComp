#include <stdio.h>
#include <stdlib.h>

#include "ArvBin.h" 



ArvBin* cria_ArvBin(){

    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));

    if(raiz != NULL)
        *raiz = NULL;

    return raiz;
}

void libera_NO(struct NO* no)
{       
    if(no == NULL){ return;}

    libera_NO(no->esq);  //<----- recursive
    libera_NO(no->dir);
    free(no);

    //no = NULL;  ---- Didnt really understand why
}

void libera_ArvBin(ArvBin* raiz)
{
    if(raiz == NULL) { return;}

    libera_NO(*raiz);//libera cada no
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, Tipo_Dado valor)
{
    if(raiz == NULL) return ERRO; //raiz nao criada

    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL) return ERRO;

    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL){*raiz = novo;}

    else
    {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;

        while(atual != NULL)
        {
            ant = atual;

            if(valor == atual->info) //elemento ja existe
            {
                free(novo);
                return 0;
            }

            if(valor > atual->info){atual = atual->dir;} //maiores para a direita
            else{atual = atual->esq;}
                
        }

        if(valor > ant->info){ant->dir = novo;}
        else{ant->esq = novo;}
            
    }
    return OK;
}

struct NO* remove_atual(struct NO* atual) 
{
    struct NO *no1, *no2;

    if(atual->esq == NULL) //apenas um filho (dir)
    {
        no2 = atual->dir;
        free(atual);
        return no2;
    }

    no1 = atual;
    no2 = atual->esq;

    while(no2->dir != NULL)
    {//procura o menor valor entre os filhos
        no1 = no2;
        no2 = no2->dir;
    }

    if(no1 != atual)
    {//filho da direita possui filhos
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }

    no2->dir = atual->dir;
    free(atual);

    return no2;
}

int remove_ArvBin(ArvBin *raiz, Tipo_Dado valor)
{
    if(raiz == NULL) return ERRO;

    struct NO* ant = NULL;
    struct NO* atual = *raiz;

    while(atual != NULL)
    {
        if(valor == atual->info)
        {
            if(atual == *raiz){*raiz = remove_atual(atual);}
                
            else
            {
                if(ant->dir == atual){ ant->dir = remove_atual(atual);}  

                else {ant->esq = remove_atual(atual);}         
            }
            return OK;
        }

        ant = atual;

        if(valor > atual->info){ atual = atual->dir;}
            
        else{ atual = atual->esq;}
            
    }
    return ERRO;
}

void Imprime_preOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL){ return;}
        
    if(*raiz != NULL)
    {
        printf("%dado");       //<---- mudar o tipo de dado 
        Imprime_preOrdem_ArvBin(&((*raiz)->esq));
        Imprime_preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void Imprime_emOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL){ return;}
        
    if(*raiz != NULL)
    {
        Imprime_emOrdem_ArvBin(&((*raiz)->esq));
        printf("%dado");         
        Imprime_emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void Imprime_posOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL){ return;}
        
    if(*raiz != NULL)
    {
        Imprime_posOrdem_ArvBin(&((*raiz)->esq));
        Imprime_posOrdem_ArvBin(&((*raiz)->dir));
        printf("%dado");        
    }
}

int altura_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL){ return ERRO;}
        
    if (*raiz == NULL){return ERRO;}
        
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));


    if (alt_esq > alt_dir){return (alt_esq + 1);}  

    else{ return(alt_dir + 1);}
       
}

int totalNO_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL){ return ERRO;}
        
    if (*raiz == NULL){return ERRO;}

    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    
    return(alt_esq + alt_dir + 1);
}