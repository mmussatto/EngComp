#pragma once
#define OK         1
#define ERRO       0

typedef double Tipo_Dado;

struct elemento
{
    struct elemento *ant;
    Tipo_Dado Latitude;
    Tipo_Dado Longitude;
    int Tempo;
    Tipo_Dado Velocidade;
    Tipo_Dado Dist_Percorrida;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;

//---------------------------------------------------

Lista* cria_lista();
void libera_lista(Lista* li);
void imprime_lista(Lista* li);
//int tamanho_lista(Lista* li);

int insere_lista_final(Lista* li, Tipo_Dado lati, Tipo_Dado longi, int tempo);
//int remove_lista_final(Lista* li);

//int insere_lista_inicio(Lista* li, Tipo_Dado dt);
//int remove_lista_inicio(Lista* li);

//int consulta_lista_pos(Lista* li, int pos, Tipo_Dado *dt);
//int consulta_lista_dado(Lista* li, Tipo_Dado dt, Elem **el);
