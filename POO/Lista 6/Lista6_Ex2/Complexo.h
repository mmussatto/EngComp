/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Complexo.h
 * Author: Murilo Mussatto
 *
 * Created on October 23, 2020, 6:22 PM
 */

#ifndef COMPLEXO_H
#define COMPLEXO_H

class Complexo {
private:
    double real;
    double img;
public:
    Complexo(double real, double img);
    Complexo Soma(Complexo y);
    Complexo Subtracao(Complexo y);
    Complexo Multiplicacao(Complexo y);
    double Modulo();
    void Imprime();
    virtual ~Complexo();

};

#endif /* COMPLEXO_H */

