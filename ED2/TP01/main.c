#include <stdio.h>
#include <stdlib.h>

#include "Matriz.h"

int main ()
{
    Matriz *li = cria_Matriz();

    int i, j, info;

    for ( i = 0; i < 10; i++)
    {
        for ( j = 0; j < 10; j++)
        {
            info = j>i ? 1:0;
            insere_Matriz(li, i, j, info);
        }
        
    }

    imprime_Matriz(li);
    system("pause");
    libera_Matriz(li);

    return 0;
    
}