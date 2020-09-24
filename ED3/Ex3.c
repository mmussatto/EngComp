/* This code will read the name of a .bin file, create it and write the information inside.
    I will then print out ta number wich was used to check if the file was correctly written.

    An exemple of input would be:

    caso1.bin
    6
    1 Joao 30
    2 Ana 15
    3 Maria 28
    4 MichaelScott 24
    5 Jose 56
    6 Leticia 10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}


int main()
{
    char nome_arq[20]; //guarda o nome do arquivo
    int num_reg;       //guarda numero de registros

    int id;        //guarda id
    char nome[50]; //guarda nome
    int tam_nome;
    int idade;     //guarda idade

    scanf("%s", nome_arq); //le nome arquivo
    FILE *arq = fopen(nome_arq, "wb"); 
    if (arq == NULL){//deu ruim
        printf("Nao foi possivel abrir o arquivo!\n");
        return 0;
    }

    scanf("%d", &num_reg); //le quantidade de registros

    for ( int i = 0; i < num_reg; i++)
    {
        scanf("%d %s %d", &id, nome,&idade);
        tam_nome = strlen(nome);

        fwrite(&id,sizeof(int),1,arq);
        fwrite(nome,sizeof(char),tam_nome+1,arq);
        fwrite(&idade,sizeof(int),1,arq);
        
    }
    
    fclose(arq);

    binarioNaTela(nome_arq);
    return 0;

}