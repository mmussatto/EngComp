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

    i = b;
    j = n;
    k = v[(b+n)/2];

    do
    {
        while(v[i] < k){ i++; }

        while(k < v[j]){ j--; }

        if(i <= j)
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }

    } while (i <= j);

    if(b < j){ Quick_Sort(v, b, j);}

    if(i< n){ Quick_Sort(v, i, n);}
}