#pragma once
#define OK         1
#define ERRO       0

typedef int Tipo_Dado;

struct elemento
{
    struct elemento *ant;
    Tipo_Dado dado;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;


Lista* cria_lista();
void libera_lista(Lista* li);

void imprime_lista(Lista* li);
int tamanho_lista(Lista* li);

int insere_lista_final(Lista* li, Tipo_Dado dt);
int remove_lista_final(Lista* li);

int insere_lista_inicio(Lista* li, Tipo_Dado dt);
int remove_lista_inicio(Lista* li);