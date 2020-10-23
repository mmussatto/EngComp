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
public class Produto {
    
    private String Nomeloja;
    private double Preco;
    protected String Descricao = "Produto de Infomatica";
    
    public void setNomeloja(String nomeloja){
        this.Nomeloja = nomeloja;
    }
    
    public String getNomeloja(){
        return Nomeloja;
    }
    
    public void setPreco(double preco){
        this.Preco = preco;
    }
    
    public double getPreco(){
        return Preco;
    }
    
    public String getDescricao(){
        return Descricao;
    }
}
