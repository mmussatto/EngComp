
package lista2ex1;
import java.util.*;

/**
 * 
 */
public class Conta_Bancaria {

    /**
     * Default constructor
     */
    public Conta_Bancaria(int Numero, int Senha) {
        this.Saldo = 0.0;
        this.Senha = Senha;
        this.Número = Numero;
    }

    /**
     * 
     */
    private double Saldo;

    /**
     * 
     */
    private int Senha;

    /**
     * 
     */
    private int Número;


    /**
     * @param Valor 
     * @return
     */
    public int Depositar(double Valor) {
        Saldo += Valor;
        return 1;
    }

    /**
     * @param Valor 
     * @return
     */
    public int Sacar(Double Valor) {
        // TODO implement here
        return 0;
    }

    /**
     * @param Valor 
     * @return
     */
    private boolean PodeSacar(double Valor) {
        // TODO implement here
        return false;
    }

    /**
     * @param Valor 
     * @param Conta 
     * @return
     */
    public int Transeferir(double Valor, int Conta) {
        // TODO implement here
        return 0;
    }
    
    public void Consulta_Saldo(){
        System.out.println("O Saldo eh: R$" + Saldo);
    }

}