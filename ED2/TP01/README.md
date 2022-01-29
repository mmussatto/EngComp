# Flood Fill - Estrutura de Dados II - 2020. 
  
## Informações

A descrição completa do trabalho pode ser encontrada no arquivo em PDF presente na pasta.

## Descrição

Esse código utiliza o algoritmo Flood Fill para determinar posições conectadas dentro de uma matriz. 

A matriz deve estar presente dentro de um arquivo .txt, que será passado como entrada para o progrma. Ela deve ser constituída de valores '0' ou '1'. Além disso, seu tamanho deve estar especificado antes da matriz em si e uma posição para comecar o algoritmo deve estar presente após a matriz.

O código lê a matriz do arquivo e constrói uma matriz dinâmica usando listas ligadas. O algortimos Flood Fill é então utilizado para verificar, recursivamente, posições de valor '1' conectadas entre si. Essas posições são apresentadas na saída do programa.

Por fim, a saída apresenta tbm uma contagem de operações.

## Exemplo de Matriz

>8 10
>
>0 0 0 0 0 0 0 0 0 0
>
>0 0 1 1 0 0 0 0 0 0
>
>0 0 0 0 1 1 0 0 0 0
>
>0 0 0 0 1 1 0 0 0 0
>
>0 0 1 1 1 0 0 0 0 0
>
>0 0 0 0 1 0 0 0 0 0
>
>0 0 0 0 0 0 0 0 0 0
>
>0 0 1 1 0 0 0 0 0 0
>
>1 2

## Exemplos de Entrada e Saída

**Entrada**

>teste.txt

**Saída**

>Total: 10
>
>1 2
>
>1 3
>
>2 4
>
>2 5
>
>3 4
>
>3 5
>
>4 2
>
>4 3
>
>4 4
>
>5 4
>
>Total Operacoes: 329



