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
public class Celular {
    
    public Celular(String Model, int bateria) {
        Modelo = Model; 
        Ligado = false;
        if(bateria >= 0 && bateria < 100){
            Nivel_Bateria = bateria;
        }
        
        Tela = new Tela_Touch();
        Som = new Sistema_de_Som(50);
        Com = new Sistema_de_Comunicacao();
        Pros = new Processador("Snap Dragon", (float) 4.32154);
    }

    private Tela_Touch Tela;
    private Sistema_de_Som Som;
    private Sistema_de_Comunicacao Com;
    private Processador Pros;
    
    
    private String Modelo;
    private int  Nivel_Bateria;
    private boolean Ligado;
    private int Bateria_Max = 100;


    
    public void Ligar() {
        Ligado = true;
        Tela.Mostrar("Telefone Ligado!");
    }
    
    public void Desligar() {
        Ligado = false;
        Tela.Mostrar("\nTelefone Desligado!");
    }

    public void Discar(int Numero) {
        Com.Discar(Numero);
        Tela.Mostrar("\nDiscando para: "+Numero);
        Tela.Mostrar("....\n....\n....");
        Com.Encerrar_Chamada();
        Tela.Mostrar("Chamada Encerrada!\n");
    }
    
    public void Conectar_Rede(String Rede){
        Tela.Mostrar("\nConectado a rede: "+Rede);
        if(Com.Conectar_Wifi(Rede) == 1)
            Tela.Mostrar("Conectado :)");
        else
            Tela.Mostrar("Conexao Falhou :(");
        
    }

    public void Carregar() {
        do{
            Aumenta_Bateria();
            Tela.Mostrar("Caregando...");
        }while(Nivel_Bateria != Bateria_Max);
        Tela.Mostrar("Bateria totalemente Carregada!");
        return ;
    }

    private void Aumenta_Bateria() {
        Nivel_Bateria += 1;
        return;
    }
    
    public void Toca_Musica(String Musica){
        Som.Tocar_Musica();
        Tela.Mostrar("\nTocando agora: "+Musica);
    }
    
    public void Pausar_Musica(){
        if(Som.Pausar_Musica() == 1){
            Tela.Mostrar("Musica pausada!");
        }
        else{
            Tela.Mostrar("Nada tocando no Momento!");
        }
    }
    
    public void Aumentar_Volume(){
        if(Som.Aumentar_Vol() == 1)
            Tela.Mostrar("Volume atual:"+Som.Get_Volume());
        else
            Tela.Mostrar("Voulme Maximo!");
    }
    
    public void Mudar_Brilho(int value){
        Tela.Set_Brilho(value);
    }
    
    public void Overclock(){
        if(Pros.Overclock() == 1)
            Tela.Mostrar("Overclock ativado :)");
        else
            Tela.Mostrar("Overclock Fail :(");
    }
}
