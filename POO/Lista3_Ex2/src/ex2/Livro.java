/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ex2;

/**
 *
 * @author Murilo
 */
public class Livro extends Produto {
    private String Autor;
     
    public Livro(String Descricao, String Autor){
        this.Descricao = Descricao;
        this.Autor = Autor;
    }
    
    public String getDescricao(){
        return Descricao+"......... Autor: "+Autor;
    }
}
