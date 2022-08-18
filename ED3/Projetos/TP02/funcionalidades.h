/*
|   SCC0607 Estrutura de Dados III
|   Trabalho Pratico 02
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
*/

#pragma once

#include "fornecido.h"
#include <stdio.h>

#define TAM_REGISTRO_PESSOA 64
#define TAM_REGISTRO_INDICE 8
#define TAM_REGISTRO_SEGUE 32

/*---------------------- Cabeçalhos -------------------------------------*/
/*Cabecalho do arquivo de dados Pessoa*/
struct cabecalho_dados
{
    char status;    //status do arquivo de dados
    int qtdPessoas; //quantidade de pessoas no arquivo de dados
};
typedef struct cabecalho_dados cabecalho_dados;

/*Cabecalho do arquivo de indice primario*/
struct cabecalho_index
{
    char status;    //status do arquivo de indice primario
};
typedef struct cabecalho_index cabecalho_index;

/*Cabecalho do arquivo de dados Segue*/
struct cabecalho_segue
{
    char status;        //status do arquivo de dados segue
    int qtdSeguidores;  //quantidade de seguidores
};
typedef struct cabecalho_segue cabecalho_segue;

/*---------------------- Registros de Dados --------------------------------*/
/*Registro do arquivo de dados Pessoa*/
struct dados
{
    char removido;          //flag de registro removido
    int idPessoa;           //identificacao da pessoa
    char nomePessoa[40];    //nome da pessoa
    int idadePessoa;        //idade da pessoa
    char twitterPessoa[15]; //twitter da pessoa
};
typedef struct dados dados;

/*Resgistro do arquivo de indice*/
struct indice
{
    int idPessoa;   //identificacao da pessoa
    int RRN;        //RRN onde esta armazenado o registro no arquivo de dados
};
typedef struct indice indice;

/*Registro do arquivo de dados Segue*/
struct segue
{
    char removido;          //flag de registro removido
    int idSegue;            //identificacao da pessoa que segue
    int idSeguido;          //identificacao da pessoa que eh seguida
    char grauAmizade[3];    //grau de amizade   ex: "1\0$"
    char dataInicio[11];    //data de incio que segue DD/MM/AAAA
    char dataFim[11];       //data de fim que segue DD/MM/AAAA
};
typedef struct segue segue;


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



/*--------------------- Funcoes Auxiliares -------------------------------------------*/

void Altera(dados *busca, dados *muda, int caso, int *muda_campo, FILE *f_pessoa, indice *index, int size_index);

void Print(int id, char *nome, int idade, char *twitter);
void PrintSegue(segue d);   //TP02

void Print_Indice(indice *index, int size_index);
int RecuperaIndice(FILE *f_index, indice **index);
void RecuperaSegue(FILE *f_segue, segue **d_segue, int size_segue); //TP02

void EscreveRegistro(dados *pessoa, FILE *f_pessoa);
void EscreveRegistroSegue(segue *d_segue, FILE *f_segue);   //TP02
void MudaCampos(dados *busca, dados *muda, int *muda_campo, indice *index, int size_index);

void Insertion_Sort(indice *v, int n);
int BuscaBinaria(indice *index, int size_index, int idBuscado);
int BuscaBinaria_Segue(segue *d_segue, int qtdSeguidores, int idBuscado);   //TP02

int Comparador (const void *x, const void *y);  //TP02
