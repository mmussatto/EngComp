void Bubble_Sort(int v[], int T)
{
    int i, j, aux, troca = 1;

    for(i=0; i<T-1 && troca; i++)
    {
        troca = 0;

        for ( j = 0; j < T-i-1; j++)
        {
            if(v[j] > v[j+1])
            {
                troca = 1;
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
        
    }
}