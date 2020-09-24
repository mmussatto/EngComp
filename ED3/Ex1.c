/* This code will read the name of a .csv file, open it and check the information inside.
    I will then print out the names or ids of the people who are 18 or older.

    An exemple of input would be:

    ID-DO-USUARIO,NOME,IDADE
    1,Joao,30
    2,,15
    3,Maria,28
    4,,24
    5,Jose,56
    6,Leticia,10

*/

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char nome_arq[20]; //guarda o nome do arquivo

    int id;        //guarda id
    char nome[20]; //guarda nome
    int idade;     //guarda idade

    int nome_nvazio; //olha se o campo nome nao esta vazio
    int byte_final;  //ultimo byte do arquivo
    int byteoffset;  


    scanf("%s", nome_arq);
    FILE *arq = fopen(nome_arq, "r"); 
    if (arq == NULL){//deu ruim
        printf("Nao foi possivel abrir o arquivo!\n");
        return 0;
    }
    
    fseek(arq,-1, SEEK_END); //coloca o ponteiro na ultimo byte que sera lido
    byte_final = ftell(arq); //guarda o ultimo byte que sera lido
    fseek(arq,0,SEEK_SET);   //retorna o ponteiro para o inicio

    fscanf(arq, "%*s[^\n]"); //ignora a primeira linha com a descricao dos campos

    while(byteoffset != byte_final)
    {//roda enquanto nao chegar no final do arquivo
        
        fscanf(arq, "%d", &id);
        getc(arq); //ignora a virgula
        nome_nvazio = fscanf(arq, "%[^,]s", nome);
        getc(arq); //ignora a virgula
        fscanf(arq, "%d[^,]", &idade);

        if(idade >= 18)
        {
            if (nome_nvazio == 1)
            {//nome nao esta vazio
                printf("O usuario %s eh de maior.\n", nome);
            }
            else
            {//nome esta vazio
                printf("O usuario de identificacao %d eh de maior.\n", id);
            }
            
        }
        byteoffset = ftell(arq); //seta o byte atual
    }


    fclose(arq);
    return 0;
}