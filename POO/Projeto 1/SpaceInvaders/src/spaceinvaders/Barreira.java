package spaceinvaders;

/**
 *
 * @author Murilo Mussatto Nusp: 11234245
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
        
        /*Construtor da Classe Mãe*/
        super(g, x, y, vx, vy);
        
        Destruido = false;
        Img = '=';
    }
    
    /**
     * Estado da Barreira
     */
    private boolean Destruido;
      
    /**
     * @return estado da barreira
     */
    public boolean getDestruido(){
        return Destruido;
    }
    
    /**
     * Esse método é chamado quando a barreira é atingida
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
