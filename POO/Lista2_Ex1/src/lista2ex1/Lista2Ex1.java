/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lista2ex1;

import java.util.Set;

/**
 *
 * @author Murilo
 */
public class Lista2Ex1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
 
        Gerente g1 = new Gerente("Marcos", 30);
        Cliente c1 = new Cliente("Joao", 20, 123123123, 123456789, 1234);

        g1.Novo_Cliente(c1);
        
        c1.conta.Depositar(500.00);
        c1.Consulta_Nome();
        c1.Consulta_Idade();
        c1.ConsultaCPF();
        c1.conta.Consulta_Saldo();
        
        
        
    }
    
}
