package spaceinvaders;

/**
 *
 * @author  Murilo Mussatto Nusp: 11234245
 *          
 */
public class Tela {
    
    /**
     * Construtor da classe Tela
     * 
     * Nesse contrutor, a matriz de char que atuará como 
     *  o display do jogo é criada.
     * 
     * @param linhas    numero inteiro de linhas da matriz
     * @param colunas   numero inteiro de colunas da matriz
     * @param g         jogo a qual a classe pertence
     */
    public Tela(int linhas, int colunas, Game g){ 
        
        display = new char[linhas][colunas];
        
        this.colunas = colunas;
        this.linhas = linhas;
        this.game = g;
    }
    
    /**
     * Matriz de char do jogo 
     */
    private char[][] display;
    
    /**
     * Quantidade de Linhas.
     */
    private final int linhas;
    
    /**
     * Quantidade de Colunas.
     */
    private final int colunas;
    
    /**
     * Jogo a qual a Tela pertence.
     */
    private final Game game;
    
    /**
     * Essa fução é responsável por Imprimir no console a matriz 
     * de char do dispay.
     */
    public void ImprimeTela(){
        
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                System.out.print(display[i][j]);
            }
                System.out.println();
        }
    }
    
    /**
     * Essa função é responsável por inicializar a matriz de char do display,
     *  adicionando as bordas e preenchendo o inteiror com espaços em branco
     */
    public void IniciaTela(){
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {      
                
                if(i == 0) {display[i][j] = '#';}
                else if(i == linhas-1) {display[i][j] = '#';}
                else if(j == 0) {display[i][j] = '#';}
                else if(j == colunas-1) {display[i][j] = '#';}
                else {display[i][j] = ' ';}
        
            }
        }
        
    }
    
    /**
     * Essa função adiciona um char qualquer a uma dada posicao da matriz 
     * do display
     * 
     * @param linha     linha onde o char será incluído
     * @param coluna    coluna onde o char será incluído
     * @param c         char que será incluído na matriz
     * 
     */
    public void AdicionaTela(int linha, int coluna, char c){
        display[linha][coluna] = c;
    }
    
    /**
     * 
     * @return quantidade de linhas da matriz do display
     */
    public int getLinhas(){
        return linhas;
    }
    
    /**
     * 
     * @return quantidade de colunas da matriz do display
     */
    public int getColunas(){
        return colunas;
    }
    
    /**
     * Essa função é responsável por "limpar" a janela do console. Por enquanto
     * ela só printa várias quebras de linha para separar as impressões antigas
     * das novas
     */
    public void LimpaConsole(){
        System.out.println("\n\n\n\n\n\n\n\n");
    }
    
    /**
     * Essa função é responsável por mostrar uma mensagem quando o jogador é 
     *  atingido por um tiro inimigo.
     * <p>
     * Para isso foram criadas duas strings e os caracteres dessas strings
     *  foram adicionadads na matriz do display.
     */
    public void MsgAtingido(){
        
        String msg1 = "Jogador Atingido!";
        String msg2 = "Vidas Restantes: " + String.valueOf(game.getVidas());
               
        /*Posicionamento da mensagem na matriz*/
        int linha = linhas/3;   
        int coluna = colunas*2/5;  
        int i; int j;
        
        /*Adicionando a primeira mensagem na matriz*/
        i = linha;
        j= coluna;
        ImprimeMsg(i, j, msg1);
        
        
        /*Adicionando a segunda mensagem na matriz*/
        i+=2;  
        j = coluna;
        ImprimeMsg(i, j, msg2);
      
    }
    
    /**
     * Essa função é responsável por mostrar uma mensagem quando o jogador 
     *  derrota todos os inimigos e passa de fase.
     * <p>
     * Para isso foram criadas tres strings e os caracteres dessas strings
     *  foram adicionadads na matriz do display.
     */
    public void MsgProxFase(){
        
        String msg1 = "Todos os inmigos foram derrotados!";
        String msg2 = "Vidas Restantes: " + String.valueOf(game.getVidas());
        String msg3 = "Proxima Fase: " + String.valueOf(game.getFase());
               
        /*Posicionamento da mensagem na matriz*/
        int linha = linhas/3;   
        int coluna = colunas*2/5;  
        int i; int j; 
        
        /*Adicionando a primeira mensagem na matriz*/
        i = linha;
        j = coluna;
        ImprimeMsg(i, j, msg1);

        /*Adicionando a segunda mensagem na matriz*/
        i += 2;  
        j = coluna;
        ImprimeMsg(i, j, msg2);
        
        /*Adicionando a terceira mensagem na matriz*/
        i += 2;  
        j = coluna;
        ImprimeMsg(i, j, msg3);
        
                
    }
    
    /**
     * Essa função é responsável por mostrar uma mensagem quando os invasores
     *  se aproximam do canhão e a fase recomeça.
     * <p>
     * Para isso foram criadas quatro strings e os caracteres dessas strings
     *  foram adicionadads na matriz do display.
     */
    public void MsgInvasoresWin(){
        
        String msg1 = "Voce falhou!";
        String msg2 = "Os inimigos invadiram a Terra!";
        String msg3 = "Recomecando Fase!";
        String msg4 = "Vidas Restantes: " + String.valueOf(game.getVidas());
               
        /*Posicionamento da mensagem na matriz*/
        int linha = linhas/3;   
        int coluna = colunas*2/5-3;  
        int i; int j;
        
        /*Adicionando a primeira mensagem na matriz*/
        i = linha;
        j = coluna;
        ImprimeMsg(i, j, msg1);
                
        /*Adicionando a segunda mensagem na matriz*/
        i+=2;  
        j = coluna-7;
        ImprimeMsg(i, j, msg2);
        
                
        /*Adicionando a terceira mensagem na matriz*/
        i+=2;  
        j=coluna;
        ImprimeMsg(i, j, msg3);
        
        
        /*Adicionando a quarta mensagem na matriz*/
        i+=2;  
        j=coluna;
        ImprimeMsg(i, j, msg4);
        
    }
    
    /**
     * Essa função é responsável por mostrar uma mensagem quando o jogador perde 
     *  o jogo.
     * <p>
     * Para isso foram criadas duas strings e os caracteres dessas strings
     *  foram adicionadads na matriz do display.
     */
    public void MsgGameOver(){
        
        String msg1 = "Game Over!";
        String msg2 = "Score: " + String.valueOf(game.getScore());
        
        /*Posicionamento da mensagem na matriz*/
        int linha = linhas/3;   
        int coluna = colunas*2/5;
        int i; int j;
        
        /*Adicionando a primeira mensagem na matriz*/
        i = linha;
        j = coluna;
        ImprimeMsg(i, j, msg1);
        
        /*Adicionando a segunda mensagem na matriz*/
        i+=2;  
        j = coluna;
        ImprimeMsg(i, j, msg2);
    }
    
    /**
     * Método interno da classe Tela, responsável por 
     *  imprimir mensgens (Strings) no display.
     * 
     * @param i     linha onde a mensgagem será mostrada
     * @param j     coluna onde a mensgaem será mostrada
     * @param msg   mensagem que será mostrada
     * 
     */
    private void ImprimeMsg(int i, int j, String msg){
        for (int k = 0; k < msg.length(); k++) {
            display[i][j] = msg.charAt(k);
            j++;
        }
    }
}
