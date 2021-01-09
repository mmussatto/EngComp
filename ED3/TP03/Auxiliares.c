#include "Auxiliares.h"

char lixo = '$'; //variavel global que representa o lixo

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
    Essa funcao mostra na tela o registro de dados pessoa passado.
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


/*  TP02
    Essa funcao imprime na tela o registro do arquivo segue passado, 
    com a devida formatação
*/
void PrintSegue(segue d)
{   
    /*Variaveis de Controle*/
    int caso;

    /*Id Pessoa que eh seguida*/
    printf("Segue a pessoa de código: %d\n", d.idSeguido);

    /*Grau de amizade*/
    printf("Justificativa para seguir: ");   
    
    if(strcmp(d.grauAmizade, "0\0$") == 0) caso = 0;
    else if(strcmp(d.grauAmizade, "1\0$") == 0) caso = 1;
    else if(strcmp(d.grauAmizade, "2\0$") == 0) caso = 2;

    switch (caso)
    {
    case 0:
        printf("segue porque é uma celebridade\n");
        break;
    
    case 1:
        printf("segue porque é amiga de minha amiga\n");
        break;

    case 2:
        printf("segue porque é minha amiga\n");
        break;
    }

    /*Comecou a Seguir*/
    printf("Começou a seguir em: %s\n", d.dataInicio);

    /*Parou de Seguir*/
    printf("Parou de seguir em: %s\n", d.dataFim);

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


/*  [TP02]
    Essa funcao recupera o arquivo de dados segue e armazena ele 
    na RAM por meio de um vetor de structs do tipo segue

    \param f_segue      Arquivo de dados Segue
    \param d_segue      vetor de struct do tipo segue
    \param size_segue   quantidade de seguidores no arquivo segue

*/
void RecuperaSegue(FILE *f_segue, segue **d_segue, int size_segue)
{
    segue *vet = malloc(size_segue*sizeof(segue)); //cria e aloca vetor

    fseek(f_segue, TAM_REGISTRO_SEGUE, SEEK_SET); //pula cabecalho

    for (int i = 0; i < size_segue; i++) //le os registros
    {
        fread(&vet[i].removido, sizeof(char), 1, f_segue); 
        fread(&vet[i].idSegue, sizeof(int), 1, f_segue);
        fread(&vet[i].idSeguido, sizeof(int), 1, f_segue);
        fread(&vet[i].grauAmizade, sizeof(char), 3, f_segue);
        fread(&vet[i].dataInicio, sizeof(char), 10, f_segue);
        fread(&vet[i].dataFim, sizeof(char), 10, f_segue);

    }

    *d_segue = vet; //retorna o vetor criado para o ponteiro passado
    
}


/*  [TP03]

    Essa funcao busca um registro do arquivo de dados pessoa pelo
    ID e recupera o nome da pessoa.

    \param f_pessoa     Arquivo de dados pessoa
    \param index        Vetor do dados do tipo indice
    \param size_index   Tamanho do vetor de dados
    \paran id           ID a ser buscado

    \return String contendo o nome da pessoa

*/
const char* RecuperaNome(FILE *f_pessoa, indice *index, int size_index, int id)  //TP03
{
    /*Dados*/
    dados d_Pessoa;

    /*Variaveis de Controle*/
    int achouID;        //flag de busca bem sucedida
    int RRN;            //RRN do registro desejado


    d_Pessoa.idPessoa = id;


    /*Busca pelo Id no Vetor de Indice*/
    achouID = BuscaBinaria(index, size_index, d_Pessoa.idPessoa);

    /*Recupera Regsitro Buscado*/
    if (achouID != -1) //achou o id
    {
        /*Posicao do cursor no RRN desejado*/
        RRN = index[achouID].RRN;
        fseek(f_pessoa, TAM_REGISTRO_PESSOA+(RRN * TAM_REGISTRO_PESSOA), SEEK_SET);
        
        /*Verifica se o registro esta removido*/
        fread(&d_Pessoa.removido, sizeof(char), 1, f_pessoa);
        if (d_Pessoa.removido == '0')
        {
            return NULL;  
        }  

        fread(&d_Pessoa.idPessoa, sizeof(int), 1, f_pessoa);
        fread(&d_Pessoa.nomePessoa, sizeof(char), 40, f_pessoa);
        fread(&d_Pessoa.idadePessoa, sizeof(int), 1, f_pessoa);
        fread(&d_Pessoa.twitterPessoa, sizeof(char), 15, f_pessoa);

            
        char *nome = malloc(40*sizeof(char)); 
        strcpy(nome, d_Pessoa.nomePessoa);
        
        return nome;

    }
    else //nao achou o id
    {
        return NULL;
    }
}


/*
    Funcao responsavel por escrever um registro no arquivo de dados Pessoa.
*/
void EscreveRegistro(dados *pessoa, FILE *f_pessoa)
{
    char barrazero = '\0';  //buffer que armazena o char '\0'
    int tam_nome;           //vertifica tamanho do nome
    int tam_twitter;        //vertifica tamanho do twitter

    /*Escrita no Arquivo de dados Pessoa*/
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


/*  TP02
    Funcao resposavel por escrever um registro no arquivo de dados Segue
*/
void EscreveRegistroSegue(segue *d_segue, FILE *f_segue)
{
    /*Escrita no arquivo de dados Segue*/
        /*Removido*/
    fwrite(&d_segue->removido, sizeof(char), 1, f_segue);
    
        /*IdPessoaQueSegue*/
    fwrite(&d_segue->idSegue, sizeof(int), 1, f_segue);

        /*IdPessoaQueESeguida*/
    fwrite(&d_segue->idSeguido, sizeof(int), 1, f_segue);

        /*Grau de Amizade*/
    fwrite(&d_segue->grauAmizade, sizeof(char), 2, f_segue);
    fwrite(&lixo, sizeof(char), 1, f_segue);

        /*Data Inicio Segue*/
    fwrite(&d_segue->dataInicio, sizeof(char), 10, f_segue);

        /*Data Fim Segue*/    
    fwrite(&d_segue->dataFim, sizeof(char), 10, f_segue);
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


/*  TP02
    Utilizado para fazer a busca de um id no vetor de seguidores

    Caso a busca tenha sido bem sucedida, um while eh encarregado de retroceder o vetor 
    ate encontrar o primeiro registro com o id buscado

    Caso a busca não tenha sido bem sucedida, retorna -1

*/
int BuscaBinaria_Segue(segue *d_segue, int qtdSeguidores, int idBuscado)
{

    int fim = qtdSeguidores;
    int comeco = -1;
    int achou = -1;
    int i = 0;

    while (comeco < fim-1)
    {
        int meio = (comeco+fim)/2;
        if (idBuscado == d_segue[meio].idSegue) 
        {
            achou = meio;
            break;
        }
        else if (idBuscado < d_segue[meio].idSegue ) fim = meio;
        else comeco = meio;
        
    }
    if(achou == -1) return achou; //nao achou o id

    /*Retrocede ate um IdSegue diferente*/
    while(d_segue[achou].idSegue == idBuscado)
    {
        achou --;
    }
    return achou+1; //soma 1 devido a condicao do while
    
}


/*  TP02
    Essa funcao é utlizada pelo qsort da funcionalidade 7 para comparar os registros e 
    definir qual é maior e qual é menor
*/
int Comparador (const void *x, const void *y)
{
    /*Casting*/
    segue *a = (segue *)x;
    segue *b = (segue *)y;


    if (a->idSegue != b->idSegue) 
        return a->idSegue - b->idSegue;
    
    else //empate id segue 
    {
        if (a->idSeguido != b->idSeguido)
            return a->idSeguido - b->idSeguido;
        
        else //empate id seguido 
        {
            int cmpInicio = strcmp(a->dataInicio, b->dataInicio);

            if(cmpInicio != 0)
                return cmpInicio;

            else //empate deta inicio que segue
            {
                return strcmp(a->dataFim, b->dataFim);
            }
                
        }
    }
}

