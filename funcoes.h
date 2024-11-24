#ifndef FUNCOES_H
#define FUNCOES_H

#include <math.h>

typedef struct {
    double x, y;
} Ponto;

double distanciaOrigem(Ponto p);
void ordenarPontos(Ponto pontos[], int n);
double calcularDistanciaTotal(Ponto pontos[], int n);
double calcularShortcut(Ponto pontos[], int n);
void testarPrograma(); 

#endif
