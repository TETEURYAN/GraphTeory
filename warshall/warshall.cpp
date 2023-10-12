#include <bits/stdc++.h>
using namespace std;
#define max INT_MAX/2


vector<vector<int>> floyd(int src, int V, const vector<vector<int>> & edges ){
    vector<vector<int>> dist(V, vector<int>(V+1, max));

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            dist[i][j] = edges[i][j];

    dist[src][0] = 0;
    dist[0][src] = 0;
    for(int i = 0; i < V; i++)        
        for(int j = 0; j < V; j++)
            for(int k = 0; k < V; k++)
                if (dist[i][j] > (dist[i][k] + dist[k][j]) and (dist[k][j] != max and dist[i][k] != max))
                    dist[i][j] = dist[i][k] + dist[k][j];
            
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
    vector<vector<int>> edges(V, vector<int>(V, max));

    for (int i = 0; i < E; i++){
        fin >> a >> b >> cost;
        edges[a-1][b-1] = cost;
        edges[b-1][a-1] = cost;
    }

    vector<vector<int>> distances = floyd(initial, V, edges);

    fin.close();

    if (not (out == "")){
        ofstream fout(out);
        if (not fout){
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        for (int i = 1; i <= V; ++i){
            if(distances[initial][i-1] != max){
                fout << i << ":" << distances[initial][i-1] << " ";
            }
            else{
                fout << i << ":" << -1 << " ";
            }
        }
        fout << endl;
        fout.close();
    }

    for (int i = 1; i <= V; ++i) {
        if(distances[initial][i-1] != max){
            cout << i << ":" << distances[initial][i-1] << " ";
        }
        else{
            cout << i << ":" << -1 << " ";
        }
    }
    cout << endl;

    return 0;
}
