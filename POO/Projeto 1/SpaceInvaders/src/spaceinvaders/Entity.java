package spaceinvaders;

/**
 * @author Murilo Mussatto Nusp: 11234245
 */
public abstract class Entity {

    /**
     * Construtor da classe abstrata
     * 
     * @param g     jogo a qual a classe pertence
     * @param x     posicao no eixo X
     * @param y     posicao no eixo Y
     * @param vx    velocidade no eixo X
     * @param vy    velocidade no eixo Y
     */
    public Entity(Game g, int x, int y, int vx, int vy) {
        game = g;
        PosX = x;
        PosY = y;
        VelX = vx;
        VelY = vy;
    }


    /**
     * Posição no eixo X.
     */
    protected int PosX;

    /**
     * Posição no eixo Y.
     */
    protected int PosY;

    /**
     * Velocidade no eixo X.
     */
    protected int VelX;
    
    /**
     * Velocidade no eixo Y.
     */
    protected int VelY;
    
    /**
     * Jogo a qual a entity pertence.
     */
    protected Game game;
    
    /**
     * Char que representa a entidade.
     */
    protected char Img;
    
    /**
     * true - esquerda
     * false - direita
     */
    protected boolean Direcao;

    /**
     * Método de movimento das Entidades.
     * 
     * @param d utilizacao depende da subclasse
     */
    public abstract void move(boolean d);
    
    
     /**
     * 
     * @return  char que representa a classe
     */
    public char getImg(){
        return Img;
    }

    /**
     * 
     * @return  posicao no eixo X
     */    
    public int getPosX(){
        return PosX;
    }

    /**
     * 
     * @return  posicao no eixo Y
     */    
    public int getPosY(){
        return PosY;
    }
    
    /**
     * 
     * @return  velocidade no eixo X
     */    
    public int getVelX(){
        return VelX;
    }
    
    /**
     * 
     * @return  velocidade no eixo Y
     */    
    public int getVelY(){
        return VelY;
    }
    
    /**
     * 
     * @return direcao do movimento
     */    
    public boolean getDirecao(){
        return Direcao;
    }
}