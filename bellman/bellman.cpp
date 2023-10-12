#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int u;
    int v;
    int weight;
};

vector<int> bellman(vector<edge> adj, int V, int src){
    vector<int> dist(V);

    fill_n(dist.begin(), V, (INT_MAX)/2);
    
    dist[src] = 0;

    for (int i = 1; i <= (V-1); i++){
        for (auto edge : adj){
            if (((dist[edge.u] + edge.weight) < dist[edge.v])){
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    for (auto edge : adj)
        if ((dist[edge.u] + edge.weight < dist[edge.v])){
            cout << "Ciclo negativo" << endl;
            break;
        }

    return dist;
}
int main(int argc, char *argv[])
{
    string in = "";
    string out = "";
    int initial = 0;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial" << endl;
            
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 and i < argc - 1){
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 and i < argc - 1){
            in = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 and i < argc - 1){
            initial = atoi(argv[++i]);
            initial--;
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
    vector<edge> adj(V);

    for (int i = 0; i < E; i++){
        fin >> a >> b >> cost;
        adj.push_back({a-1, b-1, cost});
    }

    fin.close();

    vector<int> distances = bellman(adj, V, initial);

    if (not (out == "")){
        ofstream fout(out);
        if (not fout){
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
        if(distances[i-1] != (INT_MAX/2)){
            cout << i << ":" << distances[i-1] << " ";
        }
        else{
            cout << i << ":" << -1 << " ";
        }
    }
    cout << endl;

    return 0;
}
