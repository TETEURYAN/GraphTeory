#include <bits/stdc++.h>
using namespace std;

bool compare(const pair<int, int> &a, const pair<int, int> &b){ //funcao que compara em função do peso
    if (a.first != b.first) return a.first < b.first;
    else  return a.second < b.second;
}

pair<vector<pair<int, int>>, int> prim(vector<pair<int, int>> adj[], int N, int init) // Função da árvore geradora mínima 
{
    vector<pair<int, int>> result; // vetor de resultado (vertice, pai))

    int parent[N + 1]; //vetor de pai
    int cost[N + 1]; //vetor de custo
    bool visited[N + 1];// vetor de visitado

    for (int i = 1; i <= N; i++){//Custo infinito e nenhum visitado
        cost[i] = INT_MAX;
        visited[i] = false;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;//Fila de prioridade

    cost[1] = 0;//custo do vertice 1 = 0
    parent[1] = -1;//Vertice 1 nao tem pai
    queue.push({0, 1});

    while (not queue.empty())
    {
        int u = queue.top().second;
        queue.pop();

        visited[u] = true;

        for (auto sample : adj[u])
        {
            int v = sample.first;
            int force = sample.second;
            if (visited[v] == false && force < cost[v])
            {
                parent[v] = u;
                cost[v] = force;
                queue.push({cost[v], v});
            }
        }
    }

    int summcost = 0;
    for (int i = 2; i <= N; i++)
    {
        result.push_back(make_pair(i, parent[i]));
        summcost += cost[i];
    }

    return make_pair(result, summcost);
}

int main(int argc, char *argv[])
{
    string in = "";
    string out = "";
    bool ans = false;
    int init = 1;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            cout << "-i: vértice inicial (para o algoritmo de Prim)" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1){
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1){
            in = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0){
            ans = true;
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1){
            init = atoi(argv[++i]);
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

    int N, m;
    fin >> N >> m;
    vector<pair<int, int>> adj[N + 1];

    int a, b, wt;
    for (int i = 0; i < m; i++){
        fin >> a >> b >> wt;
        adj[a].push_back(make_pair(b, wt));
        adj[b].push_back(make_pair(a, wt));
    }

    fin.close();

    pair<vector<pair<int, int>>, int> result = prim(adj, N, init);

    vector<pair<int, int>> pairsArray = result.first; 
    sort(pairsArray.begin(), pairsArray.end(), compare);

    if (!(out == "")){
        ofstream fout(out);
        if (!fout){
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        if (ans){
            for (auto sample : pairsArray)
                fout << "(" << sample.second << "," << sample.first << ") ";
        }
        else{
            fout << " " << result.second << endl;
        }
        fout.close();
    }

    if(ans){
        for (auto sample : pairsArray)
            cout << "(" << sample.second << "," << sample.first << ") ";
    }
    else{
        cout << " " << result.second << endl;
    }

    return 0;
}
