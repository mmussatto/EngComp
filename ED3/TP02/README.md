# Organização de Arquivos 2 - Estrutura de Dados III - 12/2020.
 
## Informações
 
A descrição completa do trabalho pode ser encontrada no arquivo em PDF presente na pasta.
 
## Descrição
 
Nessa segunda parte do trabalho, foi preciso criar uma arquivo de dados que relaciona os diversos registros do arquivo de dados utilizado no trabalho 1. Esse novo arquivo de dados, denominado *segue*, possui registros de tamanho fixo (32 bytes) e um cabeçalho de mesmo tamanho. Em cada registro é armazenado uma relação entre duas pessoas (pessoas estas que estão armazenadas no arquivo de dados do trabalho 1)
 
As descrições dos campos utilizados podem ser encontradas na especificação do trabalho (PDF na pasta).
 
Vale salientar que os arquivos do trabalho 1 foram reutilizados para esse trabalho. Ou seja, as funcionalidades do trabalho 1 estão presentes no código desse trabalho.
 
Esse trabalho possui 3 funcionalidades e segue a numeração do trabalho anterior.
 
### Funcionalidade 6:
 
Essa funcionalidade é similar à funcionalidade 1 do primeiro trabalho. Assim, ela é responsável por ler a base de dados fornecida no arquivo .csv e montar o arquivo de dados *segue*. Para efeitos de correção, a função "binarioNaTela" também é chamada no final do programa, e retorna um número específico caso o arquivo tenha sido criado corretamente.
 
### Funcionalidade 7:
 
Essa funcionalidade é responsável por ordenar os registros do arquivo *segue* e colocá-los de forma ordenada no arquivo *segueOrdenado*. Para fazer a ordenação, considerou-se que o arquivo de dados poderia ser inteiro armazenado na RAM do computador. Assim, utilizou-se a função *qsort* da biblioteca padrão da linguagem C.
 
### Funcionalidade 8:
 
Essa funcionalidade é uma extensão da funcionalidade 3 do trabalho anterior. Assim, o usuário pode procurar por uma pessoas e o programa irá buscar todas as outras pessoas as quais a primeira segue.
 
O usuário só pode utilizar o campo *idPessoa* para fazer a busca. Portanto, o programa utilizará a funcionalidade 3 para procurar pelas informações da pessoa identificada pelo usuários. Em seguida, o programa fará uma **busca binária** no arquivo *segueOrdenado*, construído pela funcionalidade 7, para achar todas as outras pessoas as quais a primeira segue.
 
Por fim, os dados são apresentados no terminal de forma ordenada e com o devido tratamento.
 
 
## Informações Adicionais
 
Todas as funcionalidades possuem um padrão de entrada e os arquivos envolvidos precisam estar devidamente construídos para que o programa funcione corretamente. Os padrões de entradas e uma descrição mais detalhada de cada funcionalidade pode ser encontrada na descrição do trabalho (PDF na pasta)
 
 
 

