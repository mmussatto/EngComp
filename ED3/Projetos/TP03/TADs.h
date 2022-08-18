#pragma once

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