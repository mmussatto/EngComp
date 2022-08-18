#include "funcionalidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_REGISTRO_PESSOA 64
#define TAM_REGISTRO_INDICE 8

char lixo = '$'; //variavel global que representa o lixo

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




/*
    Essa funcao eh utilizada pela funcionalidade 5 para fazer a busca do registro requisitado.

    Para isso, ela recebe duas structs do tipo "dados": busca e muda. A primeira struct contem
    os dados que devem ser usados para selecionar os registros. A segunda possui os dados que serao
    escritos no arquivo de dados. 
    
    Utilizando o inteiro "caso", eh selecionado qual campo da struct "busca" sera utilizado para realizar
    a busca dos registros.

    As variaveis *index e size_index sao utilizadas apenas quando a variavel "caso" vale 1. Ou seja,  
    na busca por id.

    Apos achados os registros que devem ser alterados, eh chamada a funcao "MudaCampos" para que os campos
    sejam alterados respeitando a solicitacao do usuario.

    Por fim eh chamada a funcao "EscreveRegistro" para escrever no arquivo de dados.



    \param *busca       dados que devem ser buscados 
    \param *muda        dados que devem ser alterados
    \param caso         caso de busca: [1]->id, [2]->nome, [3]->idade, [4]->twitter
    \param *muda_campo  vetor que identifica quais campos devem ser mudados: [0]->id; [1]->nome; [2]->idade; [3]->twitter
    \param *f_pessoa    arquivo de dados
    \param *index       vetor de structs que armazena o indice
    \param size_index   tamanho do vetor index

*/
void Altera(dados *busca, dados *muda, int caso, int *muda_campo, FILE *f_pessoa, indice *index, int size_index)
{
    int RRN = 0;        //guarda o RRN
    int achouID = -1;   //flag para verificar se achou o id desejado
    char nome[40];      //usado para armazenar temporariamente o nome
    int idade;          //usado para armazenar temporariamente a idade
    char twitter[15];   //usado para armazenar temporariamente o twitter

    switch (caso)
    {
        case 1: //busca por id    

            /*Busca pelo Id no Vetor de Indice*/
            achouID = BuscaBinaria(index, size_index, busca->idPessoa);

            /*Recupera Regsitro Buscado*/
            if (achouID != -1) //achou o id
            {
                /*Posicao do cursor no RRN desejado*/
                RRN = index[achouID].RRN;
                fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
                
                /*Verifica se o registro esta removido*/
                fread(&busca->removido, sizeof(char), 1, f_pessoa);
                if (busca->removido == '0') return;

                /*Le o Registro*/
                fread(&busca->idPessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->nomePessoa, sizeof(char), 40, f_pessoa);
                fread(&busca->idadePessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->twitterPessoa, sizeof(char), 15, f_pessoa);

            }
            else return;

            /*Muda os Campos Desejados*/
            MudaCampos(busca, muda, muda_campo, index, size_index);   

            /*Reescreve o Registro*/
            fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
            EscreveRegistro(busca, f_pessoa); 

            break;

        case 2: //busca por nome
            /*Armazena o nome buscado*/
            strncpy(nome, busca->nomePessoa, 40);


            /*Busca pelo nome no arquivo de Dados*/
            fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
            while (fread(&busca->removido, sizeof(char), 1, f_pessoa) == 1)
            { 
                fread(&busca->idPessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->nomePessoa, sizeof(char), 40, f_pessoa);
                fread(&busca->idadePessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->twitterPessoa, sizeof(char), 15, f_pessoa);

                if (busca->removido == '0')
                {
                    RRN++;
                    continue;
                }   

                if (strcmp(busca->nomePessoa, nome) == 0) //achou nome desejado
                {
                    /*Muda os campos desejados*/
                    MudaCampos(busca, muda, muda_campo, index, size_index); 

                    /*Reescreve o Registro*/
                    fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN*TAM_REGISTRO_PESSOA), SEEK_SET);
                    EscreveRegistro(busca, f_pessoa);
                }    

                RRN++;
            }        

            break;

        case 3: //busca por idade

            /*Armazena Idade Buscada*/
            idade = busca->idadePessoa;

            /*Busca pela idade no arquivo de Dados*/     
            fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
            while (fread(&busca->removido, sizeof(char), 1, f_pessoa) == 1)
            { 
                fread(&busca->idPessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->nomePessoa, sizeof(char), 40, f_pessoa);
                fread(&busca->idadePessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->twitterPessoa, sizeof(char), 15, f_pessoa);

                if (busca->removido == '0')
                {
                    RRN++;
                    continue;
                }   

                if (idade == busca->idadePessoa) //achou idade desejada
                {
                    /*Muda os campos desejados*/
                    MudaCampos(busca, muda, muda_campo, index, size_index);

                    /*Reescreve o Registro*/
                    fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN*TAM_REGISTRO_PESSOA), SEEK_SET);
                    EscreveRegistro(busca, f_pessoa);
                } 

                RRN++;
            }

            break;

        case 4: //busca por twitter

            /*Armazena Twitter Buscada*/
            strncpy(twitter, busca->twitterPessoa, 15);

            /*Busca pelo twitter no arquivo de Dados*/
            fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
            while (fread(&busca->removido, sizeof(char), 1, f_pessoa) == 1)
            { 
                fread(&busca->idPessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->nomePessoa, sizeof(char), 40, f_pessoa);
                fread(&busca->idadePessoa, sizeof(int), 1, f_pessoa);
                fread(&busca->twitterPessoa, sizeof(char), 15, f_pessoa);

                if (busca->removido == '0')
                {
                    RRN++;
                    continue;
                }   

                if (strcmp(busca->twitterPessoa, twitter) == 0) //achou twitter desejado
                {
                    /*Muda os campos desejados*/
                    MudaCampos(busca, muda, muda_campo, index, size_index); 

                    /*Reescreve o Registro*/
                    fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN*TAM_REGISTRO_PESSOA), SEEK_SET);
                    EscreveRegistro(busca, f_pessoa);
                }  
                RRN++;
            }
            break;    

        default:
            break;
    }
}


/*
    Essa funcao mostra na tela o registro passado.
*/
void Print(int id, char *nome, int idade, char *twitter)
{
    int tam_nome; //guarda o tamanho do nome

    /*ID*/
    printf("Dados da pessoa de código %d\n", id);

    /*Nome*/
    tam_nome = strlen(nome);
    if (tam_nome == 0) //nome nulo
    {
        printf("Nome: -\n");
    }
    else //nome nao nulo
    {
        printf("Nome: %s\n", nome);
    }
    
    /*Idade*/
    if (idade == -1) //idade nula
    {
        printf("Idade: -\n");
    }
    else //idade nao nula
    {
        printf("Idade: %d anos\n", idade);
    }

    /*Twitter*/
    printf("Twitter: %s\n\n", twitter);
}


/*
    Essa funcao recupera o indice do arquivo de indice e aramazena ele na
    RAM por meio de um vetor de structs do tipo indice.

    \param f_index      Arquivo de Indice Primario
    \param index_pessoa vetor de struct do tipo indice
*/
int RecuperaIndice(FILE *f_index, indice **index_pessoa)
{
    int size_index = 1;
    indice *index = malloc(size_index*sizeof(indice)); //cria aloca vetor de indice

    /*Calculo do numero de RRNs no Indice*/
    fseek(f_index, 0, SEEK_END);
    int tam_f_indice = ftell(f_index);
    int num_RRN = (tam_f_indice/8)-1; //subtrai 1 pois eh o cabecalho

    fseek(f_index, TAM_REGISTRO_INDICE, SEEK_SET); //reset do cursor
    
    /*Recupera Indices*/
    for (int i = 0; i < num_RRN; i++)
    {
        fread(&index[i].idPessoa, sizeof(int), 1, f_index);
        fread(&index[i].RRN, sizeof(int), 1, f_index);

        if(num_RRN > 1 && i < num_RRN-1) //se o indice possui mais de um regristro, precisa aumentar o vetor de indice
        {
            size_index++;
            index = realloc(index, (size_index) * sizeof(indice)); //aumenta o vetor de indice   
            
        }
    }

    *index_pessoa = index; /*copia o vetor para o endereco passado na funcao*/

    return size_index;  //retorna o tamanho do indice

}


/*
    Funcao que imprime o arquivo de indice no console.

    Essa funcao eh utilizada apenas para depurar o codigo, ela esta comentada em 
    em todas as funcionalidades onde foi utilizada
*/
void Print_Indice(indice *index, int size_index)
{
    for (int i = 0; i < size_index; i++)
    {
        printf("%d %d\n", index[i].idPessoa, index[i].RRN);
    }
    
}


/*
    Funcao responsavel por escrever um registro no arquivo de dados.
*/
void EscreveRegistro(dados *pessoa, FILE *f_pessoa)
{
    char barrazero = '\0';  //buffer que armazena o char '\0'
    int tam_nome;           //vertifica tamanho do nome
    int tam_twitter;        //vertifica tamanho do twitter

    /*Escrita no Arquivo de Dados*/
        /*Removido*/
    fwrite(&pessoa->removido, sizeof(char), 1, f_pessoa);

        /*Id Pessoa*/
    fwrite(&pessoa->idPessoa, sizeof(int), 1, f_pessoa);

        /*Nome Pessoa*/        
    tam_nome = strlen(pessoa->nomePessoa);
    if(tam_nome >= 1 ) //nome nao esta vazio
    {
        if (tam_nome+1 <= 40) //nome cabe no campo
        {
            fwrite(&pessoa->nomePessoa, sizeof(char), tam_nome+1, f_pessoa);
            for (int i = 0; i < 40-(tam_nome+1); i++) //preenche o resto com lixo
            {
                fwrite(&lixo,sizeof(char),1,f_pessoa);
            }  
        }
        else //nome maior que o campo
        {
            fwrite(&pessoa->nomePessoa, sizeof(char), 39, f_pessoa);
            fwrite(&barrazero,sizeof(char),1,f_pessoa);
        }   
    }
    else //nome vazio
    {
        fwrite(&barrazero,sizeof(char),1,f_pessoa);
        for (int i = 0; i < 39; i++) //preenche o resto com lixo
        {
            fwrite(&lixo,sizeof(char),1,f_pessoa);
        }        
    }

        /*Idade Pessoa*/
    fwrite(&pessoa->idadePessoa, sizeof(int), 1, f_pessoa);

        /*Twitter Pessoa*/
    tam_twitter = strlen(pessoa->twitterPessoa);
    if (tam_twitter+1 <= 15) //twitter cabe no campo
    {
        fwrite(&pessoa->twitterPessoa, sizeof(char), tam_twitter+1, f_pessoa);
        for (int i = 0; i < 15-(tam_twitter+1); i++) //preenche o resto com lixo
        {
            fwrite(&lixo,sizeof(char),1,f_pessoa);
        }
    }
    else //twiter maior que o campo
    {
        fwrite(&pessoa->twitterPessoa, sizeof(char), 14, f_pessoa);
        fwrite(&barrazero,sizeof(char),1,f_pessoa);
    }
}


/*
    Funcao que altera os campos de um determinado registro. 

    Utilizando o vetor "muda_campo" os dados da struct "busca" sao substituidos pelos dados 
    da struct "muda", conforme solicitado.

    As variaveis *index e size_index sao utilizadas no caso onde ha alteracao no campo idPessoa do registro.

    \param *busca       dados que devem ser buscados 
    \param *muda        dados que devem ser alterados
    \param *muda_campo  vetor que identifica quais campos devem ser mudados: [0]->id; [1]->nome; [2]->idade; [3]->twitter
    \param *index       vetor de structs que armazena o indice
    \param size_index   tamanho do vetor index


*/
void MudaCampos(dados *busca, dados *muda, int *muda_campo, indice *index, int size_index)
{
    /*Muda id*/
    if (muda_campo[0] == 1)
    {
        /*Altera no indice*/
        for (int i = 0; i < size_index; i++)
        {
            if(index[i].idPessoa == busca->idPessoa) index[i].idPessoa = muda->idPessoa;    
        }

        busca->idPessoa = muda->idPessoa;   
    }

    /*Muda nome*/        
    if (muda_campo[1] == 1)
    {
        strncpy(busca->nomePessoa, muda->nomePessoa, 40); 
    }
    
    /*Muda idade*/
    if (muda_campo[2] == 1)
    {
        busca->idadePessoa = muda->idadePessoa;
    }

    /*Muda twitter*/
    if (muda_campo[3] == 1)
    {
        strncpy(busca->twitterPessoa, muda->twitterPessoa, 15); 
    }
}


/*
    Funcao utilizada para ordenar o vetor de indice utilizando o id como parametro de ordenacao
*/
void Insertion_Sort(indice *v, int n)
{
    int i, j;
    indice k;
    
    for(j = 0; j < n; j++)
    {//percorre o vetor da esquerda para a direita

        k = v[j]; //guarda o valor do elemento que sera comparado

        for(i = j-1; i >= 0 && k.idPessoa < v[i].idPessoa; i--)
        {//percorre o vetor da direita para a esquerda a partir do elemento j
        //so executa caso i positivo e o se o valor do antecessor for maior que o elemento j
            v[i+1] = v[i]; //move o elemento maior que k para a direita 
        }
        
        v[i+1] = k; //coloca o elemento j na posicao correta (i+1)
    }
}

/*
    Utilizado para fazer a busca de um id no vetor de indice.

    Caso a busca tenha sido bem sucedida, retorna o indice do vetor onde esta o id buscado.
    Caso contrario, retorna -1.
*/
int BuscaBinaria(indice *index, int size_index, int idBuscado)
{

    int fim = size_index;
    int comeco = -1;
    int achou = -1;

    while (comeco < fim-1)
    {
        int meio = (comeco+fim)/2;
        if (idBuscado == index[meio].idPessoa) 
        {
            achou = meio;
            break;
        }
        else if (idBuscado < index[meio].idPessoa ) fim = meio;
        else comeco = meio;
        
    }
    return achou; 
    
}