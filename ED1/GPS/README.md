
# Informações

A descrição completa do trabalho pode ser encontrada no arquivo em PDF presente na pasta.

# Descrição

Esse código recebe uma série de dados de Longitude e Latitude como entrada. 

Ele possui três modos de operação:

- Modo 0: Exiobição de todas as informações já processadas.
    
    Nesse modo são apresentadas todas os dados inseridos na aplicação

- Modo 1: Verificação do excesso de velocidade
    
    Esse modo verifica se o motorista foi "pego" eu um radar

    São necessárias três entradas adicionais:

    * Posição do radar (índice do dado recebido)
    * Alcance do radar
    * Limite máximo de velocidade em m/s

- Modo 2: Simplificação de Caminho

    Esse modo exclui entradas de GPS desnecessárias

    É necessária uma entrada adicional: limite de distância do processo de simplificação, em metros


# Exemplos de Entrada e Saída

## Modo 0

**Enrtrada**

``2
22.01052233 47.88957983
22.01052233 47.88957983
0``

**Saída**

``
22.010522 47.889580 0 0.000000 0.000000
22.010522 47.889580 1 0.000000 0.000000
``

## Modo 1

**Enrtrada**

``
13
22.00517 47.891024
22.005123 47.89104467
22.00508983 47.89108183
22.0050745 47.89113433
22.00507367 47.89119983
22.00508117 47.8912795
22.00509033 47.89136533
22.00509717 47.89145033
22.00510117 47.8915275
22.00510367 47.891594
22.00510417 47.89165233
22.00510483 47.891706
22.00510617 47.8917525
1
4
10.0
8.0
``

**Saída**

``autuado
8.265013``

## Modo 2

**Enrtrada**

``13
22.00517 47.891024
22.005123 47.89104467
22.00508983 47.89108183
22.0050745 47.89113433
22.00507367 47.89119983
22.00508117 47.8912795
22.00509033 47.89136533
22.00509717 47.89145033
22.00510117 47.8915275
22.00510367 47.891594
22.00510417 47.89165233
22.00510483 47.891706
22.00510617 47.8917525
2
20.0``

**Saída**

``22.005170 47.891024 0 0.000000 0.000000
22.005074 47.891134 3 5.680899 16.655015
22.005081 47.891280 5 8.265013 31.680910
22.005097 47.891450 7 8.805825 49.403738
22.005104 47.891594 9 6.869100 64.249984
22.005106 47.891753 12 4.801579 80.611818``
