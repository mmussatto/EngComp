/*
|   SCC0607 Estrutura de Dados III
|   Trabalho Pratico 01
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
|
|   Data: 11/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include "funcionalidades.h"
#include "fornecido.h"

int main ()
{

    int funcionalidade = 0;

    char arq_entrada[30];   //f1
    char arq_pessoa[30];    //f1, f2, f3, f4  
    char arq_indexa[30];    //f1. f3, f4
    char nome_campo[30];    //f3
    int n;                  //f4, f5

    scanf("%d ", &funcionalidade);

    switch (funcionalidade)
    {
    case 1:
        scanf("%s %s %s", arq_entrada, arq_pessoa, arq_indexa);
        func1(arq_entrada, arq_pessoa, arq_indexa);
        break;
    
    case 2:
        scanf("%s", arq_pessoa);
        func2(arq_pessoa);
        break;

    case 3:
        scanf("%s %s %s", arq_pessoa, arq_indexa, nome_campo);
        func3(arq_pessoa, arq_indexa, nome_campo);
        break;
        
    case 4:
        scanf("%s %s %d", arq_pessoa, arq_indexa, &n);
        func4(arq_pessoa, arq_indexa, n);
        break;

    case 5:
        scanf("%s %s %d", arq_pessoa, arq_indexa, &n);
        func5(arq_pessoa, arq_indexa, n);
        break;
        
    default:
        break;
    }    

    return 0;
}


