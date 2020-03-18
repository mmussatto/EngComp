#include <stdio.h>
#include <stdlib.h>
#include "Criptograf.h"

int le_caracteres(Lista *li)
{
    char aux;
    //fflush(stdin);
    while (scanf("%c", &aux) == 1 && aux != 10) //le as letras da chave ate o /n ('/n' = 10)
    {
        if(aux == 32){continue;} // ignora espacos (' ' = 32)
        //printf("Leu: %c \n", aux);
        if(aux >= 97 && aux <= 122){insere_lista_final(li, aux);} //aceita apenas letras
        else
        {
            printf("ERRO!! Caracter invalido na chave\n");
            libera_lista(li); //reseta a lista
            return 0;
        }
    }
    return 1;
}

int calcula_deslocamento(Lista *li) //apendice a
{
    int desloca = 0;
    Elem *no = *li;

    while(no != NULL)
    {
        desloca = desloca ^ no->dado;
        no = no->prox;
    }
    
    return (desloca % 26);
}

int calcula_intervalo(int intervalos[], Lista *li, int deslocamento) //apendice a
{
    int i = 0;
    Elem *no = *li;
    while(no != NULL)
    {
        intervalos[i] = (no->dado - 97) ^ deslocamento;
        no = no->prox;
        i++;
    }
}

void insere_no(Lista *li_chave, Lista *li_mensagem, int intervalos[]) //apendice a
{
    int contador_intervalo = 0;
    int seletor_intevalo = 0;
    Elem *no_chave = *li_chave;
    Elem *no_mensagem = *li_mensagem;

    while(no_mensagem != NULL) //ate o fim da mensagem
    {
        if(contador_intervalo >= intervalos[seletor_intevalo % tamanho_lista(li_chave)]) //numero de nos avancados na mensagem igual ao valor do intervalo
        {
            if(insere_apos(no_mensagem, no_chave, contador_intervalo) == 0){break;} //insere um no contendo o dado do respectivo caracter da chave, Caso retorne 0, a mensagem chegou ao fim
            seletor_intevalo++; //avanca no vetor de intervalos
            no_chave = no_chave->prox; //avanca para a proxima letra da chave
            for (int i = 0; i <= contador_intervalo; i++){no_mensagem = no_mensagem->prox;}//avanca o contador de intervalos na mensagem
            contador_intervalo = 0; //reseta o avanco na mensagem
            if(no_chave == NULL){no_chave = *li_chave;}//recomce a chave
        }
        contador_intervalo++;
    }
}

void remove_no(Lista *li_chave, Lista *li_mensagem, int intervalos[])
{
    int contador_intervalo = 0;
    int seletor_intevalo = 0;
    Elem *no_mensagem = *li_mensagem;

    while(no_mensagem != NULL)
    {
        if(contador_intervalo >= intervalos[seletor_intevalo % tamanho_lista(li_chave)])
        {
            if(remove_apos(no_mensagem, contador_intervalo) == 0){break;} //remove um no apos um intervalo. Retorna 0 caso a mensgame tenha acabdo
            for (int i = 1; i <= contador_intervalo; i++){no_mensagem = no_mensagem->prox;}//avanca o contador de intervalos na mensagem
            contador_intervalo = 0; //reseta o avanco na mensagem
            seletor_intevalo++; //avanca no vetor de intervalos
        }
        contador_intervalo++;
    }
}

void cifra_cesar(Lista *li, int deslocamento) //apendice a 
{
    Elem *no = *li;
    while (no != NULL)
    {
        no->dado = (((no->dado - 97) + deslocamento) % 26) + 97;
        deslocamento ++;
        no = no->prox;
    }
}

void cifra_cesar_reversa(Lista *li_msg, int deslocamento)
{
    char aux_caractere;
    int aux_desloc = deslocamento;
    Elem *no = *li_msg;

    while (no != NULL)
    {
        aux_caractere = (no->dado - 97) - (aux_desloc % 26);

        if(aux_caractere < 0){no->dado = aux_caractere + 26 + 97;}
        else{no->dado = aux_caractere + 97;}
        no = no->prox;
        aux_desloc++;
    }

}
