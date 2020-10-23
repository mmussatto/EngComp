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
public class Sistema_de_Som {

    public Sistema_de_Som(int Vol) {
        Volume = Vol;
    }

    private boolean AltoFalante_Ligado;
    private int Volume;
    private int Volume_max = 100;
    

    public void Tocar_Musica() {
        Set_AltoFalante(true);
        return;
    }
    
    public int Pausar_Musica(){
        if(AltoFalante_Ligado == true){
            Set_AltoFalante(false);
            return 1;
        }
        else{
            return 0;
        }
    }
    
    private void Set_AltoFalante(boolean status){
        AltoFalante_Ligado = status;
    }   
    
    public int Aumentar_Vol(){
        if(Set_Volume(Volume + 5)== 1)
            return 1;
        else
            return 0;
    }

    private int Set_Volume(int Vol) {
        if(Vol >= 0 && Vol <= Volume_max){
            Volume = Vol;
            return 1;
        }
        else
            return 0;
    }
    
    public int Get_Volume(){
        return Volume;
    }

}
