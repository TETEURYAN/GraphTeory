#include <cstdlib> 
#include <iostream> 
#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int v1;
    int v2;
    int peso;
};

int getRandom(int ub, int lb)
{
    return rand() % (ub - lb +1) + lb;
}

bool in(vector<edge> edges, edge elem)
{
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].v1==elem.v1 && edges[i].v2==elem.v2) return true;
        if (edges[i].v1==elem.v2 && edges[i].v2==elem.v1) return true;
    }
    return false;
}

void imprimeGrafo(int V, int E, int pesoUB, int pesoLB, double chance, string output, int nE)
{
    vector<edge> edges;
    output = output+".mtx";
    ofstream fout(output);
    fout <<  V << " " << E << endl;
    for (int i = 0; i < E; i++)
    {
        int peso = getRandom(pesoUB,pesoLB);
        if (nE)
        {
            int escolha = getRandom(100,1);
            if (escolha < chance)
            {  
                peso = -peso;
            }
        }
        int n1, n2;
        n1 = getRandom(V, 1);
        n2 = getRandom(V, 1);
        while (in(edges, {n1,n2, peso}) || n1==n2)
        {
            n1 = getRandom(V, 1);
            n2 = getRandom(V, 1);
        }
        fout << n1 << " " << n2 << " " << peso <<  endl;
        edges.push_back({n1,n2, peso});
    }
    fout.close();
}

int main()
{
    vector<edge> edges;
    int Vmax, Vmin, Emax, Emin, nE;
    double chance; 
    srand(time(0));
    cout << "Forneça o número máximo de vértices: ";
    cin >> Vmax;
    cout << endl;
    cout << "Forneça o número mínimo de vértices: ";
    cin >> Vmin;
    cout << endl;
    cout << "Forneça o número mínimo de arestas: ";
    cin >> Emin;
    cout << endl;
    cout << "Com aresta negativa? 1 para sim 0 para não: ";
    cin >> nE;
    cout << endl;
    if (nE)
    {
        cout << "Chance de aparecer aresta negativa: (de 0 a 100%): ";
        cin >> chance;
        cout << endl;
    }
    string output = "";
    cout << "Digite o nome do arquivo de saída (sem o .mtx): ";
    cin >> output;
    cout << endl;
    int pesoUB, pesoLB;
    cout << "Digite o limite máximo para os pesos (Exemplo: 100, pesos podem ir de -100 a 100): ";
    cin >> pesoUB;
    cout << endl;
    cout << "Digite o limite mínimo para os pesos (valor positivo, se não quiser um, digite 1): ";
    cin >> pesoLB;
    cout << endl;
    cout << "Quantos arquivos de saída? ";
    int nSaidas;
    cin >> nSaidas;
    cout << endl;
    for (int i = 1; i <= nSaidas; i++)
    {
        int V = getRandom(Vmax, Vmin);
        Emax = (V*(V-1))/2;
        int E = getRandom(Emax, Emin);
        imprimeGrafo(V, E, pesoUB, pesoLB, chance, output + to_string(i), nE);
    }
    
    
    return 0;
}