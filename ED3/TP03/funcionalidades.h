/*
|   SCC0607 Estrutura de Dados III
|   Trabalho Pratico 03
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
*/

#pragma once

#include "fornecido.h"
#include "Auxiliares.h"
#include "Grafo.h"
#include "TADs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/*-------------------- Funcionalidades ----------------------------------------------*/
void func1(char *arq_entrada, char *arq_pessoa, char *arq_indexa);

void func2(char *arq_pessoa);

void func3(char *arq_pessoa, char *arq_indexa, char *nome_campo);
int func3_modificada(FILE *f_pessoa, FILE *f_index, char *nome_campo, int valor, dados *d);     //TP02

void func4(char *arq_pessoa, char *arq_indexa, int n);

void func5(char *arq_pessoa, char *arq_indexa, int n);

void func6(char *arq_entrada, char *arq_segue);                                                 //TP02

void func7(char *arq_segue, char *arq_sOrdenado);                                               //TP02

void func8(char *arq_pessoa, char *arq_indexa, char *nome_campo, int n, char *arq_sOrdenado);   //TP02

void func9(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado);                            //TP03

void func10(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado);                            //TP03

void func11(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado);                            //TP03

void func12(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado);                            //TP03



