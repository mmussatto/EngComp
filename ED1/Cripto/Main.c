/*
|   SSC0603 Estrutura de Dados I
|   Trabalho 1: Criptografia com Chave Simétrica
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
|
|   Data: 09/2019
*/


#include <stdio.h>
#include <stdlib.h>
#include "LDES.h"
#include "Criptograf.h"

int main ()
{
    int modo_execucao; // 0 encriptar ; 1 decriptar 
    int verifica = 0; //verifica se tudo foi lido corretamente 
    int tam_msg_original; //tamanho original da mensagem
    int tam_msg_final; //tamanho final da mensagem 
    int lixo;

    Lista *li_msg;
    Lista *li_chave;

    scanf("%d", &modo_execucao); //le o modo de execucao (0 ou 1)
    //printf("Modo: %d \n", modo_execucao);
    scanf("%d", &lixo);
    //fflush(stdin);

    if(modo_execucao == 0)
    {
        do
        {
            li_msg = cria_lista();//cria lista de mensagen  
            verifica = le_caracteres(li_msg); //retorna 1 caso tenha lido tudo certo e 0 caso nao tenha
        } while (verifica == 0); //para caso algum caracter invalido seja digitado
        
        verifica = 0; // reseta a verficacao;

        do
        {
            li_chave = cria_lista();   
            verifica = le_caracteres(li_chave);
        } while (verifica == 0);

        tam_msg_original = tamanho_lista(li_msg); //guarda o tamanho original da mensagem

        int deslocamento = calcula_deslocamento(li_chave); //calcula o deslocamento
        //printf("Desloc: %d\n", deslocamento);

        int tam_intervalo = tamanho_lista(li_chave);
        int intervalos[tam_intervalo]; //cria um vetor com o tamanho da chave
        calcula_intervalo(intervalos, li_chave, deslocamento); //define valores pro vetor intervalo
        //for(int i=0;i<7;i++){printf("Inter: %d\n", intervalos[i]);}
        
        insere_no(li_chave, li_msg, intervalos); //insere nos na mensagem

        //imprime_lista(li_msg);
        //printf("\n\n");
        cifra_cesar(li_msg, deslocamento); //aplica a cifra de cesar 

        tam_msg_final = tamanho_lista(li_msg);//guarda o tamanho final da mensagem 

        printf("%d\n%d\n",tam_msg_original, tam_msg_final); //imprime os tamanhos
        imprime_lista(li_msg); //imprime a mensagem incriptada 
        //imprime_lista(li_chave);
        

        libera_lista(li_msg);
        libera_lista(li_chave);

        //system("pause");
    }

    else if (modo_execucao == 1)
    {
        do
        {
            li_msg = cria_lista();//cria lista de mensagen   
            verifica = le_caracteres(li_msg); //retorna 1 caso tenha lido tudo certo e 0 caso nao tenha
        } while (verifica == 0); //para caso algum caracter invalido seja digitado
        
        verifica = 0; // reseta a verficacao;

        do
        {
            li_chave = cria_lista();   
            verifica = le_caracteres(li_chave);
        } while (verifica == 0);

        tam_msg_original = tamanho_lista(li_msg); //guarda o tamanho original da mensagem

        int deslocamento = calcula_deslocamento(li_chave); //calcula o deslocamento

        cifra_cesar_reversa(li_msg, deslocamento);

        int intervalos[tamanho_lista(li_chave)]; //cria um vetor com o tamanho da chave
        calcula_intervalo(intervalos, li_chave, deslocamento); //define valores pro vetor intervalo

        remove_no(li_chave, li_msg, intervalos);//remove os nos da chave

        tam_msg_final = tamanho_lista(li_msg);//guarda o tamanho final da mensagem

        printf("%d\n%d\n",tam_msg_original, tam_msg_final); //imprime os tamanhos
        imprime_lista(li_msg);     

        libera_lista(li_msg);
        libera_lista(li_chave);

        //system("pause");   
    }

    else
    {
        printf(" Caracter invalido\n 0 - encriptar\n 1- decriptar");
        //system("pause");
    }

    return 0;
}
