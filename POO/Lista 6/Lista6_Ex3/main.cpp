/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Murilo
 *
 * Created on October 23, 2020, 6:58 PM
 */

#include <cstdlib>
#include <iostream>
#include "Complexo.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Complexo a(3.0, 4.0);
    Complexo b(2.0, 7.0);
    
    Complexo c = a + b;
    Complexo d = a - b;
    Complexo e = a * b;
    

    cout << "    a: ";   a.Imprime();
    cout << "    b: ";   b.Imprime();
    cout << "a + b: "; c.Imprime();
    cout << "a - b: "; d.Imprime(); 
    cout << "a * b: "; e.Imprime();
    
    /*Para o módulo, escolhi o operador ! pois ele leva apenas um parâmetro*/
    cout << "Modulo a: " << !a << endl;
    
    return 0;
}

