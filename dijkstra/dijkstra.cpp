#include <bits/stdc++.h>
using namespace std;
#define max INT_MAX

typedef pair<int, int> pares;

vector<int> path(int src, int V, list<pair<int, int>> * arestas)
{
    priority_queue<pares, vector<pares>, greater<pares>> queue;
    vector<int> dist(V + 1, max);

    queue.push(make_pair(0, src));
    dist[src] = 0;

    while (not queue.empty()) {
        int u = queue.top().second;
        queue.pop();
        
        list<pair<int, int>>::iterator i;
        for (i = arestas[u].begin(); i != arestas[u].end(); i++) {
            int v = (*i).first;
            int peso = (*i).second;

            if (dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                queue.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main(int argc, char *argv[])
{
    string in = "";
    string out = "";
    int initial = 1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial" << endl;
            
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
        {
            in = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1)
        {
            initial = atoi(argv[++i]);
        }
    }

    if (in == ""){
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(in);

    if (not fin){
        cerr << "Could not open input file: " << in << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;

    int a, b, cost;
    list<pair<int, int>> arestas[V + 1];

    for (int i = 0; i < E; i++)
    {
        fin >> a >> b >> cost;
        arestas[b].push_back(make_pair(a, cost));
        arestas[a].push_back(make_pair(b, cost));
    }

    fin.close();

    vector<int> distances = path(initial, V, arestas);

    if (not (out == ""))
    {
        ofstream fout(out);
        if (not fout)
        {
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        
        for (int i = 1; i <= V; ++i) {
            fout << i << ":" << distances[i] << " ";
        }
        fout << endl;

        fout.close();
    }

    for (int i = 1; i <= V; ++i) {
        cout << i << ":" << distances[i] << " ";
    }
    cout << endl;

    return 0;
}
