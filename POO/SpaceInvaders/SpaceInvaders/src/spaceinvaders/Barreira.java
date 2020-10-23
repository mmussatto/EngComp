/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package spaceinvaders;

/**
 *
 * @author Murilo
 */
public class Barreira extends Entity{
    
    /**
     * Construtor da classe Barreira
     * 
     * @param g             jogo a qual a classe pertence
     * @param x             posicao no eixo X
     * @param y             posicao no eixo Y
     * @param vx            velocidade no eixo X
     * @param vy            velocidade no eixo Y
     */
    public Barreira (Game g, int x, int y, int vx, int vy){
        
        super(g, x, y, vx, vy);
        
        Destruido = false;
        Img = '=';
    }
    
    /**
     * 
     */
    private boolean Destruido;
      
    /**
     * @return estado da barreira
     */
    public boolean getDestruido(){
        return Destruido;
    }
    
    /**
     * 
     */
    public void setDestruido(){
        Destruido = true;
    }
    
    /**
     * Esse método não é utilizado por essa classe uma vez que a barreira
     *  não se move.
     */
    @Override
    public void move(boolean d) {
    }
    
    
}
