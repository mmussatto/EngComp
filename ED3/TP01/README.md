# Organização de Arquivos - Estrutura de Dados III - 11/2020.
 
## Informações
 
A descrição completa do trabalho pode ser encontrada no arquivo em PDF presente na pasta.
 
## Descrição
 
Nessa primeira parte do trabalho, foi preciso ler uma base de dados (arquivo .csv disponibilizado pelo docente) e organizar os dados em um arquivo binário. Esse arquivo possui um cabeçalho (64 bytes) e é dividido em registros de tamanho fixo (64 bytes) contendo as informações da base de dados.
 
Além disso, foi preciso construir um **Arquivo de Índice** para indexar as entradas do arquivo principal. Este arquivo de índice possui um cabeçalho (8 bytes) e é dividido em campos de tamanho fixo (8 bytes).
 
As descrições dos campos, dos dois arquivos, podem ser encontradas na especificação do trabalho (PDF na pasta)
 
O programa em si possui 5 funcionalidades:
 
 
 
### Funcionalidade 1:
 
Para essa funcionalidade, o programa lê o arquivo .csv fornecido e cria os arquivos binários de dados e de índice. Para efeitos de correção, a função "binarioNaTela" era chamada no final do programa, e retornava um número específico caso o arquivo tivesse sido criado corretamente.
 
### Funcionalidade 2:
 
Essa funcionalidade permite a recuperação dos dados armazenados no arquivo binários criado. Os registros são mostrados no terminal com o devido tratamento.
 
### Funcionalidade 3:
 
A funcionalidade 3 permite a busca de registros que satisfazem uma determinada condição. O usuário pode escolher qualquer um dos campos para fazer a procura. Entretanto, se ele optar por fazer a busca utilizando o campo *idPessoa*, o arquivo de índice é utilizado para fazer a busca, juntamente com o algoritmo de **Busca Binária**.
 
### Funcionalidade 4
 
Essa funcionalidade permite a inclusão de registros adicionais ao arquivo de dados. Para isso ela procura por registros *logicamente removidos* e substitui os campos pelas informações passadas pelo usuário, fazendo o devido truncamento dos dados quando necessário. Ela pode ser executada diversas vezes em sequência
 
### Funcionalidade 5
 
Essa funcionalidade permite a atualização dos campos de um ou mais registros, que foram encontrados utilizando a funcionalidade 3. O programa faz o devido tratamento dos dados, como truncamento e identificação de dados nulos. Além disso, caso o campo *idPessoa* fosse alterado, o programa faz as devidas alterações no arquivo de índice para manter a consistência dos dois arquivos.
 
 
## Informações Adicionais

Todas as funcionalidades possuem um padrão de entrada e os arquivos envolvidos precisam estar devidamente construídos para que o programa funcione corretamente. Os padrões de entradas e uma descrição mais detalhada de cada funcionalidade pode ser encontrada na descrição do trabalho (PDF na pasta)
 

