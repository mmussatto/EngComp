package spaceinvaders;
import java.util.*;

/**
 * 
 */
public class Canhao extends Entity {

    /**
     * Construtor da classe Canhao
     * 
     * @param g             jogo a qual a classe pertence
     * @param x             posicao no eixo X
     * @param y             posicao no eixo Y
     * @param vx            velocidade no eixo X
     * @param vy            velocidade no eixo Y
     * @param ptotaldelay   
     */
    public Canhao(Game g, int x, int y, int vx, int vy, int ptotaldelay) {
        
        super(g, x, y, vx, vy);
        
        Vidas = 3;
        Img = '^';
        Direcao = false;    /*começa movendo pra direita*/
        DelayTiro = 0;      
        TotalDelay = ptotaldelay;
    }

    /**
     * 
     */
    private int Vidas;
    
    /**
     * variável para controlar a quantidade de tiros e 
     * impedir varios tiros consecutivos
     */
    private int DelayTiro;
    
    /**
     * controla a quantidade de maxima de delay para dar o tiro
     */
    private final int TotalDelay;
    


    /**
     * Esse método possui um contador formado pelas variáveis TotalDelay 
     *  e DelayTiro. A finalidade é imperdir que o jogador atire várias vezes
     *  consecutivas.
     * 
     * @return null caso nao tenha atirado e um obejto da classe Tiro caso 
     *  tenha atirado
     */
    public Tiro Atrirar() {
        
        if(DelayTiro <= TotalDelay){
            DelayTiro++;
            return null;
        }
        
        else{
            DelayTiro = 0;
            Tiro tiro = new Tiro(this.game, PosX-1, PosY, 2, 0, true);
            return tiro;
        }    
    }

    /**
     * Esse método é chamado quando o jogador é atingido por um tiro inimigo.
     *  Ela chama vário métodos da classe jogo a qual o canhão pertence.
     * 
     * @param x true caso os inimigos tenham chegado perto do canhao e
     *          false se foi atingido por um tiro
     */
    public void Atingido(boolean x) {
        
        Vidas--;
        
        if(x) return;
        
        game.Display.IniciaTela();
        game.Display.MsgAtingido();
        game.Display.ImprimeTela();
        
        game.LimpaTiro();
        game.wait(1200);
        
    }

    /**
     * @return número de vidas restantes
     */
    public int getVidas() {
        return Vidas;
    }
    
    /**
     * se true: move p/ esquerda
     * se false: move p/ direita
     */
    @Override
    public void move(boolean d){
        
        if(d == true){
            PosY -= VelY;
            Direcao = d;
        }
        
        if(d == false){
            PosY += VelY;
            Direcao = d;
        }
    }
}