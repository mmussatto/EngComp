//TAD Arvore Binaria

#define OK         1
#define ERRO       0

typedef int Tipo_Dado;

struct Ind{
    char Tipo_NO; // pode ser B(binario), N(numerico) ou C(classe)
    int Ident;    //numero de tres digitos, identifica o no
};

typedef struct Ind Indice;

struct NO {
    Indice NO_Atual;       //tipo e identificacao do no atual    
    char Info[100];          //semantica do no 
    float Valor_Teste;    //Valor para ser testado no caso do Tipo ser N
    Indice NO_Pai;        //tipo e identificacao do no pai
    char Lado_Conex;      //lado da conexao com pai, E(esquerda) ou D(direita)
    float Nivel_Certeza;   //nivel de certeza caso o tipo seja C
    struct NO *esq;
    struct NO *dir;

};

typedef struct NO Nodo;
typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_NO(struct NO* no);
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin *raiz, char Tipo_NO, int Ident, char *Info, float Valor_Teste, char Pai_Tipo_No, int Pai_Ident, char conex, float Nivel_Certeza);
struct NO* Procura_NO(struct NO *NO, struct NO *result, char Tipo_NO, int Ident);
struct NO* Maior_Ctz(struct NO *atual, struct NO *maior_no, float *maior_ctz);

