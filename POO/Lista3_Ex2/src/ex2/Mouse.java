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
public class Mouse extends Produto{
    
    private String tipo;
    
    public Mouse(String Descricao, String Tipo){
        this.Descricao = Descricao;
        tipo = Tipo;
    }
    
    public String getDescricao(){
        return Descricao+"......... Tipo: "+tipo;
    }
}
