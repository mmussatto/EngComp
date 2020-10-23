/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lista1_ex1;

/**
 *
 * @author Murilo
 */
public class Processador {
 
    public Processador(String Model, float c){
        Modelo = Model;
        Clock = c;
    }
    
    private String Modelo;
    private float Clock;
    private float Clock_Max = 5;
    
    public int Overclock(){
        if(Set_Clock((float)4.84651) == 1)
            return 1;
        else
            return 0;
    }
    
    private int Set_Clock(float value){
        if(value > 4 && value < 5){
            Clock = value;
            return 1;
        }   
        else
            return 0;
    }
}
