#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBin.h"

int main()    
{
    ArvBin *raiz = cria_ArvBin();
    int i, entradas;
    int j;

    char Tipo_NO; //letra do indice
    int Ident; //numero do indice 
    char aux[30]; //auxiliar para montar a informacao  
    char Info[100]; //vetor que guarda a informacao do nodo
    float Valor_Teste; 
    float Nivel_Certeza;
    Indice Pai; //struct que possui Tipo_NO e Ident do pai
    char conex; //lado onde o nodo sera pendurado


    scanf("%d", &entradas); //numero de nodos da arvore

    for(i=0; i < entradas ; i++)
    { //construcao da arvore
        fflush(stdin);

        scanf(" %c%d", &Tipo_NO, &Ident); //indice do nodo

        scanf("%s", Info);
        if(Info[strlen(Info)-1] != '"')
        {//ler a proxima palavra no aux e contatenar na info ate o ultimo char ser aspas duplas
            do{
                strcat(Info, " ");
                scanf("%s", aux);
                strcat(Info, aux);
            }while(aux[strlen(aux)-1] != '"'); 
        }
        
        if(Tipo_NO == 'N')
        {//no numerico
            scanf("%f", &Valor_Teste);
        }
        else {Valor_Teste = 0;}

        scanf(" %c%d", &Pai.Tipo_NO, &Pai.Ident);

        if(Pai.Tipo_NO != 'R') scanf(" %c", &conex);//le o lado da conexao caso o pai nao seja raiz

        if(Tipo_NO == 'C') scanf("%f", &Nivel_Certeza);
        else{Nivel_Certeza = 0;}

        
        Info[strlen(Info)-1] = '\0';//retira as aspas da mesagem
        j = 0;
        while (j <= strlen(Info)-1)
        {
            Info[j] = Info[j+1];
            j++;
        }

        insere_ArvBin(raiz, Tipo_NO, Ident, Info, Valor_Teste, Pai.Tipo_NO, Pai.Ident, conex, Nivel_Certeza);
    }

    scanf("%d", &entradas);

    struct NO *atual = *raiz; //guardar a posicao na arvore
    char existe; //guardar se a informacao existe
    char resp; //guardar a resposta 
    int fim; //fim do loop
    float salario = 0; //guardar o salario 
    struct NO *ctz = NULL; //guarda o no com maior certeza d
    float *maior_ctz = (float*)malloc(sizeof(float));//guardar o maior nivel de certeza

    for(i=0; i < entradas ; i++)
    { //entradas do usuario 
        while(fim == 0)
        { //cada ciclo representa uma das entradas

            scanf(" %c", &existe);
            
            if(existe == 'E') //informacao existe 
            {
                if (atual->NO_Atual.Tipo_NO != 'N'){scanf(" %c", &resp);} //nodo binario 
                else{scanf(" %f", &salario);} //nodo numerico

                if(atual->NO_Atual.Tipo_NO != 'N')
                {//no binario
                    if(resp == 'V'){atual = atual->esq;} //verdadeira desce pela esquerda
                    else{atual = atual->dir;} //falso desce pela direita
                }
                else
                {//no numerico
                    if(salario < atual->Valor_Teste){atual =atual->esq;}
                    else{atual = atual->dir;}
                }
                
                if(atual->NO_Atual.Tipo_NO == 'C') 
                {//ve se e no do tipo folha
                    fim = 1;//finaliza o loop while
                    printf("%s\n",atual->Info);
                }
            }

            else //informacao nao existe
            {
                *maior_ctz = 0; //reseta a maior certeza 
                ctz = Maior_Ctz(atual, ctz, maior_ctz); //retorna o nodo com maior certeza
                fim = 1; //termina o loop while
                printf("%s\n",ctz->Info);

            }
            
        }

        fim = 0; //reseta o looping while
        atual = *raiz;//reseta a arvore
    }
    
    //system("pause");
    free(maior_ctz);
    libera_ArvBin(raiz);
    return 0;

}