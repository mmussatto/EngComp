#pragma once

struct coordenada{
    int linha;
    int coluna;
    struct coordenada *prox;
};

typedef struct coordenada Coord;
typedef struct coordenada* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_ordenada(Lista* li, int cordx, int cordy);
void imprime_lista(Lista* li);
int tamanho_lista(Lista* li);
