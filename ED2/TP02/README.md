# Agrupagem de Anagramas - Estrutura de Dados II - 2020.
 
## Informações
 
A descrição completa do trabalho pode ser encontrada no arquivo em PDF presente na pasta.
 
## Descrição
 
Esse código agrupa uma série de N strings em grupos compostos por anagramas.
 
Um arquivo .txt contendo as strings, de tamanho fixo e igual a 5, é passado como entrada para o programa.
 
A saída apresenta os grupos de strings que são anagramas entre si, juntamente com o número total de grupos.
 
Para formar os grupos, o programa constrói uma tabela hash. As strings são ordenadas em ordem alfabética e inseridas na tabela de acordo com uma função hash definida no arquivo Hash.c.
 
## Exemplo de Strings
 
>ihgcb
>
>abghi
>
>gcbih
>
>bgiha
>
>
>gibch
>
>hibcg
 
## Exemplos de Entrada e Saída
 
**Entrada**
 
>teste.txt
 
**Saída**
 
>ihgcb gcbih gibch hibcg
>
>abghi bgiha
>
>Grupos totais: 2

