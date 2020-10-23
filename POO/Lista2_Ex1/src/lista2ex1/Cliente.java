package lista2ex1;
import java.util.*;

/**
 * 
 */
public class Cliente {

    /**
     * Default constructor
     */
    public Cliente(String Nome, int Idade, int CPF, int Numero_Conta, int Senha_Conta) {
        this.Nome = Nome;
        this.Idade = Idade;
        this.CPF = CPF;
        this.conta = new Conta_Bancaria(Numero_Conta, Senha_Conta);
        this.PossuiConta = true;
    }

    /**
     * 
     */
    private String Nome;

    /**
     * 
     */
    private int Idade;

    /**
     * 
     */
    private boolean PossuiConta;

    /**
     * 
     */
    private int CPF;
    
    /**
     * 
     */
    public Conta_Bancaria conta;



    /**
     * @return
     */
    public int ConsultaCPF() {
        System.out.println("O CPF do Cliente eh: " + CPF);
        return 0;
    }

    /**
     * @return
     */
    public int Consulta_Idade() {
        System.out.println("A Idade do Cliente eh: " + Idade);
        return 0;
    }

    /**
     * @return
     */
    public void Consulta_Nome() {
        System.out.println("O Nome do Cliente eh: " + Nome);
    }

    /**
     * @param gerente
     */
    public void Pedir_Cartao(Gerente gerente) {
        // TODO implement here
        
    }

    /**
     * @param gerente 
     * @param Valor
     */
    public void Pedir_Emprestimo(Gerente gerente, double Valor) {
        // TODO implement here
    }

}