package spaceinvaders;


/**
 * @author Murilo Mussatto Nusp: 11234245
 */
public class Invasor extends Entity {

    /**
     * Construtor da Classe
     * 
     * Para esse construtor, os tipos de alienigena foram diferenciados com 
     *  diferentes chars. Como tinha um número desigual de invasores de cada tipo,
     *  foi criado um parâmetro ptipo e utilizá-lo para setar os tipos
     *  dos invadores. 
     * 
     * 
     * @param g     jogo a qual a classe pertence
     * @param x     posicao no eixo X
     * @param y     posicao no eixo Y
     * @param vx    velocidade no eixo X
     * @param vy    velocidade no eixo Y
     * @param ptipo tipo de invasor
     */
    public Invasor(Game g, int x, int y, int vx, int vy, int ptipo) {
        
        /*Construtor da Classe Mãe*/
        super(g, x, y, vx, vy);
        
        Morto = false;      /*Invasor começa vivo*/
        Direcao = false;    /*Começa se movendo para a direita*/
        
        switch (ptipo) {
            case 0:         /*Primeira linha de invasores*/                
                Tipo = 0;
                break;
                
            case 1:         /*Segunda e terceira linha*/
            case 2:
                Tipo = 1;
                break;
                
            default:        /*Ultimas duas linhas*/
                Tipo = 2;
                break;
        }
        
        switch (Tipo) {
            case 0:         /*Tipo 0*/
                Img = '@';
                break;
            case 1:         /*Tipo 1*/      
                Img = '$';
                break;
            default:        /*Tipo 2*/
                Img = '&';
                break;
        }
        
    }
    
    /**
     * Estado do Invasor
     */
    private boolean Morto;

    /**
     * O tipo define apenas o char que representa o invasor e a pontuação 
     * recebida por acertá-lo.
     * 
     * Existem três tipos de invasor e sua classificação depende da posição
     *  no jogo. Os invasores que ficam na linha mais distante do jogador, são
     *  do tipo 0. Os invasores nas duas linhas intermediárias são do tipo 1.
     *  Por fim, invasores das duas fileiras mais próximas ao jogador são do
     *  tipo 2.
     * 
     */
    private int Tipo;


    /**
     * Método de movimento do Invasor.
     * 
     * @param d  indica se  o movimento eh horizontal ou vertical
     */
    @Override
    public void move(boolean d){
        
        if(d == true){          /*movimento vertical*/
            PosX+= VelX;        /*para baixo*/
            Direcao = !Direcao; /*inverte a direcao*/
        }
        
        else{                       /*movimento horaizontal*/
            if(Direcao == true){    /*para a esquerda*/
                PosY-= VelY;
            }
            if(Direcao == false){   /*para a direita*/
                PosY+= VelY;
            }
        }
    }
    
    /**
     * 
     * @return  objeto to classe tiro se conseguiu atirar
     *          null caso invasor esteja morto
     */
    public Tiro Atrirar() {
        
        if(!Morto){
            Tiro tiro = new Tiro(this.game, PosX+1, PosY, 2, 0, false);
            return tiro;
        }
        else return null;
    }
    
    /**
     * Método que aumenta a velocidade do Invasor
     */
    public void AumentaVel() {
        VelY++;
    }
    
    /**
     * 
     * @return  estado de vida do invasor
     */
    public boolean getMorto(){
        return Morto;
    }
    
    /**
     * Método utilizado quando o Invasor é atingido
     */
    public void setMorto(){
        Morto = true;
    }
    
    /**
     * 
     * @param d true: esquerda
     *          false: direita
     */
    public void setDirecao(boolean d){
        Direcao = d;
    }
    
    /**
     * 
     * @return tipo do invasor definido pelo char Img
     */
    public int getTipo(){
        return Tipo;
    }
    
}