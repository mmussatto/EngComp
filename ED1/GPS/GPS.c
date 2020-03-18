#include "GPS.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double grauParaRadiano(double angulo)
{
    return (angulo * M_PI) / 180.0;
}

double distancia(double lati1, double long1, double lati2, double long2)
{
    double diferencaLatitude = grauParaRadiano(lati1 - lati2);
    double diferencaLongitude = grauParaRadiano(long1 - long2);
    double a = pow(sin(diferencaLatitude / 2.0), 2.0) + cos(grauParaRadiano(lati2)) * cos(grauParaRadiano(lati1)) * pow(sin(diferencaLongitude / 2.0), 2.0);
    return 6378137.0 * (2.0 * atan2(sqrt(a), sqrt(1.0 - a)));
}

void insere_dist(Lista* li, int entrada)
{
    if (li == NULL) return;

    int i;
    Elem *no = *li; 
    Elem *aux = *li;

    for(i=0; i < entrada; i++) //move o ponteiro no ate a entrada desejada
    {
        no = no->prox;
    }
    no->Dist_Percorrida = 0;  //distacia se torna inicialmente zero para poder usar +=

    if(no->ant != NULL) //se o anterior for null, a distancia continua zero
    {
        no->Dist_Percorrida = no->ant->Dist_Percorrida; //adiciona a distacia da ultima entrada
        no->Dist_Percorrida += distancia(no->ant->Latitude, no->ant->Longitude, no->Latitude, no->Longitude); 
    }

}

void insere_velo(Lista *li, int entrada)
{
    if (li == NULL) return;

    int i;
    Elem *no = *li;

    for(i=0; i < entrada; i++)//move o ponteiro no ate a entrada desejada 
    {
        no = no->prox;
    }

    if(no->ant == NULL){no->Velocidade = 0;} //entrada 0
    else{no->Velocidade = no->Dist_Percorrida - no->ant->Dist_Percorrida;} //velocidade = diferenca das distancias 
}

void radar(Lista *li, int entrada, double dist_cobertura, double vel_max)
{
    if(li == NULL) return;

    int i;
    double dist_analisada = 0, maior_vel = 0;
    Elem *radar = *li;

    for ( i = 0; i < entrada; i++) //move o ponteiro radar ate onde realmente esta o radar
    {
        radar = radar->prox;
    }

    if(radar->Velocidade > vel_max){maior_vel = radar->Velocidade;} //caso tenha ultrapassado o limite onde esta o radar 

    Elem *aux = radar;

    while(dist_analisada < dist_cobertura) //checagem das entradas anteriores
    {
        aux = aux->ant;
        if(aux == NULL){break;} //fim da lista
        dist_analisada = radar->Dist_Percorrida - aux->Dist_Percorrida; 
        if(dist_analisada > dist_cobertura){break;} //passou da cobertura do radar
        if(aux->Velocidade > vel_max && aux->Velocidade > maior_vel){maior_vel = aux->Velocidade;}
    }
    
    dist_analisada = 0; //reseta a distancia analisada
    aux = radar;//reseta o ponteiro auzx

    while(dist_analisada < dist_cobertura) //checagem das entradas anteriores
    {
        aux = aux->prox;
        if(aux == NULL){break;} //fim da lista 
        dist_analisada = aux->Dist_Percorrida - radar->Dist_Percorrida;
        if(dist_analisada > dist_cobertura){break;} //passou da cobertura do radar
        if(aux->Velocidade > vel_max && aux->Velocidade > maior_vel){maior_vel = aux->Velocidade;}
    }

    if (maior_vel != 0)
    {
        printf("autuado\n");
        printf("%.6lf", maior_vel);
    }
    else
    {
        printf("liberado");
    }
    
    

}

void simplifica_trajeto (Lista *li, double dist_max)
{
    if(li == NULL) return;

    Elem *inicio = *li; //comeco da lista
    Elem *fim = *li; //vai ficar no fim da lista
    while(fim->prox != NULL){fim = fim->prox;}

    Elem *no_esq = inicio; //comeco da lista
    Elem *no_dir = fim; //vai ficar no fim da lista
    double Dist_esq = 0, Dist_dir = 0;

    Elem *no;


    while(fim->Dist_Percorrida - inicio->Dist_Percorrida > dist_max)
    {
        

        no_esq = no_esq->prox; //comeca o algoritimo pelo lado esquerdo
        Dist_esq += no_esq->Dist_Percorrida - no_esq->ant->Dist_Percorrida;

        while(Dist_esq < dist_max || Dist_dir < dist_max)
        {

            if (no_dir == no_esq){break;} //encontrao
            

            if(Dist_esq < Dist_dir)
            {
                Dist_esq += no_esq->prox->Dist_Percorrida - no_esq->Dist_Percorrida;
                if(Dist_esq >= dist_max) break;
                no_esq = no_esq->prox;
            }

            else if(Dist_dir < Dist_esq)
            {
                Dist_dir += no_dir->Dist_Percorrida - no_dir->ant->Dist_Percorrida;
                if(Dist_dir >= dist_max) break;
                no_dir = no_dir->ant;
            }
        }

        no = inicio;

        while(no->prox != no_esq) //libera nos do lado esquerdo
        {

            if (no == no_esq){break;}


            no = no->prox; //no na proxima entrada
            no->ant->prox = no->prox;
            no->prox->ant = no->ant;

            free(no);

            no = inicio; //no na entrada 1   
        }

        no = fim; //coloca o no no fim da lista
        while(no->ant != no_dir)
        {

            if (no == no_dir){break;}
            
            no = no->ant; //no na penultima entrada
            no->ant->prox = no->prox;
            no->prox->ant = no->ant;

            free(no);

            no = fim; //no no fim da lista 

        }

        inicio = no_esq;
        fim = no_dir; 
        Dist_dir = 0; Dist_esq = 0;
    }

    while(inicio->prox != fim)
    {
        if(inicio == fim){break;}
        no = inicio->prox;
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;

        free(no);

        no = inicio;
    }

    
}