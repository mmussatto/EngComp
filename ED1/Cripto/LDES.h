#pragma once
#define OK         1
#define ERRO       0

typedef char tipo_dado;

struct elemento
{
    tipo_dado dado;
    struct elemento *prox;
};

typedef struct elemento Elem;
typedef struct elemento* Lista;

Lista* cria_lista ();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, tipo_dado dt);
int insere_apos(Elem *no_msg, Elem *no_chave, int contador);
int remove_apos(Elem *no_msg, int contador);
void imprime_lista(Lista* li);
int tamanho_lista(Lista* li);

