/* This code will read the name of a .bin file, open it and check the information inside.
    I will then print out the names or ids of the people who are 18 or older.

    An exemple of input would be:

    caso1.bin

======== caso1.bin ========================
    ID-DO-USUARIO,NOME,IDADE
    1,Joao,30
    2,,15
    3,Maria,28
    4,,24
    5,Jose,56
    6,Leticia,10
==========================================

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    char nome_arq[20]; //guarda o nome do arquivo

    int id;        //guarda id
    char nome[50]; //guarda nome
    int idade;     //guarda idade

    scanf("%s", nome_arq); //le nome arquivo
    FILE *arq = fopen(nome_arq, "rb"); 
    if (arq == NULL){//deu ruim
        printf("Nao foi possivel abrir o arquivo!\n");
        return 0;
    }

    while(fread(&id,sizeof(int),1,arq) != 0)
    {
        fread(nome,sizeof(char),50,arq); //le nomw
        fread(&idade,sizeof(int),1,arq); //le idade

        if (idade >= 18)
        {
            if (strlen(nome) != 0)
            {//nome nao vazio
                printf("O usuario %s eh de maior.\n", nome);
            }
            else
            {//nome esta vazio
                printf("O usuario de identificacao %d eh de maior.\n", id);
            }
            
        }
        
    }

    fclose(arq);
    return 0;
}