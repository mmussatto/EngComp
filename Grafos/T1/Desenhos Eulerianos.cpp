/*
|   SCC0216 - Modelagem Computacional em Grafos
|   T1 - Desenhos Eulerianos
|
|   Nome: Murilo Mussatto
|   NUSP: 1123425
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;


class Graph 
{
public:

    vector<map<int, int>> adjList;

    Graph (int v) 
    {
        adjList.resize(v);
    }

    void addEdge (int src, int dest) 
    {
        adjList[src][dest] = dest;
        adjList[dest][src] = src;
    }

    bool checkPossibleEulerianCycle()
    {
        for (auto v : adjList)
        {
            //All vertices need to be even degree
            if (v.size() %2 != 0)
                return false;   
        }

        return true;
    }

    void printEulerianCycle()
    {
        int v = 0;
        int prev_v = 0;
        cout << v << " ";

        //Get next node
        v = adjList[v].begin()->second;

        //Traverse graph until returning to first node
        while (v != 0 || adjList[0].size() != 1)
        {
            //Print current node
            cout << v << " ";

            //Remove edges
            adjList[v].erase(prev_v);
            adjList[prev_v].erase(v);

            //Get next node
            prev_v = v;
            v = adjList[v].begin()->second;

            //If next node is 0, verify if all other edges were traversed
            if(v == 0 && adjList[0].size() == 1 && adjList[prev_v].size() != 1)
            {
                //Get another next node
                map<int, int>::iterator it = adjList[prev_v].begin();
                it++;
                v = it->second;
            }
        }

        //Print last node
        cout << v;
    }
};


int main () {

    //Read file name
    string fileName;
    cin >> fileName;

    //Open file
    ifstream infile(fileName);
    if (!infile)
    {
        cout << "Could not open file!";
        exit(1);
    }
    
    //Read first line
    int v, a;
    infile >> v >> a;

    //Create graph
    Graph graph(v);

    while (!infile.eof())
    {
        int src, dest;
        infile >> src >> dest;
        graph.addEdge(src, dest);
    }


    //Check if an Eulerian Circuit is possible
    if (!graph.checkPossibleEulerianCycle())
    {
        cout << "Não";
        return 0;
    }


    //Print the Eulerian circuit
    cout << "Sim" << endl;
    graph.printEulerianCycle();

    return 0;
}