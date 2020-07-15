#pragma once

#define OK         1
#define ERRO       0

typedef int Tipo_Dado;

struct NO
{
    Tipo_Dado info;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO NodoArvBin;
typedef struct NO *ArvBin;


ArvBin* cria_ArvBin();
void libera_NO(struct NO* no);
void libera_ArvBin(ArvBin *raiz);

int insere_ArvBin(ArvBin* raiz, Tipo_Dado valor);

struct NO* remove_atual(struct NO* atual);
int remove_ArvBin(ArvBin *raiz, Tipo_Dado valor);

void Imprime_preOrdem_ArvBin(ArvBin *raiz);
void Imprime_emOrdem_ArvBin(ArvBin *raiz);
void Imprime_posOrdem_ArvBin(ArvBin *raiz);

int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
