/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Complexo.h
 * Author: Murilo
 *
 * Created on October 23, 2020, 6:58 PM
 */

#ifndef COMPLEXO_H
#define COMPLEXO_H

class Complexo {
private:
    double real;
    double img;
public:
    Complexo(double real, double img);
    Complexo operator+(Complexo y);
    Complexo operator-(Complexo y);
    Complexo operator*(Complexo y);
    double operator!();
    void Imprime();
    virtual ~Complexo();

};

#endif /* COMPLEXO_H */

