/*
|   SCC0607 Estrutura de Dados III
|   Trabalho Pratico 03
|
|   Desenvolvido por: Murilo Mussatto
|               NUSP: 11234245
*/

#include "Grafo.h"


void criaGrafo(Grafo* g, int v)
{
    g->V = v;
    g->A = 0;

    Lista* l = (Lista*) malloc (sizeof(Lista));

    if (l != NULL) *l = NULL;

    g->li = l;
}

void liberaGrafo(Lista *li)
{
    if (li != NULL)
    {
        Nodo *vertice;
        Nodo *no;

        while(*li != NULL)
        {
            vertice = *li;
            *li = (*li)->prox;

            while (vertice != NULL)
            {
                no = vertice;
                vertice = vertice->adj;
                free(no);
            }

            free(vertice);
            
        }

        free (li);
    }
}

void imprimeGrafo(Grafo *g)
{
    Lista *li = g->li;

    if (li != NULL)
    {
        Nodo *vertice = *li;
        Nodo *no;

        while(vertice != NULL)
        {

            printf("%s", vertice->nome);
            no = vertice->adj;

            while (no != NULL)
            {
                printf(", %s", no->nome);
                no = no->adj;
            }

            printf("\n");
            vertice = vertice->prox;
            
        }

    }

}

void imprimeCeleb(Grafo *g, int ordem[])
{

    Lista *li = g->li;
    Nodo *v;
    
    for (v = *li; v != NULL; v = v->prox)
    {
        int antecessor = ordem[v->id];

        if(antecessor == 0) continue; //pula celebridade buscada 
        
        printf("%s", v->nome);

        if (antecessor == -1)
        {
            printf(", NAO SEGUE A CELEBRIDADE\n");
            continue;
        }

        
        while (antecessor != 0)
        {
            Nodo *aux = *li;
            while (aux->id != antecessor) aux = aux->prox;

            printf(", %s", aux->nome);

            antecessor = ordem[aux->id];
                
        }

        printf("\n");

    }

}


void controiGrafo(Grafo *g, FILE *f_pessoa, FILE *f_index, FILE *f_segue, int qtdSeguidores)
{
    /*Registros*/
    dados d_pessoa;
    int size_index;
    indice *index; 
    segue *d_segue;

    /*Recupera Indice*/
    size_index = RecuperaIndice(f_index, &index);

    /*Carrega arquivo segue para a RAM*/
    RecuperaSegue(f_segue, &d_segue, qtdSeguidores);

    /*Adiciona pessoas no grafo*/
    for (int i = 0; i < size_index; i++)
    {   
        const char *nome_segue = RecuperaNome(f_pessoa, index, size_index, index[i].idPessoa); 

        insereAresta(g, nome_segue, NULL);

        free((char*) nome_segue);
        
    }

    OrdenaID(g);

    
    /*Adiciona Relacoes entre Pessoas*/
    for (int i = 0; i < qtdSeguidores; i++)
    {
        
        if (d_segue[i].removido == 0) continue;
        

        const char *nome_segue = RecuperaNome(f_pessoa, index, size_index, d_segue[i].idSegue);
        const char *nome_seguido = RecuperaNome(f_pessoa, index, size_index, d_segue[i].idSeguido);

        insereAresta(g, nome_segue, nome_seguido);

        free((char*) nome_segue);
        free((char*) nome_seguido);


    }

    free(index);
    free(d_segue);
}

void controiGrafoT(Grafo *g, FILE *f_pessoa, FILE *f_index, FILE *f_segue, int qtdSeguidores)
{
    /*Registros*/
    dados d_pessoa;
    int size_index;
    indice *index; 
    segue *d_segue;

    /*Recupera Indice*/
    size_index = RecuperaIndice(f_index, &index);

    /*Carrega arquivo segue para a RAM*/
    RecuperaSegue(f_segue, &d_segue, qtdSeguidores);

    /*Adiciona pessoas no grafo*/
    for (int i = 0; i < size_index; i++)
    {   
        const char *nome_segue = RecuperaNome(f_pessoa, index, size_index, index[i].idPessoa); 

        insereAresta(g, nome_segue, NULL);

        free((char*) nome_segue);
        
    }

    OrdenaID(g);
    
    /*Adiciona Relacoes entre Pessoas*/
    for (int i = 0; i < qtdSeguidores; i++)
    {
        
        if (d_segue[i].removido == 0) continue;
        

        const char *nome_segue = RecuperaNome(f_pessoa, index, size_index, d_segue[i].idSegue);
        const char *nome_seguido = RecuperaNome(f_pessoa, index, size_index, d_segue[i].idSeguido);

        insereAresta(g, nome_seguido, nome_segue);

        free((char*) nome_segue);
        free((char*) nome_seguido);


    }

    free(index);
    free(d_segue);
}

/*

    Insere a Aresta (pessoaquesegue, pessoaqueehseguida)

*/
void insereAresta(Grafo *g, const char segue[], const char seguida[])
{

    Lista *li = g->li;

    if (li == NULL) return; //lista nao foi iniciada


    if (*li == NULL) //lista vazia
    {
        Nodo *no_u = malloc (sizeof(Nodo));
        if (no_u == NULL) return;

        no_u->id = -1;
        strcpy(no_u->nome, segue);
        no_u->prox = NULL;
        no_u->adj = NULL;

        *li = no_u;

        //if(seguida == NULL) return;

        /*
        Nodo *no_v = malloc (sizeof(Nodo)); //aloca no pessoa seguida
        if (no_v == NULL) return;

        strcpy(no_v->nome, seguida);
        no_v->prox = NULL;
        no_v->adj = NULL; 

        no_u->adj = no_v;
        
        */
        return;
    } 

    Nodo *aux;
    aux = *li;

    while (aux->prox != NULL) //enquanto tiverem elementos na lista principal
    {   
        if (strcmp(aux->prox->nome, segue) <= 0) aux = aux->prox; //se o proximo nodo for menor que o nodo u, continua
        else break;
        
    } 

    if(strcmp(aux->nome, segue) == 0) //vertice u ja esta na lista principal
    {

        if (seguida == NULL) return; //nao possui pessoa seguida

        while (aux->adj != NULL) //percorre lista de adjacencia
        {
            if (strcmp(aux->adj->nome, seguida) <= 0) aux = aux->adj;
            else break;
        }


        if(strcmp(aux->nome, seguida) == 0) return; //entrada repitida

        Nodo *no_v = malloc (sizeof(Nodo)); //aloca no pessoa seguida
        if (no_v == NULL) return;

        no_v->id = buscaID(g, (char*)seguida);
        strcpy(no_v->nome, seguida);
        no_v->prox = NULL;
        no_v->adj = NULL;
        
        no_v->adj = aux->adj;      
        aux->adj = no_v;

        g->A += 1; //adiciona uma aresta no grafico


    } 
    else   //vertice u nao esta na lista princiapal
    {    
        Nodo *no_u = malloc (sizeof(Nodo)); 
        if (no_u == NULL) return;

        no_u->id = -1;
        strcpy(no_u->nome, segue);
        no_u->adj = NULL;

        no_u->prox = aux->prox;
        aux->prox = no_u; 

        if (seguida == NULL) return; //nao possui pessoa seguida

        g->A += 1; //adiciona uma aresta no grafico

        Nodo *no_v = malloc (sizeof(Nodo)); //aloca no pessoa seguida
        if (no_v == NULL) return;

        no_v->id = buscaID(g, (char*)seguida);
        strcpy(no_v->nome, seguida);
        no_v->prox = NULL;
        no_v->adj = NULL;

        no_u->adj = no_v;
        
    }
    
}

int buscaID(Grafo *g, char nome[])
{
    Lista *li = g->li;

    Nodo *v = *li;
    for (v; v != NULL; v = v->prox)
    {
        if (strcmp(nome, v->nome) == 0)
        {
            return v->id;
        }
        
    }

    return -1;

}

void OrdenaID(Grafo *g)
{
    Lista *li = g->li;

    Nodo *v = *li;

    int cont = 0;

    while (v != NULL)
    {
        cont++;
        v->id = cont;
        v = v->prox;
    }    

}

void BFS(Grafo *g, char celebridade[], int *ordem)
{

    Lista *li = g->li;

    int celebID = buscaID(g, celebridade);

     
    int count = 0;

    int visitados[g->V+1];
    for (int i = 0; i <= g->V; i++)
    {
        ordem[i] = -1;
        visitados[i] = -1;
    }  
        
    QUEUE *fila = Q_New(sizeof(int));

    visitados[celebID] = count;

    ordem[celebID] = 0;     //comeca pelo vertice celebID
    Q_Push(&celebID, fila);

    while (Q_Size(fila) > 0)
    {
        int ID_atual;
        Q_Shift(&ID_atual, fila);

        Nodo *v = *li;  
        while (v->id != ID_atual) v = v->prox;  //vertice ID_atual

        Nodo *aux = v->adj; //adjacentes
        
        while (aux != NULL)
        {
            if (visitados[aux->id] == -1)   //se != -1, ja foi visitado
            {
                count ++;   
                visitados[aux->id] = count; //marca adjacente como visitado
                ordem[aux->id] = v->id;     //marca antecessor
                Q_Push(&(aux->id), fila);   //coloca adjacente na fila 
            }

            aux = aux->adj; //proximo adjacente a v
            
        }
    }
    
    Q_Destroy(fila);

    return;
    
}

int DFS(Grafo *g, int idFofoca, int *visitados)
{
    Lista *li = g->li;

    int count = 0;

    STACK *pilha = S_New(sizeof(int));

    for (int i = 0; i <= g->V; i++)
    {
        visitados[i] = -1;
    }


    int ID_atual = idFofoca;
    visitados[ID_atual] = count;
    S_Push(&ID_atual, pilha);

    while (S_Size(pilha) > 0)
    {
        S_Top(&ID_atual, pilha);

        Nodo *v = *li;  
        while (v->id != ID_atual) v = v->prox;  //vertice ID_atual  

        Nodo *aux = v->adj; //adjacentes

        while (aux != NULL)
        {
            if (aux->id == idFofoca)
            {
                count ++;
                return count;
            }
            
            if (visitados[aux->id] != -1)   //se != -1, ja foi visitado
            {
                aux = aux->adj;
            }
            else    //vertice nao visitado
            {
                count ++;
                visitados[aux->id] = count; //marca no vetor que o adjacente foi visitado
                S_Push(&(aux->id), pilha);  //coloca na pilha 
                //ID_atual = aux->id;
                break;
            }  
        }
        if (aux == NULL)
        {
            count --;
            S_Pop(&ID_atual, pilha);  
            /* 
            if (ID_atual == v->id)
            {
                S_Pop(&ID_atual, pilha);   
            }*/
            
        }
    }
    
    return -1;  //se chegou aqui, foi pq nao achou ciclo


}

void teste()
{
    Grafo g;
    criaGrafo( &g, 3);

    insereAresta(&g, "Aline", NULL);
    insereAresta(&g, "Bruno", NULL);
    insereAresta(&g, "Jacob", NULL);
    insereAresta(&g, "Maria", NULL);
    insereAresta(&g, "Aline", "Jacob");
    insereAresta(&g, "Jacob", "Maria");
    insereAresta(&g, "Jacob", "Bruno");
    insereAresta(&g, "Bruno", "Giorno");
    insereAresta(&g, "Bruno", "Dio");

    int teste = buscaID(&g, "Bruno");

    imprimeGrafo(&g);

    liberaGrafo(g.li);

    return;
}


