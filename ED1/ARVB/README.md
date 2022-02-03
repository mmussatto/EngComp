# Trabalho de Árvores do curso de Estrutura de Dados 1 - 12/2019.
 
## Informações
 
A descrição completa do trabalho pode ser encontrada no arquivo em PDF presente na pasta.
 
## Descrição
 
Esse código possui duas etapas:
 
1. Primeiramente é construída uma árvore de decisões binária. A semântica utilizada pode ser analisada no PDF presente na pasta.
2. Inserção de dados conhecidos e escolha da decisão final.
 
## Exemplos de Entrada e Saída
 
**Entrada**
 
>7
>
>B000 "E estudante?" R000
>
>C000 "Nao liberar o emprestimo" B000 E 258.08
>
>B001 "Trabalha?" B000 D
>
>C001 "Nao liberar o emprestimo" B001 D 235.4
>
>N000 "Qual e o salario anual?" 24000.0 B001 E
>
>C002 "Liberar ate 10 mil reais" N000 E 115.85
>
>C003 "Liberar ate 15 mil reais" N000 D 42.31
>
>4
>
>E V
>
>E F E F
>
>E F E V E 32000.0
>
>E F N
 
 
**Saída**
 
>Nao liberar o emprestimo
>
>Nao liberar o emprestimo
>
>Liberar ate 15 mil reais
>
>Nao liberar o emprestimo
 
 
 
 

