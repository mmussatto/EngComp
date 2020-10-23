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
public class Lista1_Ex1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Celular cel = new Celular("Galaxy", 95);
        
        cel.Ligar();
        cel.Mudar_Brilho(60);
        cel.Conectar_Rede("NET_Virtua");
        
        cel.Toca_Musica("Never Going Back Againg by Fleetwood Mac");
        cel.Overclock();
        cel.Aumentar_Volume();
        cel.Pausar_Musica();
        
        
        cel.Discar(12344321);
        
        cel.Carregar();
        cel.Desligar();
    }
    
}
