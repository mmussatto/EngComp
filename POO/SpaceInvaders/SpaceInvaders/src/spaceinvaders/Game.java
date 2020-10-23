package spaceinvaders;
import java.util.*;


/**
 * 
 */
public class Game {

    /**
     * Construtor da Classe Game.
     */
    public Game() {
        Score = 0;
        Nfase = 0;
    }

    /**
     * Pontuacao do Jogador.
     */
    private int Score;

    /**
     * Número da fase em que o jogador está.
     */
    private int Nfase;

    /**
     * Número total de invasores .
     */
    private final int Ninvasores = 55;
    
    /**
     * Contador do número de invasores destruídos.
     */
    private int Ninvasoresmortos = 0;
    
    /**
     * Obejto da Classe Tela que representa o display do jogo.
     */
    public Tela Display;
    
    /**
     * Vetor de Obejtos da Classe Invasor.
     */
    private ArrayList<Invasor> Ainvasores = new ArrayList();
    
    /**
     * Vetor de Objetos da Classe Tiro.
     */
    private ArrayList<Tiro> Atiro = new ArrayList();
    
    /**
     * Vetor de Objetos da Classe Barreira.
     */
    private ArrayList<Barreira> Abarreiras = new ArrayList();
    
    /**
     * Obejeto da Classe Canhao.
     *  Representa o Player
     */
    private Canhao Ocanhao;
    
    /**
     * Obejto da Classe Random.
     *  É utilizado para randomizar os tiros dos invasores
     */
    private Random random = new Random();

    
 /*---------------- Load --------------------------------------------------------------------------------------------------------*/    

    /**
     * Cria o objeto Canhao.
     * 
     */
    public void LoadCanhao() {
       Ocanhao = new Canhao(this, Display.getLinhas()-3, Display.getColunas()/2, 0, 3, 0);
    }

    /**
     * Cria o vetor de invasores e o preenche com os objetos.
     */
    public void LoadInvasores() {
        int j = 0; /* utilizado para determinar espaçamento entre os invasores*/
        
        for (int i = 0; i < Ninvasores; i++){
            
            /* os parametros utilizados servem p/ comecar com invasores no meio da tela  */
            Invasor e = new Invasor(this, i/11+2, j+Display.getColunas()/4, 1, 1, i/11); 
            Ainvasores.add(e);
            
            j+=4;
            if(j%11 == 0 && i!=0) /* quando j multiplo de 11, comeca nova linha, logo j reseta*/
                j = 0;
        }
    }

    /**
     * Cria o vetor de barreiras e o preenche com os objetos
     * Para a implementação do jogo, considerei 4 conjuntos de 3 barreiras
     */
    public void LoadBarreiras() {
        for (int i = 1; i <= 4; i++) {
            
            Barreira b1 = new Barreira(this, Display.getLinhas()-6, i*Display.getColunas()/4-9, 0, 0);
            Barreira b2 = new Barreira(this, Display.getLinhas()-6, i*Display.getColunas()/4-8, 0, 0);
            Barreira b3 = new Barreira(this, Display.getLinhas()-6, i*Display.getColunas()/4-7, 0, 0);
            
            Abarreiras.add(b1);
            Abarreiras.add(b2);
            Abarreiras.add(b3);
            
        }
    }
    
    /**
     * Cria o Display do jogo
     */
    public void LoadDisplay() {
       Display = new Tela(25, 70, this);
       Display.IniciaTela();
    }
    
    
 /*---------------- Desenha -----------------------------------------------------------------------------------------------------*/    
    
    /**
     * Adiciona os invasores na matriz de char do Display
     */
    public void DesenhaInvasores() {
        for (int i = 0; i < Ninvasores; i++) {
            if( Ainvasores.get(i).getMorto() == false)
                Display.AdicionaTela(Ainvasores.get(i).getPosX(), 
                                     Ainvasores.get(i).getPosY(), 
                                     Ainvasores.get(i).getImg() );                
        }
    }
    
    /**
     * Adiciona o canhão na matriz de char do Display
     */
    public void DesenhaCanhao() {
        Display.AdicionaTela(Ocanhao.getPosX(), Ocanhao.getPosY(), Ocanhao.getImg());
    }
    
    /**
     * Adiciona os tiros na matriz de char do Display
     */
    public void DesenhaTiros(){
        for (int i = 0; i < Atiro.size(); i++) {
            Display.AdicionaTela(Atiro.get(i).getPosX(), Atiro.get(i).getPosY(), Atiro.get(i).getImg());
            
        }
    }
    
    /**
     * Adiciona as barreiras na matriz de char do Display
     */
    public void DesenhaBarreiras(){
        for (int i = 0; i < Abarreiras.size(); i++) {
            if(!Abarreiras.get(i).getDestruido()){
                Display.AdicionaTela(Abarreiras.get(i).getPosX(), Abarreiras.get(i).getPosY(), Abarreiras.get(i).getImg());
            }
        }
    }
  
 /*-------------- Tiro e COlisao ----------------------------------------------------------------------------------------------------*/   
    
    /**
     * Controla o disparo do canhão
     */
    public void AtiraCanhao(){
        Tiro tiro = Ocanhao.Atrirar();
        
        if(tiro != null){
            Atiro.add(tiro);
        }        
    }
    
    /**
     * Controla o disparo dos invasores.
     * 
     * O número de tiros randomicos depende da fase em que o jogador está.
     * Como existe um espaçamento entre os invasore, é preciso achar um 
     *  que esteja em uma coluna suficientemente próxima da do canhão para o 
     *  tiro calculado. Além disso, é preciso se certificar de que que existe
     *  algum invasor vivo nas 5 fileiras e que esteja nessa coluna aproximada.
     */
    public void AtiraInvasor(){
        
        /*Tiros aleatórios*/
        for (int i = 0; i < Nfase; i++) {
            
            int j = random.nextInt(55);
            Tiro tiro = Ainvasores.get(j).Atrirar();
            
            if(tiro != null){
                Atiro.add(tiro);
            }
        }
        
        /*Tiros Calculados*/
        
        int colunaCanhao = Ocanhao.getPosY(); //guarda a coluna do canhao 
        int colunaInvasor;                    //guarda a coluna do invasor
        int invasor = -1;                     //indice do invasor no vetor de invasores
        
        /*Procura um invasor que esteja em uma coluna proxima a do canhao*/
        for (int i = 0; i < Ninvasores; i++) {
            colunaInvasor = Ainvasores.get(i).getPosY();
            if (colunaInvasor >= colunaCanhao && colunaInvasor <= colunaCanhao+4){
                invasor = i;
                break;
            }
        }
        
        /*Percorre as 5 linhas de invasores até achar um apto a atirar*/
        for (int i = 0; i < 5; i++) {
            
            if(invasor == -1) break; //nao achou um invaor
            
            Tiro tiro = Ainvasores.get(invasor+11*i).Atrirar();
            
            if(tiro != null){
                Atiro.add(tiro);
                break;
            }
        }
               
        
        
       
         
    }
    
    /**
     * Esse método controla as colisões entre os tiros tanto dos invasores 
     *  quanto do canhão.
     * <p>
     * Como o tiro se possui uma velocidade maior que 1, precisei colocar 
     *  condicionais com operadores maior-igual e menor-igual, utilizando a 
     *  posição atual do tiro e sua posição antiga.
     * <p>
     * Funcionamento: o primeiro for percorre o vetor de tiros, checando as 
     *  condicões para cada um dos objetos.
     * Cada tiro é comparado com todos os objetos do vetor de invasores, todos 
     *  os objetos do vetor de barreiras, todos os objetos do vetor de tiros 
     *  e o canhão.
     * 
     * @return true caso o canhão tenha sido atingido por um tiro inimigo
     */
    public boolean Colisao(){
        
        boolean remove; /*condicao para remoção do tiro do vetor de tiros*/
        boolean CanhaoAtingido = false;
        boolean remove2tiros;
        int segundotiro = 0;
        
        int TPosXAtual;     /*posição atual do tiro na coordenada X*/
        int TPosXAntiga;    /*posição antiga do tiro na coordenada X*/
        
        /*percorre todo o vetor de tiros*/
        for (int i = 0; i < Atiro.size(); i++){
            
            TPosXAtual = Atiro.get(i).PosX; 
            
            /*define posicao antiga do tiro na coordenada X*/
            if(Atiro.get(i).Atirador){
                TPosXAntiga = TPosXAtual + Atiro.get(i).VelX;                 
            }
            else{
                TPosXAntiga = TPosXAtual - Atiro.get(i).VelX; 
            }
           
            remove = false;         /*reset*/
            remove2tiros = false;   /*reset*/
            
            
            /*Colisao com invasores*/
            if(Atiro.get(i).getAtirador()){ //se o tiro foi de um invasor, nao tem colisao com outros invasores
                
                /*percorre vetor de invasores*/
                for (int j = 0; j < Ninvasores; j++){ 
                    if(!Ainvasores.get(j).getMorto()){ //se invasor já estiver morto, não faz sentido
                        if(Ainvasores.get(j).PosX >= TPosXAtual 
                                && Ainvasores.get(j).PosX <= TPosXAntiga 
                                && Atiro.get(i).PosY == Ainvasores.get(j).PosY ){
                            
                            /*Animação de explosão*/
                            Display.AdicionaTela(Ainvasores.get(j).PosX , 
                                    Ainvasores.get(j).PosY, '*'); 
                            
                            Ainvasores.get(j).setMorto();  
                            AumentaScore(Ainvasores.get(j).getTipo());
                            Ninvasoresmortos++;
                            remove = true;
                            break;
                        }
                    }  
                }/*end colição com invasores*/
            }
            
            /*Colisao com barreiras*/
            for (int j = 0; j < Abarreiras.size(); j++) {
                
                if(!Abarreiras.get(j).getDestruido()){                  //se a barreira já estiver destruída, não faz sentido
                    if(Atiro.get(i).PosY == Abarreiras.get(j).PosY){    //verifica se estão na mesma coluna
                        
                        /*Disparo do Canhão*/
                        if(Atiro.get(i).Atirador){
                            if(Abarreiras.get(j).PosX <= TPosXAntiga  
                                    && Abarreiras.get(j).PosX >= TPosXAtual){
                                
                                /*Animação de explosão*/
                                Display.AdicionaTela(Abarreiras.get(j).PosX , 
                                        Abarreiras.get(j).PosY, '*'); 
                                
                                Abarreiras.get(j).setDestruido();
                                remove = true;
                                break;
                            }
                        }
                        /*Disparo do invasor*/
                        else{
                            if(Abarreiras.get(j).PosX <= TPosXAtual 
                                    && Abarreiras.get(j).PosX >= TPosXAntiga){
                                
                                /*Animação de explosão*/
                                Display.AdicionaTela(Abarreiras.get(j).PosX , 
                                        Abarreiras.get(j).PosY, '*'); 
                                
                                Abarreiras.get(j).setDestruido();
                                remove = true;
                                break;
                            }
                        }
                    }
                }
            } /*end colisão com barreira*/
            
            /*Colisao com outros tiros*/
            for (int j = i+1; j < Atiro.size(); j++) {                //i+1 -> para não comparar tiros iguais
                if(Atiro.get(i).getPosY() == Atiro.get(j).getPosY()){ //verifica se estão na mesma coluna
                       
                    /*Disparo do Canhão*/
                    if(Atiro.get(i).Atirador){
                        if(Atiro.get(j).getPosX() <= TPosXAntiga  
                                && Atiro.get(j).getPosX() >= TPosXAtual){

                            /*Animação de explosão*/
                            Display.AdicionaTela(Atiro.get(j).getPosX(), 
                                    Atiro.get(j).getPosY(), '*');

                            remove2tiros = true;
                            segundotiro = j;
                            remove = true;
                            break;
                        }
                    }
                    
                    /*Disparo do invasor*/
                    else{
                        if(Atiro.get(j).getPosX() <= TPosXAtual 
                                && Atiro.get(j).getPosX() >= TPosXAntiga){

                            /*Animação de explosão*/
                            Display.AdicionaTela(Atiro.get(j).getPosX(), 
                                    Atiro.get(j).getPosY(), '*');

                            remove2tiros = true;
                            segundotiro = j;
                            remove = true;
                            break;
                        }
                    }
                }
            }/*end colisão com outros tiros*/
            
            
            /*Colisao com o canhao*/
            if(Ocanhao.getPosX() <= TPosXAtual 
                    && Ocanhao.getPosX() >= TPosXAntiga 
                    && Ocanhao.getPosY() == Atiro.get(i).PosY){
                
                remove = true;
                CanhaoAtingido = true;
                
            }/*end colisão com canhão*/
            
            if(remove2tiros == true) Atiro.remove(segundotiro);
            if(remove == true) Atiro.remove(i);
            
        }/*end vetor de tiros*/
        
        return CanhaoAtingido;
    }
    
    /**
     * Esse método remove todos os tiros do vetor de tiros.
     * Ele é chamado quando o canhão é atingido e o jogo recomeça.
     */
    public void LimpaTiro(){
        Atiro.clear();
    }
    
 /*---------------- Move ----------------------------------------------------------------------------------------------------------*/
    
     /**
     * Altera as posições dos invasores.
     * 
     * Nesse método é verficado se o primeiro e o último invasor da primeira
     *  fila vão ultrapassar os limites do display. Caso isso aconteca, a 
     *  flag trocaDirecao se torna true e é mandada para a rotina de movimento
     *  dos invasores, indicando que o movimento deve ser na vertical.
     * Caso contrário, a flag continua como false, indicando que o movimento 
     *  deve ser na horizontal.
     * <p>
     * Como, mesmo mortos, as posições dos invasores ainda mudam, basta
     *  verificar as posições desses dois invasores para saber se eles sairão 
     *  dos limites do display
     */
    public void MoveInvasores(){
        
        boolean trocaDirecao = false;
        
        int PosYFirstInvasor = Ainvasores.get(0).PosY;
        int VelYFirstInvasor = Ainvasores.get(0).getVelY();
        boolean DirecaoFirstInvasor = Ainvasores.get(0).getDirecao();
        
        int PosYLastInvasor = Ainvasores.get(10).PosY;
        int VelYLastInvasor = Ainvasores.get(10).getVelY();
        boolean DirecaoLastInvasor = Ainvasores.get(10).getDirecao();
        
        /*Verifica se os invasores ultrapassarão o limite da esquerda*/
        if(PosYFirstInvasor-VelYFirstInvasor <= 0 && DirecaoFirstInvasor)
            trocaDirecao = true;
        
        /*Verifica se os invasores ultrapassarão o limite da direita*/
        if (PosYLastInvasor+VelYLastInvasor >= Display.getColunas()-1 
                && !DirecaoLastInvasor )
            trocaDirecao = true;
        
        /*Percorre o vetor de invasores, chmando o método de mover*/
        for (int i = 0; i < Ninvasores; i++){
            Ainvasores.get(i).move(trocaDirecao);
        }
        
    /*-----Movimentacao Antiga dos Invasores---------------------*/      
        /*Percorre o vetor de invasores*/
    //        for (int i = 0; i < Ninvasores; i++){
    //            if(Ainvasores.get(i).PosY+Ainvasores.get(i).getVelY() >= Display.getColunas()-1 
    //                    && !((Ainvasores.get(i)).getDirecao()) )
    //                trocaDirecao = true;
    //            
    //            if(Ainvasores.get(i).PosY-Ainvasores.get(i).getVelY() <= 0 
    //                    && (Ainvasores.get(i).getDirecao()) )
    //                trocaDirecao = true;
    //        }
      
    }
    
    /**
     * Altera as posições do canhão.
     * 
     * Esse método verifica para que lado o canhão deve se mover. Idealmente,
     *  aqui é o local onde seria implementado a leitura de teclas do teclado.
     *  Porém, essa parte será desenvolvida nas próxima etapas do trabalho. 
     * <p>
     * Por enquanto, o canhão se move de um lado para outro, percorrendo o
     *  display inteiro. 
     */
    public void MoveCanhao(){
        if((Ocanhao.getPosY()+Ocanhao.getVelY() >= Display.getColunas()-1 
                && !(Ocanhao.getDirecao())) || Ocanhao.getDirecao() )
            Ocanhao.move(true);
        
        if((Ocanhao.getPosY()-Ocanhao.getVelY() <= 0 && (Ocanhao.getDirecao())) 
                || !Ocanhao.getDirecao())
            Ocanhao.move(false);
    }
    
    /**
     * Altera as posições dos tiros.
     * 
     * Esse método simples percorre o vetor de tiros, chamando o método de
     *  mover e verifica se algum tiro está ultrapassando os limites do
     *  display.
     * Caso o tiro esteja saindo do display, ele é retirado do vetor de tiros.
     */
    public void MoveTiros(){
        /*Percorre o vetor de tiros*/
        for (int i = 0; i < Atiro.size(); i++) {
            
            Atiro.get(i).move(true);
            
            /*Tiro saindo por cima*/
            if(Atiro.get(i).PosX <= 0){ 
                Atiro.remove(i);
                break;
            } 
            
            /*Tiro saindo por baixo*/
            if(Atiro.get(i).PosX >= Display.getLinhas()-1){ 
                Atiro.remove(i);
                break;
            }      
        }
    }
    
    /**
     * Aumenta a velocidade de movimento dos invasores.
     */
    public void AceleraInvasores(){
        for (int i = 0; i < Ninvasores; i++){
            Ainvasores.get(i).AumentaVel();
        }
    }
   
    
 /*----------------- Game Settings ---------------------------------------------------------------------------------------------------*/    
    
    /**
     * Mostra informacoes sobre o jogo no console.
     */
    public void MostraInfo(){
        
        System.out.println("Jogo inciado!");
        System.out.print("Fase: " + String.valueOf(this.Nfase) + "\t\t\t");
        //System.out.print("Imortos: " + String.valueOf(this.Ninvasoresmortos) + "\t");
        System.out.print("Score: " + String.valueOf(this.Score) + "\t\t\t");
        System.out.println("Vidas: " + String.valueOf(Ocanhao.getVidas()));
    }    
    
    /**
     * Incrementa o Score de acordo com o tipo de inimigo atingido.
     * 
     * Como existem três tipos de inimigos, foi escolhido um número arbitrário
     *  de pontos para cada um, levando em conta sua posição no jogo. Assim,
     *  inimigos que ficam mais longe do jogador (tipo 0), valem mais pontos
     *  ao serem atingidos.
     * 
     * @param tipo tipo de invasor que foi atingido
     */
    public void AumentaScore(int tipo){
        
        switch (tipo) {
            case 0:
                Score += 250;
                break;
            case 1:
                Score += 150;
                break;
            default:
                Score += 100;
                break;
        }
    }  
    
    /**
     * Criacao dos Objetos e controle de Fases.
     * <p>
     * Esse método cria todo os objetos necessários para o funcionamento do
     *  game e inicia o loop principal.
     * O método gameloop pode retornar três diferentes valores e cada um
     *  tem seu próprio significado. Esses significados podem ser encontrados
     *  ma decrição do método.
     * 
     */
    public void IniciaGame() {
        
        /*Criação dos objetos*/
        LoadDisplay();
        LoadInvasores();
        LoadCanhao();
        LoadBarreiras();
        
        int estado = 1;
        
        /*loop princial*/
        while(estado != 0){
            estado = GameLoop(); 
            
            /*invasores chegaram no canhão*/
            if(estado == 1){
                Ocanhao.Atingido(true);
                RestartFase(false);  
            }
            
            /*passou de fase*/
            if(estado == 2) RestartFase(true);
        }
        
        /*Fim de jogo*/
        GameOver();
            

    }

    /**
     * Fim do jogo.
     */
    public void GameOver() {
        
        Display.LimpaConsole();
        Display.IniciaTela();
        Display.MsgGameOver();
        Display.ImprimeTela();
        
    }
    
    /**
     * Método principal do Jogo.
     * Esse método controla o loop do jogo em sim. Quando o jogador perde, 
     *  seja porque acabaram suas vidas ou porque os invasore chegaram muito
     *  perto da nave, o valor 0 é retornado e o while do método IniciaGame é
     *  parado. Caso o jogador mate todos os invasores, o valor 1 é retornado
     *  e uma nova faze começa.
     * 
     * @return 0 caso tenha dado gameover 
     *         1 caso tenha recomeçado a fase 
     *         2 caso tenha passado de fase
     */
    public int GameLoop() {
        
        /*Variáveis de Controle*/
        int DelayTiroInvasor = 0;   //frequência de tiros dos invasores
        int AumentodeVel = 0;       //vezes que a velocidade foi aumentada
        boolean CanhaoAtingido; 
        Nfase++;
        
        /*Loop principal*/   
        while(true){

            if(Ocanhao.getVidas() == 0) return 0;
            if(VerficaFim()) return 1;
            if(Ninvasoresmortos == Ninvasores) return 2;

            wait(300);
            Display.LimpaConsole();        //print /n para separar as paginas
            Display.IniciaTela();       //retira todo os objetos que estavam na tela passada
            CanhaoAtingido = Colisao(); //verifica colisoes e se o canhao foi atingido 

            if(CanhaoAtingido == true){
                //MostraInfo();           //mostra informacoes sobre a fase
                Ocanhao.Atingido(false);     
                continue;
            }

            MostraInfo();           //mostra informacoes sobre a fase
            DesenhaInvasores();     //adiciona os invasores no display
            DesenhaBarreiras();     //adiciona as barreiraas no display
            DesenhaCanhao();        //adiciona o canhao no display
            DesenhaTiros();         //adiciona os tiros no display
            Display.ImprimeTela();  //imprime o display no console


            if(Ninvasoresmortos >= Ninvasores*5/8 && AumentodeVel == 0){
                AceleraInvasores();
                AumentodeVel++;
            }

            MoveInvasores();        // |
            MoveTiros();            // |> Move as entidades 
            MoveCanhao();           // |

            /*Tiro canhão*/
            AtiraCanhao();          

            /*Tiro Invasor*/
            if(DelayTiroInvasor <= 4)
                DelayTiroInvasor++;
            else{
                AtiraInvasor();
                DelayTiroInvasor = 0;
            } 
        }
    }  
    
    /**
     * Esse método verifica se os invasores chegaram na linha das barreiras.
     * Ele retorna true caso isso tenha acontecido e acionará o gameover
     * 
     * @return true caso os invasores tenham chagado na linha das barreiras
     */
    public boolean VerficaFim(){
        
        for (int i = 0; i < Ninvasores; i++) {
            if(!Ainvasores.get(i).getMorto()){
                if(Ainvasores.get(i).getPosX() == Abarreiras.get(0).PosX)
                    return true;
            }
        } 
        
        return false;
    }
    
    /**
     * Recoloca os invasores e barreiras no jogo além de excluir todos
     *  os tiros.
     * 
     * Esse método tem duas utilidades. Ele é chamado quando o jogador derrota
     *  todos os invasores e, consequentemente, passa de fase e, quando os 
     *  invasores chegam muito perto do canhão e devem ser recolocados no 
     *  topo da tela.
     * 
     * Se o parâmetro x for true, o jogador passou de fase e a mensagem deve
     *  ser impressa na tela.
     * Se o parâmetro x for false, os invasores chegaram muito perto do canhão
     *  e a mensagem correspondente deve ser exibida.
     * 
     * @param x true se passou de fase, 
     *          false se invasores chegaram perto do canhao
     */
    public void RestartFase(boolean x){
        
        
        if(x){ //passou de fase
            Display.LimpaConsole();
            Display.IniciaTela();
            Display.MsgProxFase();
            Display.ImprimeTela();
            wait(2000);
        }
        else{ //invasors chegaram no canhão
            Display.LimpaConsole();
            Display.IniciaTela();
            Display.MsgInvasoresWin();
            Display.ImprimeTela();
            wait(2000);
        }
        
        /*Reset invasores*/
        Ainvasores.clear();
        LoadInvasores();
        Ninvasoresmortos = 0;
        
        /*Reset Tiro*/
        Atiro.clear();
        
        /*Reset Barreiras*/
        Abarreiras.clear();
        LoadBarreiras();
        
    }
    
    
    /**
     * Funcao para congelar o game por um tempo.
     * 
     * Esse método precisou ser implementado para deixar os prints do jogo no
     *  console mais estáveis.
     * Além disso, quando o jogador é atingido, esse método é chamado para 
     *  congelar o tempo por alguns segundos.
     * 
     * @param ms tempo em milisegundos que o jogo fica congelado
     */
    public static void wait(int ms)
    {
        try
        {
            Thread.sleep(ms);
        }
        catch(InterruptedException ex)
        {
            Thread.currentThread().interrupt();
        }
    }   

 /*-----------------Outside Functions ---------------------------------------------------------------------------------------------------*/
    
    /**
     * Retorna o número de vidas restantes do canhão.
     * 
     * Como o objeto do canhão é private e pertence a classe jogo, outras
     *  classes não podem acessar o método getVidas() do canhão. Assim,
     *  foi necessário criar esse método apenas para retornar as vidas restantes.
     * <p>
     * Esse método é utilizado pela classe Tela, no método MsgAtingido()
     *
     * @return vidas do canhão
     */
    public int getVidas(){
        return Ocanhao.getVidas();
    }
    
    /**
     * Retorna a pontuação do jogador.
     * 
     * Esse método é utilizado na hora de escrever a 
     *  mensagem de game over.
     * 
     * @return pontuação do jogador 
     */
    public int getScore(){
        return Score;
    }
    
    /**
     * Retorna a fase atual do jogador.
     * 
     * Esse método pe utilizado na hora de escrever a 
     *  mensagem de próxima fase
     * 
     * @return fase atual do jogador
     */
    public int getFase(){
        return Nfase;
    }
}