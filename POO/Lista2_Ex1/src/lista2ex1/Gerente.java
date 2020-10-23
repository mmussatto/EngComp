package lista2ex1;
import java.util.*;

/**
 * 
 */
public class Gerente {

    /**
     * Default constructor
     */
    public Gerente(String Nome, int Idade) {
        this.Nome = Nome;
        this.Idade = Idade;
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
    private Set<Cliente> responsavel = new HashSet<>();









    /**
     * @return
     */
    public boolean AprovaCartao() {
        // TODO implement here
        return true;
    }

    /**
     * @param Valor
     */
    public void AprovaEmprestimo(double Valor) {
        // TODO implement here
    }
    
    public void Novo_Cliente(Cliente c){
        responsavel.add(c);
    }

}