/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lista1_ex1;
import java.util.Scanner;

/**
 *
 * @author Murilo
 */
public class Tela_Touch {
    
    public Tela_Touch() {
        Brilho = Brilho_Max;
    }
    
    private boolean Bloqueada;
    private int Brilho;
    private int Brilho_Max = 100;
    
    public void Mostrar(String Output) {
        Set_Tela(false);
        System.out.println(Output);
        Set_Tela(true);
    }

    public String Recebe_input() {
        Scanner s = new Scanner(System.in);
        return s.nextLine(); //le e retorna uma linha do teclado  
    }

    private void Set_Tela(boolean status) {
        Bloqueada = status;
    }

    public void Set_Brilho(int Valor) {
        if(Valor >= 0 && Valor <=100){
            Brilho = Valor;
            Mostrar("Nivel de Brilho: "+Brilho);
        }
        else{
            Mostrar("Nivel de Brilho invalido...");
        }
    }

}
