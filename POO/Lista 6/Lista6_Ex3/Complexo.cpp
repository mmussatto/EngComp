/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Complexo.cpp
 * Author: Murilo
 * 
 * Created on October 23, 2020, 6:58 PM
 */

#include "Complexo.h"
#include <iostream>
#include <math.h>

Complexo::Complexo(double real, double img) {
    this->real = real;
    this->img = img;
}

Complexo Complexo::operator+(Complexo y){
    
    double c_real = this->real + y.real;
    double c_img = this->img + y.img;
    
    Complexo c(c_real, c_img);
    return c;
}

Complexo Complexo::operator-(Complexo y){
    
    double c_real = this->real - y.real;
    double c_img = this->img - y.img;
    
    Complexo c(c_real, c_img);
    return c;
    
}

Complexo Complexo::operator*(Complexo y){
    
    double c_real = (this->real * y.real) - (this->img * y.img);
    double c_img = (this->real*y.img) + (this->img*y.real);
    
    Complexo c(c_real, c_img);
    return c;
    
}
double Complexo::operator!(){
    
    double abs = sqrt((pow(this->real,2)+pow(this->img,2)));
    
    return abs;
}

void Complexo::Imprime(){
    if(this->img >= 0 ){
        std::cout << this->real << " +" << this->img << "i" << std::endl;
    }
    else{
        std::cout << this->real << " " << this->img << "i" << std::endl;
    }
    
}


Complexo::~Complexo() {
}
