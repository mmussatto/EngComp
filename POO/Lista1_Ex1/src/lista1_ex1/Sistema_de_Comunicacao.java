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
public class Sistema_de_Comunicacao {
    
    public Sistema_de_Comunicacao(){
        Wifi_Habilitado = false;
        Microfone_Ligado = false;
    }
    
    private boolean Microfone_Ligado;
    private String Rede_Wifi;
    private boolean Wifi_Habilitado;

    public void Discar(int Numero) {
        Set_Microfone(true);
    }
    
    public void Encerrar_Chamada(){
        Set_Microfone(false);
    }

    private void Habilitar_Wifi(boolean status) {
        Wifi_Habilitado = status;
    } 
    
    public int Conectar_Wifi(String Rede) {
        Habilitar_Wifi(true);
        Rede_Wifi = Rede;
        return 1;
    }
    
    private void Set_Microfone(boolean State) {
        Microfone_Ligado = State;
    }
}
