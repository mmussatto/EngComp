#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED



#endif // HASH_H_INCLUDED

#define OK         1
#define ERRO       0


struct elemento
{
    char str[6];
    char str_ordenada[6];
    struct elemento *prox;
};

typedef struct elemento Elem;

void cria_tabela(Elem* tabela[],int TABLE_SIZE);

void libera_tabela(Elem* tabela[],int TABLE_SIZE);

void imprime_tabela(Elem* tabela[],int TABLE_SIZE);

int funcao_hash(char v[], int TABLE_SIZE);

int funcao_rehash (int i, char str[], int TABLE_SIZE);

int insere_tabela_ordenada(Elem* tabela[], char str[], char ord[], int TABLE_SIZE);

void Ordenada_String(char v[], int T);
