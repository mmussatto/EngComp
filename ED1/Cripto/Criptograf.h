#pragma once
#include "LDES.h"

int le_caracteres(Lista *li);
int calcula_deslocamento(Lista *li);
int calcula_intervalo(int intervalos[], Lista *li, int deslocamento);
void insere_no(Lista *li_chave, Lista *li_mensagem, int intervalos[]);
void remove_no(Lista *li_chave, Lista *li_mensagem, int intervalos[]);
void cifra_cesar(Lista *li, int deslocamento);
void cifra_cesar_reversa(Lista *li_msg, int deslocamento);
