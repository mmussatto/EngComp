/*
|   SCC0607 Estrutura de Dados III
|   Trabalho Pratico 03
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
*/

#pragma once

#include "TADs.h"
#include "Auxiliares.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo
{
    int id;
    char nome[40];
    struct nodo *adj;
    struct nodo *prox;
    
};
typedef struct nodo Nodo;
typedef struct nodo* Lista;

struct grafo
{
    int V;
    int A;
    Lista *li;
};
typedef struct grafo Grafo;



void criaGrafo(Grafo *g, int v);

void liberaGrafo(Lista *li);

void imprimeGrafo(Grafo *g);

void imprimeCeleb(Grafo *g, int ordem[]);

void controiGrafo(Grafo *g, FILE *f_pessoa, FILE *f_index, FILE *f_segue, int qtdSeguidores);

void controiGrafoT(Grafo *g, FILE *f_pessoa, FILE *f_index, FILE *f_segue, int qtdSeguidores);

void insereAresta(Grafo *g, const char segue[], const char seguida[]);

int buscaID(Grafo *g, char nome[]);

void OrdenaID(Grafo *g);

void BFS(Grafo *g, char celebridade[], int *ordem);

int DFS(Grafo *g, int id, int *visitados);


void teste();


