#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int u;
    int v;
    int weight;

    bool equals(struct edge b)
    {
        if (this->u == b.u && this->v == b.v && this->weight==b.weight) return true;
        return false;
    }
};

struct Graph
{
private:
    //Nº de vértices e arestas
    int N, E;
    //Vetor de adjacências [[{V, Peso}]]
    std::vector<std::pair<int, int>>* adj;
    //Vetor de arestas [{{Vi, Vf}, Peso}]
    std::vector<edge> edges;
    //Flag de grafo direcionado
    bool Dgraf;

public:
    //Construtor (Número de vértices, arestas e flag de Digrafo (default = false))
    Graph(int N, int E, bool Dgraf=false){
        this->N = N;
        this->E = E;
        this->Dgraf=Dgraf;
        this->adj = new std::vector<std::pair<int, int>>[N];
    }


    //Insere arestas no grafo
    void insertEdge(int a, int b, int wt){
        //Insere a ida, se não for digrafo insere a volta
        adj[a-1].push_back(std::make_pair(b-1, wt));
        if (!Dgraf) adj[b-1].push_back(std::make_pair(a-1, wt));
        edges.push_back({a-1, b-1, wt});
        if (!Dgraf) edges.push_back({b-1, a-1, wt});
    }

    int getNodeCount(){
        return N;
    }

    int getEdgeCount(){
        return E;
    }

    std::vector<edge> getEdgesList(){
        return edges;
    }

    std::vector<std::pair<int, int>>* getAdjList(){
        return adj;
    }


};

//BF Algorithm
vector<int> bellmanFord(Graph G, int iN)
{
    int N = G.getNodeCount();
    vector<int> dist(N);
    fill(dist.begin(), dist.end(), (INT_MAX/2));
    dist[iN] = 0;
    for (int i = 0; i < N-1; i++){
        for (auto e: G.getEdgesList()){
            //Se a distância até u + peso da aresta uv < distancia até v
            //Então distancia até v = distancia até u + peso da aresta uv
            if (dist[e.u] + e.weight < dist[e.v]) dist[e.v] = dist[e.u] + e.weight;
        }
    }
    for (int i = 0; i < N-1; i++){
        for (auto e: G.getEdgesList()){
            //Se a distância até u + peso da aresta uv < distancia até v
            //Então distancia até v = distancia até u + peso da aresta uv
            if (dist[e.u] + e.weight < dist[e.v]) dist[e.v] = -(INT_MAX/2);
        }
    }

    return dist;
}

int main(int argc, char *argv[]){
    string in = "";
    string out = "";
    int startVertex = 0;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1){
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1){
            in = argv[++i];
        }

    }

    if (in == ""){
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }
    
    ifstream fin(in);
    if (!fin){
        cerr << "Could not open input file: " << in << endl;
        return 1;
    }

    int N, E;
    fin >> N >> E;
    Graph G(N, E);
    int a, b, wt;

    for (int e = 0; e < E; e++){
        fin >> a >> b >> wt;
        G.insertEdge(a, b, wt);
    }
    fin.close();

    vector<int> dist = bellmanFord(G, startVertex);

    if (!(out=="")){
        ofstream fout(out);
        if (!fout){
            cerr << "Could not open output file:" << out << endl;
            return 1;
        }
        for (int i = 0; i < N; i++) {
            fout << i+1 << ":" << dist[i] << " ";
        }
        fout << endl;
        fout.close();
    }
    
    for (int i = 0; i < N; i++) {
        cout << i+1 << ":" << dist[i] << " ";
    }
    cout << endl;


    return 0;
}