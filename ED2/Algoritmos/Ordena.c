int Bubble_Sort(int v[], int T)
{
    int cont = 0; //contador de operacoes

    int i, j, aux; 
    int troca = 1; //olha se o vetor ja esta ordenado
    cont += 4; //declaracao das variaveis

    for(i=0; i<T-1 && troca; i++)
    {
        cont +=2;

        troca = 0; //se troca continuar igual a zero, o vetor esta ordenado
        cont++;

        for ( j = 0; j < T-i-1; j++)
        {
            cont += 2;

            if(v[j] > v[j+1])
            {
                troca = 1;
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                cont += 4;
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
    cont += 3;

    do
    {
        cont++;
        while(v[i] < k){ i++; cont++; } //percorre da esq p/ direita selecioando o primeiro elemento maior que o pivot

        cont++;
        while(k < v[j]){ j--; cont++; } //percorre da dir p/ esq selecionando o primeiro elemenro menor que o pivot

        cont++;
        if(i <= j) 
        {//troca os elementos selecionados de posicao (menor p/ esq e maior p/ dir)
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
            cont += 5;
        }

    cont++;
    } while (i <= j); //quando os pointer se cruzarem, o lado esq do pivot sera menor que ele e o lado dir sera maior

    cont++;
    if(b < j){ cont += Quick_Sort(v, b, j);} //aplica quicksort para o lado esq

    cont++;
    if(i < n){ cont += Quick_Sort(v, i, n);} //aplica quicksort para o lado dir

    return cont;
}

