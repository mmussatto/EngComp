#pragma once
#define OK         1
#define ERRO       0

typedef int Tipo_Dado;

struct elemento 
{
    int i, j; //coordenadas do elemento
    Tipo_Dado info;
    struct elemento *acima;
    struct elemento *direita;
    struct elemento *esquerda;
    struct elemento *abaixo;
};

typedef struct elemento Elem;

typedef struct elemento* Matriz;

//------------------------------------

Matriz* cria_Matriz();
void libera_Matriz(Matriz *li);
int insere_Matriz (Matriz *li, int i, int j, Tipo_Dado info);
void imprime_Matriz();