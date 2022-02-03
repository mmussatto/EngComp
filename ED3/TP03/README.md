# Organização de Arquivos 3 - Estrutura de Dados III - 01/2021.
 
## Informações
 
A descrição completa do trabalho pode ser encontrada no arquivo em PDF presente na pasta.
 
## Descrição
 
Na terceira parte do trabalho, o objetivo era criar um grafo direcionado e não ponderado, utilizando os arquivos de dados criados nas duas primeiras partes do trabalho. O grafo foi construído utilizando a forma de **listas de adjacências**. A principal função do grafo é representar as relações entre as pessoas presentes na base de dados, ou seja, quem segue quem.
 
Vale salientar que os arquivos dos trabalhos 1 e 2 foram reutilizados para esse trabalho. Ou seja, as funcionalidades das duas primeiras partes estão presentes no código desse trabalho.
 
Nessa terceira parte foram implementadas 4 funcionalidades:
 
### Funcionalidade 9
 
Essa funcionalidade é responsável por montar o grafo em questão, utilizando os arquivos binários construídos pelas funcionalidades desenvolvidas nas duas primeiras partes do trabalho. Após montar o grafo, o programa imprime no terminal as listas de adjacência de forma ordenada e com os devidos tratamentos de dados.
 
### Funcionalidade 10
 
Essa funcionalidade é muito similar à funcionalidade 9, porém esta gera o grafo **transposto**. Esse grafo específico será utilizado por outras funcionalidades, como a funcionalidade 11 por exemplo.
 
### Funcionalidade 11
 
Essa funcionalidade calcula o caminho mais curto entre uma celebridade e todas as pessoas que a seguem. O nome da celebridade em questão é fornecido ao programa pelo usuário.
 
Essa funcionalidade utiliza o grafo transposto criado pelo funcionalidade 10. Isso porque, a estratégia utilizada para encontrar o caminho mais curto, é fazer com que a origem seja única. Como queremos o caminho mais curto para todas as pessoas que seguem determinada celebridade, utilizando o grafo transposto, podemos fazer com que o vértice da celebridade seja o vértice de origem da busca.
 
Por fim, o programa imprime no terminal o caminho mais curto entre cada pessoa que segue a celebridade, e a celebridade em si.
 
### Funcionalidade 12
 
Essa funcionalidade é utilizada para verificar se existe um ciclo dentro do grafo. Utilizando a **busca em profundidade**, o programa busca, para cada pessoa, se existe um caminho até ela mesma. Caso haja mais de um ciclo, o programa irá apresentar apenas o primeiro ciclo que foi encontrado.
 
 
## Informações Adicionais
 
Todas as funcionalidades possuem um padrão de entrada e os arquivos envolvidos precisam estar devidamente construídos para que o programa funcione corretamente. Os padrões de entradas e uma descrição mais detalhada de cada funcionalidade pode ser encontrada na descrição do trabalho (PDF na pasta)
 
 
 

