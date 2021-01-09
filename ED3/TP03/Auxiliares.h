/*
|   SCC0607 Estrutura de Dados III
|   Trabalho Pratico 03
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
*/

#pragma once

#include "funcionalidades.h"
#include "TADs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char lixo; //variavel externa usada por diferentes arquivos .c


void Altera(dados *busca, dados *muda, int caso, int *muda_campo, FILE *f_pessoa, indice *index, int size_index);

void Print(int id, char *nome, int idade, char *twitter);
void PrintSegue(segue d);   //TP02
void Print_Indice(indice *index, int size_index);

int RecuperaIndice(FILE *f_index, indice **index);
void RecuperaSegue(FILE *f_segue, segue **d_segue, int size_segue); //TP02
const char* RecuperaNome(FILE *f_pessoa, indice *index, int size_index,  int id);  //TP03

void EscreveRegistro(dados *pessoa, FILE *f_pessoa);
void EscreveRegistroSegue(segue *d_segue, FILE *f_segue);   //TP02
void MudaCampos(dados *busca, dados *muda, int *muda_campo, indice *index, int size_index);

void Insertion_Sort(indice *v, int n);
int BuscaBinaria(indice *index, int size_index, int idBuscado);
int BuscaBinaria_Segue(segue *d_segue, int qtdSeguidores, int idBuscado);   //TP02

int Comparador (const void *x, const void *y);  //TP02