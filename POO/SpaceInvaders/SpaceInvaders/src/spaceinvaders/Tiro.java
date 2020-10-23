package spaceinvaders;
import java.util.*;


/**
 * 
 */
public class Tiro extends Entity {

    /**
     * Construtor da classe Tiro
     * 
     * @param g         jogo a qual a classe pertence
     * @param x         posicao no eixo X
     * @param y         posicao no eixo Y
     * @param vx        velocidade no eixo X
     * @param vy        velocidade no eixo Y
     * @param patirador difere quem criou o tiro
     */
    public Tiro(Game g, int x, int y, int vx, int vy, boolean patirador) {
        
        super(g, x, y, vx, vy);
        
        Atirador = patirador;
                
        if(Atirador == true){
            Direcao = true;
            Img = '|';
        }
        else{
            Direcao = false;
            Img = '!';      
        }
        
    }

    /**
     * se true:     player
     * se false:    invasor
     */
    public boolean Atirador;

    /**
     * Nessa funcao, eu nao precisei utilizar o parametro d que veio da classe
     * abstrata devido a variáveis de controle da própria classe tiro, no
     * caso a váriavel Atirador
     * 
     * @param d     nao é utilizado para a classe tiro
     */
    public void move(boolean d){
        
        if(Atirador == true){
            PosX-=VelX;
        }
        else{
            PosX+=VelX;
        } 
    }
    
    /**
     * 
     * @return se true: player, se false: invasor
     */
    public boolean getAtirador(){
        return Atirador;
    }
}