/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ex2;
import java.util.ArrayList;

/**
 *
 * @author Murilo
 */
public class Ex2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        //Produtos
        Mouse M1 = new Mouse("Mouse óptico, Saída USB, 1.600 dpi", "Casual");
        Mouse M2 = new Mouse("Mouse Gamer super fast, Saida USB-C", "Profissional");
        Mouse M3 = new Mouse("Mouse de Plastico da Xuxa, Cor Rosa", "Brinquedo");
        
        Livro L1 = new Livro("Harry Potter e a Pedra Filosofal","J.K.Rowling");
        Livro L2 = new Livro("Percy Jackson e o Ladrao de Raios","Rick Riodan");
        Livro L3 = new Livro("The Wicher: The Last Wish","Andrzej Sapkowski");
        
        
        //Carrinho
        String Descricao;
        ArrayList<Produto> carrinho = new ArrayList<Produto>();
        carrinho.add(M1);
        carrinho.add(L1);
        carrinho.add(M2);
        carrinho.add(L2);
        carrinho.add(L3);
        carrinho.add(M3);
            
        for(int i=0; i < carrinho.size(); i++){
            Descricao = carrinho.get(i).getDescricao();
            System.out.println(Descricao);
        }
        
        
    }
    
}
