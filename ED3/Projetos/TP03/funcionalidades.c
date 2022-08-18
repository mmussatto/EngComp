/*
|   SCC0607 Estrutura de Dados III
|   Trabalho Pratico 03
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
*/

#include "funcionalidades.h"



/*--------------- Funcionalidade 1 --------------------------------------------*/
void func1(char *arq_entrada, char *arq_pessoa, char *arq_indexa)
{
    /*Arquivo de Entrada*/
    FILE *f_entrada;
    f_entrada = fopen(arq_entrada, "r");
    if(f_entrada == NULL)
    {
        printf("Falha no carregamento do arquivo.");
        return; 
    }

    /*Arquivo de Dados*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "wb");
    if(f_pessoa == NULL)
    {
        printf("Falha no carregamento do arquivo.");
        return; 
    }

    /*Arquivo de Indice Primario*/
    FILE *f_index;
    f_index = fopen(arq_indexa, "wb");
    if(f_index == NULL)
    {
        printf("Falha no carregamento do arquivo.");
        return; 
    }


    /*Inicia Cabecalho*/
    cabecalho_dados c_dados;
    c_dados.status = '0';
    c_dados.qtdPessoas = 0;

    cabecalho_index c_index;
    c_index.status = '0';


    /*Inicia dados*/
    dados d_pessoa;
    d_pessoa.removido = '1';

    int size_indexPessoa = 1;
    indice *indexPessoa = malloc(size_indexPessoa * sizeof(indice)); //vetor de indice
    

    /*Variaveis de Controle*/
    int nome_vazio;         //verifica se o nome eh nulo
    int tam_nome;           //vertifica tamanho do nome
    int tam_twitter;        //vertifica tamanho do twitter
    char barrazero = '\0';  //buffer que armazena o char '\0'
    int cont = 0;           //contador utilizado para o realloc


    /*Escreve cabecalho*/
        /*Arquivo de Dados*/
    fwrite(&c_dados.status,sizeof(char),1,f_pessoa);
    fwrite(&c_dados.qtdPessoas,sizeof(int),1,f_pessoa);
    for (int i = 0; i < 59; i++)
    {
        fwrite(&lixo,sizeof(char),1,f_pessoa);     
    }
        /*Arquivo de Indice*/
    fwrite(&c_index.status, sizeof(char), 1, f_index);
    for (int i = 0; i < 7; i++)
    {
        fwrite(&lixo, sizeof(char), 1, f_index);
    }
    

    fscanf(f_entrada, "%*s[^\n]"); //ignora a primeira linha com a descricao dos campos


    /*Leitura dos Dados*/
    while(fscanf(f_entrada, "%d", &d_pessoa.idPessoa) == 1)
    {
        getc(f_entrada); //ignora virgula

        nome_vazio = fscanf(f_entrada, "%[^,]s", d_pessoa.nomePessoa);
        if (nome_vazio == 0) d_pessoa.nomePessoa[0] = '\0';

        getc(f_entrada); //ignora virgula

        fscanf(f_entrada, "%d[^,]", &d_pessoa.idadePessoa);

        getc(f_entrada); //ignora virgula
        
        fscanf(f_entrada, "%[^\n]s", d_pessoa.twitterPessoa);


        /*Escrita no Arquivo de Dados*/
        EscreveRegistro(&d_pessoa, f_pessoa);
        

        /*Verifica o tamanho do vetor de Indice*/
        if (cont >= size_indexPessoa)
        {
            indexPessoa = realloc(indexPessoa, (cont+1) * sizeof(indice)); //aumenta o vetor de indice
            size_indexPessoa++;             
        }
        
        /*Armazena o Indice*/
        indexPessoa[cont].idPessoa = d_pessoa.idPessoa;
        indexPessoa[cont].RRN = cont;
        cont++;
    }

    /*Ordenacao dos Indices*/
    Insertion_Sort(indexPessoa, size_indexPessoa);

    /*Escrita no Arquivo de Indice*/
    for (int i = 0; i < size_indexPessoa; i++)
    {   
        fwrite(&indexPessoa[i].idPessoa, sizeof(int), 1, f_index);
        fwrite(&indexPessoa[i].RRN, sizeof(int), 1, f_index);   
    }


    /*Reescreve o Cabecalho*/
        /*Arquivo de Indice*/
    fseek(f_index, 0, SEEK_SET);
    c_index.status = '1';
    fwrite(&c_index.status, sizeof(char), 1, f_index);

        /*Arquivo de Dados*/
    fseek(f_pessoa, 0, SEEK_SET);

    c_dados.status = '1';
    fwrite(&c_dados.status,sizeof(char),1,f_pessoa);

    c_dados.qtdPessoas = size_indexPessoa;
    fwrite(&c_dados.qtdPessoas,sizeof(int),1,f_pessoa);

    /*Fecha Arquivos*/
    fclose(f_entrada);
    fclose(f_index);
    fclose(f_pessoa);

    /*Desaloca a memoria do indice*/
    free(indexPessoa);

    /*Funcao fornecida*/
    binarioNaTela1(arq_pessoa, arq_indexa);
    return;

}

/*--------------- Funcionalidade 2 --------------------------------------------*/
void func2(char *arq_pessoa)
{
    /*Arquivo de Dados*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb");
    if(f_pessoa == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Cabecalho*/
    cabecalho_dados c_dados;

    /*Dados*/
    dados d_Pessoa;

    /*Variaveis de Controle*/
    int tam_nome;   //vertifica tamanho do nome
    int RRN = 0;
    int cont = 0;   //contador utilizado no loop          

    /*Verifica o Status do Arquivo de Dados*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }
    
    /*Verifica Quantidade de Pessoas no Arquivo de Dados*/
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa);
    fseek(f_pessoa, TAM_REGISTRO_PESSOA, SEEK_SET);

    if (c_dados.qtdPessoas == 0)
    {//nenhum registro no arquivo de dados
        printf("Registro inexistente.");
        return;
    }
    
    
    /*Leitura do Arquivo de Dados*/
    while(cont < c_dados.qtdPessoas)
    {
        
        fread(&d_Pessoa.removido, sizeof(char), 1, f_pessoa);
        if (d_Pessoa.removido == '0') //registro está removido
        {
            RRN++;
            fseek(f_pessoa, TAM_REGISTRO_PESSOA + RRN*TAM_REGISTRO_PESSOA, SEEK_SET);
            continue; 
        }  

        fread(&d_Pessoa.idPessoa, sizeof(int), 1, f_pessoa);
        fread(&d_Pessoa.nomePessoa, sizeof(char), 40, f_pessoa);
        fread(&d_Pessoa.idadePessoa, sizeof(int), 1, f_pessoa);
        fread(&d_Pessoa.twitterPessoa, sizeof(char), 15, f_pessoa);

        Print(d_Pessoa.idPessoa, d_Pessoa.nomePessoa, d_Pessoa.idadePessoa, d_Pessoa.twitterPessoa);  

        RRN++;
        cont++;
    }

    /*Fecha Arquivos*/
    fclose(f_pessoa);
}

/*--------------- Funcionalidade 3 --------------------------------------------*/
void func3(char *arq_pessoa, char *arq_indexa, char *nome_campo)
{
    /*Arquivo de Dados*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb");
    if(f_pessoa == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Arquivo de Indice Primario*/
    FILE *f_index;
    f_index = fopen(arq_indexa, "rb");
    if(f_index == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }
 
    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;

    /*Dados*/
    dados d_Pessoa;
    int size_indexPessoa;
    indice *indexPessoa; //vetor de indice

    /*Variaveis de Controle*/
    int caso = 0;       //caso de busca
    int RRN;            //RRN do registro desejado
    int achouID;        //flag de busca bem sucedida
    char nome[40];      //usado para armazenar temporariamente o nome
    int idade;          //usado para armazenar temporariamente a idade
    char twitter[15];   //usado para armazenar temporariamente o twitter


    /*Verifica Status Arquivo de Dados*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Identificacao do Caso*/
    if(strcmp(nome_campo, "idPessoa") == 0) caso = 1;
    else if(strcmp(nome_campo, "nomePessoa") == 0) caso = 2;
    else if(strcmp(nome_campo, "idadePessoa") == 0) caso = 3;
    else if(strcmp(nome_campo, "twitterPessoa") == 0) caso = 4;

    /*Busca*/
    switch (caso)
    {
    case 1: //busca por id
       
        /*Leitura do Id*/
        scanf("%d", &d_Pessoa.idPessoa);

        /*Recupera Indice*/
        size_indexPessoa = RecuperaIndice(f_index, &indexPessoa);

        /*Busca pelo Id no Vetor de Indice*/
        achouID = BuscaBinaria(indexPessoa, size_indexPessoa, d_Pessoa.idPessoa);

        /*Recupera Regsitro Buscado*/
        if (achouID != -1) //achou o id
        {
            /*Posicao do cursor no RRN desejado*/
            RRN = indexPessoa[achouID].RRN;
            fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
            
            /*Verifica se o registro esta removido*/
            fread(&d_Pessoa.removido, sizeof(char), 1, f_pessoa);
            if (d_Pessoa.removido == '0')
            {
                printf("Registro inexistente."); 
                return;  
            }  

            fread(&d_Pessoa.idPessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.nomePessoa, sizeof(char), 40, f_pessoa);
            fread(&d_Pessoa.idadePessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.twitterPessoa, sizeof(char), 15, f_pessoa);

            /*Impressao na tela*/
            Print(d_Pessoa.idPessoa, d_Pessoa.nomePessoa, d_Pessoa.idadePessoa, d_Pessoa.twitterPessoa);  

        }
        else //nao achou o id
        {
            printf("Registro inexistente.");
            return;
        }
        break;

    case 2: //busca por nome
       
        /*Leitura do Nome*/
        scan_quote_string(nome);

        fseek(f_pessoa, TAM_REGISTRO_PESSOA, SEEK_SET); //pula o cabecalho

        /*Percorre o arquivo de Dados*/
        while (fread(&d_Pessoa.removido, sizeof(char), 1, f_pessoa) == 1)
        { 
            fread(&d_Pessoa.idPessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.nomePessoa, sizeof(char), 40, f_pessoa);
            fread(&d_Pessoa.idadePessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.twitterPessoa, sizeof(char), 15, f_pessoa);
   
            if (strcmp(d_Pessoa.nomePessoa, nome) == 0) //possui o nome buscado
            {
                if (d_Pessoa.removido == '0') continue;

                /*Impressao na tela*/    
                Print(d_Pessoa.idPessoa, d_Pessoa.nomePessoa, d_Pessoa.idadePessoa, d_Pessoa.twitterPessoa);  
            }
        }

        break;

    case 3: //busca por idade
   
        /*Leitura do Id*/
        scanf("%d", &idade);

        fseek(f_pessoa, TAM_REGISTRO_PESSOA, SEEK_SET); //pula o cabecalho

        /*Percorre o arquivo de Dados*/
        while (fread(&d_Pessoa.removido, sizeof(char), 1, f_pessoa) == 1)
        { 
            fread(&d_Pessoa.idPessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.nomePessoa, sizeof(char), 40, f_pessoa);
            fread(&d_Pessoa.idadePessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.twitterPessoa, sizeof(char), 15, f_pessoa);
   
            if (d_Pessoa.idadePessoa == idade) //possui a idade buscada
            {
                if (d_Pessoa.removido == '0') continue;

                /*Impressao na tela*/
                Print(d_Pessoa.idPessoa, d_Pessoa.nomePessoa, d_Pessoa.idadePessoa, d_Pessoa.twitterPessoa);  
            }
        }

        break;

    case 4: //busca por twitter

        /*Leitura do Nome*/
        scan_quote_string(twitter);

        fseek(f_pessoa, TAM_REGISTRO_PESSOA, SEEK_SET); //pula o cabecalho

        /*Percorre o arquivo de Dados*/
        while (fread(&d_Pessoa.removido, sizeof(char), 1, f_pessoa) == 1)
        { 
            fread(&d_Pessoa.idPessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.nomePessoa, sizeof(char), 40, f_pessoa);
            fread(&d_Pessoa.idadePessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.twitterPessoa, sizeof(char), 15, f_pessoa);
   
            if (strcmp(d_Pessoa.twitterPessoa, twitter) == 0) //possui o nome buscado
            {
                if (d_Pessoa.removido == '0') continue;

                /*Impressao na tela*/
                Print(d_Pessoa.idPessoa, d_Pessoa.nomePessoa, d_Pessoa.idadePessoa, d_Pessoa.twitterPessoa);  
            }
        }

        break;

    default:
        break;
    }


}

/*
      Essa funcionalidade foi modificada para isolar o caso de busca por id. 
      Além disso, a função agora retorna um inteiro (0 ou 1) indicando se o id foi encontrado
    no arquivo de dados pessoa.

      Na funcionalidade original, era utilizado um scanf para ler o valor buscado, mas como o valor 
    já foi lio na funcionalidade 8, foi mais fácil criar outra função que contornasse o problema.
      Outro problema que foi contornado com essa funcão modificada, foi a abertura dos arquivos. 
    Enquanto a funcionalidade 3 original abria os arquivos, na função modificada considera que eles já foram abertos 
    na funcionalidade 8.

      Por fim, utilizei um ponteiro do tipo struct dados, para retornar o registro lido para a função 8.

*/
int func3_modificada(FILE *f_pessoa, FILE *f_index, char *nome_campo, int valor, dados *d)
{

    /*Dados*/
    dados d_Pessoa;
    int size_indexPessoa;
    indice *indexPessoa; //vetor de indice


    /*Variaveis de Controle*/
    int achouID;        //flag de busca bem sucedida
    int RRN;            //RRN do registro desejado


    /*Leitura do Id*/
        //scanf("%d", &d_Pessoa.idPessoa);
        d_Pessoa.idPessoa = valor;

        /*Recupera Indice*/
        size_indexPessoa = RecuperaIndice(f_index, &indexPessoa);

        /*Busca pelo Id no Vetor de Indice*/
        achouID = BuscaBinaria(indexPessoa, size_indexPessoa, d_Pessoa.idPessoa);

        /*Recupera Regsitro Buscado*/
        if (achouID != -1) //achou o id
        {
            /*Posicao do cursor no RRN desejado*/
            RRN = indexPessoa[achouID].RRN;
            fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
            
            /*Verifica se o registro esta removido*/
            fread(&d_Pessoa.removido, sizeof(char), 1, f_pessoa);
            if (d_Pessoa.removido == '0')
            {
                printf("Registro inexistente."); 
                return 0;  
            }  

            fread(&d_Pessoa.idPessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.nomePessoa, sizeof(char), 40, f_pessoa);
            fread(&d_Pessoa.idadePessoa, sizeof(int), 1, f_pessoa);
            fread(&d_Pessoa.twitterPessoa, sizeof(char), 15, f_pessoa);

              

            *d = d_Pessoa; //retorna o registro por meio de um ponteiro
            return 1;

        }
        else //nao achou o id
        {
            printf("Registro inexistente.");
            return 0;
        }
        

}

/*--------------- Funcionalidade 4 --------------------------------------------*/
void func4(char *arq_pessoa, char *arq_indexa, int n)
{
    /*Arquivo de Dados*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb+"); 
    if(f_pessoa == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Arquivo de Indice Primario*/
    FILE *f_index;
    f_index = fopen(arq_indexa, "rb+");
    if(f_index == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }
 
    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;

    /*Dados*/
    dados d_Pessoa;
    d_Pessoa.removido = '1';

    /*Indice*/
    int size_indexPessoa;
    indice *indexPessoa;

    /*Verifica Status Arquivo de Dados*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa);

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Recupera Indice*/
    size_indexPessoa = RecuperaIndice(f_index, &indexPessoa);
    //Print_Indice(indexPessoa, size_indexPessoa);


    /*Reescreve o Cabecalho*/
        /*Arquivo de Indice*/
    fseek(f_index, 0, SEEK_SET);
    c_index.status = '0';
    fwrite(&c_index.status, sizeof(char), 1, f_index);

        /*Arquivo de Dados*/
    fseek(f_pessoa, 0, SEEK_SET);
    c_dados.status = '0';
    fwrite(&c_dados.status,sizeof(char),1,f_pessoa);   


    /*Calculo do RRN do Arquivo de Dados*/
    fseek(f_pessoa, 0, SEEK_END);
    int tam_f_pessoa = ftell(f_pessoa);
    int num_RRN = (tam_f_pessoa/TAM_REGISTRO_PESSOA)-1; //subtrai 1 pois eh o cabecalho

    /*Leitura e Escrita dos Dados*/
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &d_Pessoa.idPessoa);        //le id
        scan_quote_string(d_Pessoa.nomePessoa); //le nome
        scanf("%d", &d_Pessoa.idadePessoa);     //le idade
        scanf("%s", d_Pessoa.twitterPessoa);    //le twitter

        /*Escrita no Arquivo de Dados*/
        EscreveRegistro(&d_Pessoa, f_pessoa);
        

        /*Aumento do Vetor de Indice*/
        size_indexPessoa++;
        indexPessoa = realloc(indexPessoa, (size_indexPessoa) * sizeof(indice)); //aumenta o vetor de indice

        /*Inclui Indice*/
        indexPessoa[size_indexPessoa-1].idPessoa = d_Pessoa.idPessoa;
        indexPessoa[size_indexPessoa-1].RRN = num_RRN;
        num_RRN++;

        /*Aumenta Quantidade de Pessoas no Arquivo de Dados*/
        c_dados.qtdPessoas++;

    }

    /*Ordenacao do Vetor de Indice*/
    Insertion_Sort(indexPessoa, size_indexPessoa);
    //Print_Indice(indexPessoa, size_indexPessoa);


    /*Escrita no Arquivo de Indice*/
    fseek(f_index, TAM_REGISTRO_INDICE, SEEK_SET);
    for (int i = 0; i < size_indexPessoa; i++)
    {   
        fwrite(&indexPessoa[i].idPessoa, sizeof(int), 1, f_index);
        fwrite(&indexPessoa[i].RRN, sizeof(int), 1, f_index);   
    }
    
    /*Reescreve o Cabecalho*/
        /*Arquivo de Indice*/
    fseek(f_index, 0, SEEK_SET);
    c_index.status = '1';
    fwrite(&c_index.status, sizeof(char), 1, f_index);

        /*Arquivo de Dados*/
    fseek(f_pessoa, 0, SEEK_SET);
    c_dados.status = '1';
    fwrite(&c_dados.status,sizeof(char),1,f_pessoa);
    c_dados.qtdPessoas = size_indexPessoa;
    fwrite(&c_dados.qtdPessoas,sizeof(int),1,f_pessoa);

    /*Fecha Arquivos*/
    fclose(f_index);
    fclose(f_pessoa);

    /*Desaloca a memoria do indice*/
    free(indexPessoa);
    
    /*Funcao Fornecida*/
    binarioNaTela1(arq_pessoa, arq_indexa);
    return;    
}

/*--------------- Funcionalidade 5 --------------------------------------------*/
void func5(char *arq_pessoa, char *arq_indexa, int n)
{
    /*Arquivo de Dados*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb+"); 
    if(f_pessoa == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Arquivo de Indice Primario*/
    FILE *f_index;
    f_index = fopen(arq_indexa, "rb+");
    if(f_index == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }
 
    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;

    /*Dados*/
    dados d_Pessoa;
    dados d_busca;

    /*Indice*/
    int size_indexPessoa;
    indice *indexPessoa;

    /*Variaveis de Controle*/
    int mudou_indice = 0;       //flag para alteracao no arq indice -> serve para decidir se reordena ou nao
    char campo_busca[30];       //guarda o nome do campo de busca
    char campo_altera[30];      //guarda o nome do campo de alteracao
    int caso = 0;               //identificador do tipo de busca
    int m;                      //valor m dado na entrada
    int muda_campo[] = {0, 0, 0, 0};    //vetor que identifica quais campos mudaram: [0]->id; [1]->nome; [2]->idade; [3]->twitter

    /*Verifica Status Arquivo de Dados*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa); //le quantidade de pessoas

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Recupera Indice*/
    size_indexPessoa = RecuperaIndice(f_index, &indexPessoa);
    //Print_Indice(indexPessoa, size_indexPessoa);

    /*Reescreve o Cabecalho*/
        /*Arquivo de Indice*/
    fseek(f_index, 0, SEEK_SET);
    c_index.status = '0';
    fwrite(&c_index.status, sizeof(char), 1, f_index);

        /*Arquivo de Dados*/
    fseek(f_pessoa, 0, SEEK_SET);
    c_dados.status = '0';
    fwrite(&c_dados.status,sizeof(char),1,f_pessoa);   


    /*Leitura das Entradas*/
    for (int i = 0; i < n; i++)
    {
        /*Reset Vetor de Mudancas*/
        for (int j = 0; j < 4; j++) muda_campo[j] = 0;        

        /*Leitura do Campo de Busca*/
        scanf("%s", campo_busca); //le sobre qual vai ocorre a busca

        if(strcmp(campo_busca, "idPessoa") == 0) caso = 1;
        else if(strcmp(campo_busca, "nomePessoa") == 0) caso = 2;
        else if(strcmp(campo_busca, "idadePessoa") == 0) caso = 3;
        else if(strcmp(campo_busca, "twitterPessoa") == 0) caso = 4;

        switch (caso)
        {
        case 1: //busca por id
            scanf("%d %d", &d_busca.idPessoa, &m); 
            break;

        case 2: //busca por nome
            scan_quote_string(d_busca.nomePessoa); 
            scanf("%d", &m);                        
            break;

        case 3: //busca por idade
            scanf("%d %d", &d_busca.idadePessoa, &m);
            break;

        case 4: //busca por twitter
            scan_quote_string(d_busca.twitterPessoa);
            scanf("%d", &m);
            break;      

        default:
            return;
        }


        /*Leitura das Alteracoes*/
        for (int j = 0; j < m; j++)
        {
            scanf("%s", campo_altera);

            if(strcmp(campo_altera, "idPessoa") == 0) //altera id
            {
                scanf("%d", &d_Pessoa.idPessoa);
                muda_campo[0] = 1;
                mudou_indice = 1; //vetor precisa ser reordenado antes de escrever no arq indice
                
            }
            else if(strcmp(campo_altera, "nomePessoa") == 0) //altera nome
            {
                scan_quote_string(d_Pessoa.nomePessoa);
                muda_campo[1] = 1;
            }
            else if(strcmp(campo_altera, "idadePessoa") == 0) //altera idade
            {
                scanf("%d", &d_Pessoa.idadePessoa);
                muda_campo[2] = 1;
            }
            else if(strcmp(campo_altera, "twitterPessoa") == 0) //altera twitter
            {
                scan_quote_string(d_Pessoa.twitterPessoa); 
                muda_campo[3] = 1;
            }
        }

        /*Altera os Campos Desejados*/
        Altera(&d_busca, &d_Pessoa, caso, muda_campo, f_pessoa, indexPessoa, size_indexPessoa);

        /*Reordena Vetor de Indice se Necessario*/
        if (mudou_indice == 1) 
        {
            Insertion_Sort(indexPessoa, size_indexPessoa); //reordena indice
            mudou_indice = 0;        
        } 
        

    }


    /*Escrita no Arquivo de Indice*/
    fseek(f_index, TAM_REGISTRO_INDICE, SEEK_SET);
    for (int i = 0; i < size_indexPessoa; i++)
    {   
        fwrite(&indexPessoa[i].idPessoa, sizeof(int), 1, f_index);
        fwrite(&indexPessoa[i].RRN, sizeof(int), 1, f_index);   
    }
    
    
    
    /*Reescreve o Cabecalho*/
        /*Arquivo de Indice*/
    fseek(f_index, 0, SEEK_SET);
    c_index.status = '1';
    fwrite(&c_index.status, sizeof(char), 1, f_index);

        /*Arquivo de Dados*/
    fseek(f_pessoa, 0, SEEK_SET);
    c_dados.status = '1';
    fwrite(&c_dados.status,sizeof(char),1,f_pessoa);
    c_dados.qtdPessoas = size_indexPessoa;
    fwrite(&c_dados.qtdPessoas,sizeof(int),1,f_pessoa);

    /*Fecha Arquivos*/
    fclose(f_index);
    fclose(f_pessoa);

    /*Desaloca a memoria do indice*/
    free(indexPessoa);

    /*Funcao Fornecida*/
    binarioNaTela1(arq_pessoa, arq_indexa);

    return;

}

/*--------------- Funcionalidade 6 --------------------------------------------*/
void func6(char *arq_entrada, char *arq_segue)
{
    /*Arquivo de Entrada*/
    FILE *f_entrada;
    f_entrada = fopen(arq_entrada, "r");
    if(f_entrada == NULL)
    {
        printf("Falha no carregamento do arquivo.");
        return; 
    }

    /*Arquivo de Dados*/
    FILE *f_segue;
    f_segue = fopen(arq_segue, "wb");
    if(f_segue == NULL)
    {
        printf("Falha no carregamento do arquivo.");
        return; 
    }


    /*Inicia Cabecalho*/
    cabecalho_segue c_segue;
    c_segue.status = '0';
    c_segue.qtdSeguidores = 0;    

    /*Inicia dados*/
    segue d_segue;
    d_segue.removido = '1';


    /*Escreve Cabecalho*/
    fwrite(&c_segue.status, sizeof(char), 1, f_segue);
    fwrite(&c_segue.qtdSeguidores, sizeof(int), 1, f_segue);
    for(int i = 0; i < 27; i++) 
        fwrite(&lixo, sizeof(char), 1 ,f_segue);
   

    /*Variaveis de Controle*/
    int grauAmizade;

    fscanf(f_entrada, "%*s[^\n]"); //ignora a primeira linha com a descricao dos campos


    /*Leitura de Dados*/
    while (fscanf(f_entrada, "%d", &d_segue.idSegue) == 1)
    {
        getc(f_entrada); //ignora virgula

        fscanf(f_entrada, "%d[^,]", &d_segue.idSeguido);

        getc(f_entrada); //ignora virgula

        fscanf(f_entrada, "%[^,]s", d_segue.grauAmizade);

        getc(f_entrada); //ignora virgula
    
        fscanf(f_entrada, "%[^,]s", d_segue.dataInicio);

        getc(f_entrada); //ignora virgula
        
        fscanf(f_entrada, "%[^\n]s", d_segue.dataFim);

        EscreveRegistroSegue(&d_segue, f_segue);
        c_segue.qtdSeguidores++;
    }

    /*Reescreve Cabecalho*/
    fseek(f_segue, 0, SEEK_SET);
    c_segue.status = '1';
    fwrite(&c_segue.status, sizeof(char), 1, f_segue);
    fwrite(&c_segue.qtdSeguidores, sizeof(int), 1, f_segue);
    for(int i = 0; i < 27; i++) 
        fwrite(&lixo, sizeof(char), 1 ,f_segue);

    /*Fecha Arquivos*/
    fclose(f_segue);
    fclose(f_entrada);

    /*Funcao fornecida*/
    binarioNaTela2(arq_segue);
    return;

}

/*--------------- Funcionalidade 7 --------------------------------------------*/
void func7(char *arq_segue, char *arq_sOrdenado)
{
    /*Arquivo de Dados*/
    FILE *f_segue;
    f_segue = fopen(arq_segue, "rb");
    if(f_segue == NULL)
    {
        printf("Falha no carregamento do arquivo.");
        return; 
    }

    /*Arquivo de Dados Ordenado*/
    FILE *f_sOrdenado;
    f_sOrdenado = fopen(arq_sOrdenado, "wb");
    if(f_sOrdenado == NULL)
    {
        printf("Falha no carregamento do arquivo.");
        return; 
    }


    /*Inicia Cabecalho*/
    cabecalho_segue c_segue;
    c_segue.status;
    c_segue.qtdSeguidores;    
    
    fread(&c_segue.status, sizeof(char), 1, f_segue);
    if (c_segue.status == '0')
    {
        printf("Falha no carregamento do arquivo.");
        return;
    }
    fread(&c_segue.qtdSeguidores, sizeof(int), 1 ,f_segue);

    cabecalho_segue c_sOrdenado;
    c_sOrdenado.status = '0';
    c_sOrdenado.qtdSeguidores = c_segue.qtdSeguidores;    

    /*Escreve Cabecalho do Arquivo Ordenado*/
    fwrite(&c_sOrdenado.status, sizeof(char), 1, f_sOrdenado);
    fwrite(&c_sOrdenado.qtdSeguidores, sizeof(int), 1, f_sOrdenado);
    for(int i = 0; i < 27; i++) 
        fwrite(&lixo, sizeof(char), 1 ,f_sOrdenado);


    /*Incia dados*/
    segue *d_segue;

    /*Recupera Registros do Arquivo de Dados Segue*/
    RecuperaSegue(f_segue, &d_segue, c_segue.qtdSeguidores);

    /*Ordena Vetor de Registros*/
    qsort(d_segue, c_segue.qtdSeguidores, sizeof(segue), Comparador);

    /*Escreve Registros no Arquivo Ordenado*/
    for (int i = 0; i < c_segue.qtdSeguidores; i++)
    {
        EscreveRegistroSegue(&d_segue[i], f_sOrdenado);
    }


    /*Reescreve Cabecalho*/
    fseek(f_sOrdenado, 0, SEEK_SET);
    c_sOrdenado.status = '1';
    fwrite(&c_sOrdenado.status, sizeof(char), 1, f_sOrdenado);
    fwrite(&c_sOrdenado.qtdSeguidores, sizeof(int), 1, f_sOrdenado);

    /*Fecha Arquivos*/
    fclose(f_segue);
    fclose(f_sOrdenado);

    /*Funcao Fornecida*/
    binarioNaTela2(arq_sOrdenado);

    return;
}

/*--------------- Funcionalidade 8 --------------------------------------------*/
void func8(char *arq_pessoa, char *arq_indexa, char *nome_campo, int n, char *arq_sOrdenado)
{   
    /*Abertura de Arquivos*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb");
    if(f_pessoa == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    FILE *f_index;
    f_index = fopen(arq_indexa, "rb");
    if(f_index == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    FILE *f_segue;
    f_segue = fopen(arq_sOrdenado, "rb");
    if(f_segue == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }


    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;
    cabecalho_segue c_segue;

    /*Verifica Status Arquivo de Dados Pessoa*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa);

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return; 
    }

    /*Verifica Status Arquivo de Dados Segue*/
    fread(&c_segue.status, sizeof(char), 1, f_segue);
    if(c_segue.status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return;    
    }
    fread(&c_segue.qtdSeguidores, sizeof(int), 1, f_segue);

    /*Registros*/
    dados d_pessoa;
    segue *d_segue;

    /*Variaveis de Controle*/
    int achouID;    //achou id no arquivo de dados pessoa
    int achouSegue; //achou id no arquivo de dados segue

    /*Procura o ID Pessoa*/
    achouID = func3_modificada(f_pessoa, f_index, nome_campo, n, &d_pessoa);

    if(achouID == 0) return;    //nao achou o id no arquivo pessoa

    /*Carrega arquivo segue para a RAM*/
    RecuperaSegue(f_segue, &d_segue, c_segue.qtdSeguidores);

    /*Procura o ID no arquivo Segue*/
    achouSegue = BuscaBinaria_Segue(d_segue, c_segue.qtdSeguidores, d_pessoa.idPessoa);

    if (achouSegue == -1) //nao achou o id no arquivo segue
    {
        printf("Registro inexistente.");
        return;
    }
    

    /*Impressao na tela*/
    Print(d_pessoa.idPessoa, d_pessoa.nomePessoa, d_pessoa.idadePessoa, d_pessoa.twitterPessoa);

    while (d_segue[achouSegue].idSegue == d_pessoa.idPessoa)
    {
        PrintSegue(d_segue[achouSegue]);
        printf("\n");
        achouSegue++;
    }
    
}

/*--------------- Funcionalidade 9 --------------------------------------------*/
void func9(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado)
{
    /*Abertura de Arquivos*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb");
    if(f_pessoa == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_index;
    f_index = fopen(arq_indexa, "rb");
    if(f_index == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_segue;
    f_segue = fopen(arq_sOrdenado, "rb");
    if(f_segue == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }


    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;
    cabecalho_segue c_segue;

    /*Verifica Status Arquivo de Dados Pessoa*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa);

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    /*Verifica Status Arquivo de Dados Segue*/
    fread(&c_segue.status, sizeof(char), 1, f_segue);
    if(c_segue.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return;    
    }
    fread(&c_segue.qtdSeguidores, sizeof(int), 1, f_segue);

    /*Grafo*/
    Grafo g;
    criaGrafo(&g, c_dados.qtdPessoas);

    controiGrafo(&g, f_pessoa, f_index, f_segue, c_segue.qtdSeguidores);
    
    /*Imprime Grafo*/
    imprimeGrafo(&g);

    /*Fecha Arquivos*/
    fclose(f_pessoa);
    fclose(f_index);
    fclose(f_segue);

    /*Desaloca a memoria*/

    liberaGrafo(g.li);

}

/*--------------- Funcionalidade 10 --------------------------------------------*/
void func10(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado)
{
    /*Abertura de Arquivos*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb");
    if(f_pessoa == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_index;
    f_index = fopen(arq_indexa, "rb");
    if(f_index == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_segue;
    f_segue = fopen(arq_sOrdenado, "rb");
    if(f_segue == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;
    cabecalho_segue c_segue;

    /*Verifica Status Arquivo de Dados Pessoa*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa);

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    /*Verifica Status Arquivo de Dados Segue*/
    fread(&c_segue.status, sizeof(char), 1, f_segue);
    if(c_segue.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return;    
    }
    fread(&c_segue.qtdSeguidores, sizeof(int), 1, f_segue);


    /*Grafo*/
    Grafo g;
    criaGrafo(&g, c_dados.qtdPessoas);

    controiGrafoT(&g, f_pessoa, f_index, f_segue, c_segue.qtdSeguidores);
    
    
    /*Imprime Grafo*/
    imprimeGrafo(&g);

    /*Fecha Arquivos*/
    fclose(f_pessoa);
    fclose(f_index);
    fclose(f_segue);


    /*Desaloca a memoria*/
    liberaGrafo(g.li);
}     

/*--------------- Funcionalidade 11 --------------------------------------------*/
void func11(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado)
{

    /*Abertura de Arquivos*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb");
    if(f_pessoa == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_index;
    f_index = fopen(arq_indexa, "rb");
    if(f_index == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_segue;
    f_segue = fopen(arq_sOrdenado, "rb");
    if(f_segue == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;
    cabecalho_segue c_segue;

    /*Verifica Status Arquivo de Dados Pessoa*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa);

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    /*Verifica Status Arquivo de Dados Segue*/
    fread(&c_segue.status, sizeof(char), 1, f_segue);
    if(c_segue.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return;    
    }
    fread(&c_segue.qtdSeguidores, sizeof(int), 1, f_segue);

    /*Le nome da celebridade*/
    char celebridade[40];
    scan_quote_string(celebridade);


    /*Grafo*/
    Grafo g;
    criaGrafo(&g, c_dados.qtdPessoas);
    controiGrafo(&g, f_pessoa, f_index, f_segue, c_segue.qtdSeguidores);

    Grafo gT;
    criaGrafo(&gT, c_dados.qtdPessoas);
    controiGrafoT(&gT, f_pessoa, f_index, f_segue, c_segue.qtdSeguidores);

    int ordem[g.V+1];

    BFS(&gT, celebridade, ordem);

    imprimeCeleb(&g, ordem);
    
    /*Fecha Arquivos*/
    fclose(f_pessoa);
    fclose(f_index);
    fclose(f_segue);

    /*Desaloca a memoria*/
    liberaGrafo(g.li);
    liberaGrafo(gT.li);
}


void func12(char *arq_pessoa, char *arq_indexa, char *arq_sOrdenado)
{
    /*Abertura de Arquivos*/
    FILE *f_pessoa;
    f_pessoa = fopen(arq_pessoa, "rb");
    if(f_pessoa == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_index;
    f_index = fopen(arq_indexa, "rb");
    if(f_index == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    FILE *f_segue;
    f_segue = fopen(arq_sOrdenado, "rb");
    if(f_segue == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    /*Cabecalho*/
    cabecalho_dados c_dados;
    cabecalho_index c_index;
    cabecalho_segue c_segue;

    /*Verifica Status Arquivo de Dados Pessoa*/
    fread(&c_dados.status, sizeof(char), 1, f_pessoa);
    if (c_dados.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }
    fread(&c_dados.qtdPessoas, sizeof(int), 1, f_pessoa);

    /*Verifica Status Arquivo de Indice*/
    fread(&c_index.status, sizeof(char), 1, f_index);
    if (c_index.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return; 
    }

    /*Verifica Status Arquivo de Dados Segue*/
    fread(&c_segue.status, sizeof(char), 1, f_segue);
    if(c_segue.status != '1')
    {
        printf("Falha na execução da funcionalidade.");
        return;    
    }
    fread(&c_segue.qtdSeguidores, sizeof(int), 1, f_segue);


    /*Le nome da nome de quem gerou a Fofoca*/
    char nomeFofoca[40];
    scan_quote_string(nomeFofoca);


    /*Grafo*/
    Grafo g;
    criaGrafo(&g, c_dados.qtdPessoas);
    controiGrafo(&g, f_pessoa, f_index, f_segue, c_segue.qtdSeguidores);

    int id = buscaID(&g, nomeFofoca);
    int ordem[g.V+1];

    int ciclo = DFS(&g, id, ordem);
    if (ciclo == -1)
        printf("A FOFOCA NAO RETORNOU");
    else
        printf("%d", ciclo);
    
    

    /*Fecha Arquivos*/
    fclose(f_pessoa);
    fclose(f_index);
    fclose(f_segue);

    /*Desaloca a memoria*/
    liberaGrafo(g.li);

}

