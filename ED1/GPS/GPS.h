#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LDED.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif



double grauParaRadiano(double angulo);
double distancia(double lati1, double long1, double lati2, double long2);

void insere_dist(Lista* li, int entrada);
void insere_velo(Lista *li, int entrada);

void radar(Lista *li, int entrada, double dist_cobertura, double vel_max);
void simplifica_trajeto(Lista *li, double dist_max);