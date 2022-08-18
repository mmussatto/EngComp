
#pragma once

#include "fornecido.h"
#include <stdio.h>

/*Cabecalho do arquivo de dados*/
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

/*Registro do arquivo de dados*/
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



/*Funcionalidades*/
void func1(char *arq_entrada, char *arq_pessoa, char *arq_indexa);
void func2(char *arq_pessoa);
void func3(char *arq_pessoa, char *arq_indexa, char *nome_campo);
void func4(char *arq_pessoa, char *arq_indexa, int n);
void func5(char *arq_pessoa, char *arq_indexa, int n);


/*Funcoes Auxiliares*/

void Altera(dados *busca, dados *muda, int caso, int *muda_campo, FILE *f_pessoa, indice *index, int size_index);

void Print(int id, char *nome, int idade, char *twitter);

int RecuperaIndice(FILE *f_index, indice **index);
void Print_Indice(indice *index, int size_index);

void EscreveRegistro(dados *pessoa, FILE *f_pessoa);
void MudaCampos(dados *busca, dados *muda, int *muda_campo, indice *index, int size_index);

void Insertion_Sort(indice *v, int n);
int BuscaBinaria(indice *index, int size_index, int idBuscado);
