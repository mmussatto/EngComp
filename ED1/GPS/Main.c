#include <stdio.h>
#include <stdlib.h>
#include "LDED.h"
#include"GPS.h"


int main ()
{
    Lista *li = cria_lista();
    int n, i;
    double lat, lon;

    int entrada;
    double dist_cobertura, vel_max; //utilizados no modo 1

    double dist_max; //usada no modo 2

    scanf("%d", &n); //le numero de entradas 
    for ( i = 0; i < n; i++)
    {
        scanf("%lf %lf", &lat, &lon);
        insere_lista_final(li, lat, lon, i); //insere os dados nas entradas 
    }

    for ( i = 0; i < n; i++)
    {
        insere_dist(li, i); //insere a dsitancia percorrida para cada entrada 
        insere_velo(li, i); //insere a velociadade para cada entrada
    }

    scanf("%d", &n); //le modo de execucao

    switch (n)
    {
    case 0: //imprime
        imprime_lista(li);
        break;

    case 1: //radar

        scanf("%d", &entrada);
        scanf("%lf", &dist_cobertura);
        scanf("%lf", &vel_max);

        
        radar(li, entrada, dist_cobertura, vel_max);

        break;

    case 2:  // simplificacao de caminho
    
        scanf("%lf", &dist_max);
        
        simplifica_trajeto(li, dist_max);
        
        imprime_lista(li);
    
    default:
        
        break;
    }

    libera_lista(li);
    system("pause");
    return 0; 
}
