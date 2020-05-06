int Bubble_Sort(int v[], int T)
{
    int cont = 0; //contador de operacoes

    int i, j, aux; 
    int troca = 1; //olha se o vetor ja esta ordenado
    cont ++; 

    for(i=0; i<T-1 && troca; i++)
    {
        cont +=4;

        troca = 0; //se troca continuar igual a zero, o vetor esta ordenado
        cont++;

        for ( j = 0; j < T-i-1; j++)
        {
            cont += 3;

            if(v[j] > v[j+1])
            {
                troca = 1;
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                cont += 6;
            }
        }
    }

    return cont;
}

int Quick_Sort(int v[], int b, int n)
{
    int i, j, k, aux;

    int cont = 0; //contador de operacoes

    i = b; //lado esquerdo
    j = n; //lado direito
    k = v[(b+n)/2]; //pivot, elemento central
    cont += 5;

    do
    {
        cont++;
        while(v[i] < k){ i++; cont+=2; } //percorre da esq p/ direita selecioando o primeiro elemento maior que o pivot

        cont++;
        while(k < v[j]){ j--; cont+=2; } //percorre da dir p/ esq selecionando o primeiro elemenro menor que o pivot

        cont++;
        if(i <= j) 
        {//troca os elementos selecionados de posicao (menor p/ esq e maior p/ dir)
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
            cont += 7;
        }

    cont++;
    } while (i <= j); //quando os pointer se cruzarem, o lado esq do pivot sera menor que ele e o lado dir sera maior

    cont++;
    if(b < j){ cont += Quick_Sort(v, b, j);} //aplica quicksort para o lado esq

    cont++;
    if(i < n){ cont += Quick_Sort(v, i, n);} //aplica quicksort para o lado dir

    return cont;
}

int Selection_Sort(int v[], int T)
{
    int i; //marca o fim do vetor
    int j, maior;
    int aux;// index do maior elemento
    int cont = 0; //contador de operacoes

    for ( i = T - 1; i > 0; i--) 
    {//for diminui a cada iteracao o tamanho do vetor
        cont += 3;
        
        maior = v[0];
        aux = 0;
        cont += 2;

        for ( j = 1; j <= i; j++)
        {//percorre o vetor e seleciona o maior elemento
            cont += 3;

            cont++;
            if (v[j] > maior)
            {
                maior = v[j];
                aux = j;
                cont += 2;
            }
        }
        
        cont += 2; 
        v[aux] = v[i]; //troca do maior elemento
        v[i] = maior;  // com o último
    
    }

    return cont;
}

/*
int Heap_Sort(int v[], int n)
{

}
void faz_Heap(int v[], int n)
{

}
void ajuste(int v[], int i, int n)
{

}
Nao implementado*/

int Insertion_Sort(int v[], int n)
{
    int i, j ,k;
    int cont = 0; //contador de operacoes

    cont += 2;
    for(j = 0; j < n; j++)
    {//percorre o vetor da esquerda para a direita
        cont += 3;

        cont++; k = v[j]; //guarda o valor do elemento que sera comparado

        cont += 4;
        for(i = j-1; i >= 0 && k < v[i]; i--)
        {//percorre o vetor da direita para a esquerda a partir do elemento j
        //so executa caso i positivo e o se o valor do antecessor for maior que o elemento j
            cont += 4;
            cont+=2; v[i+1] = v[i]; //move o elemento maior que k para a direita 
        }
        
        cont+=2; v[i+1] = k; //coloca o elemento j na posicao correta (i+1)
    }
    return cont;
}

