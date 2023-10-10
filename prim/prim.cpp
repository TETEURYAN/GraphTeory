#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> prim(vector<pair<int, int>> adj[], int N, int & sum, int init) 
{
    vector<pair<int, int>> result; 

    int parent[N + 1]; 
    int cost[N + 1]; 
    bool visited[N + 1];

    for(int i = 1; i <= N; i++){
        visited[i] = false;
        cost[i] = INT_MAX;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;//Fila de prioridade

    cost[1] = 0;
    parent[1] = -1;
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

   
    for (int i = 2; i <= N; i++){
        result.push_back(make_pair(i, parent[i]));
        sum += cost[i];
    }

    return result;
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

    int minimum_cost = 0;
    vector<pair<int, int>> result = prim(adj, N, minimum_cost, init);

    sort(result.begin(), result.end(), compare);

    if (!(out == "")){
        ofstream fout(out);
        if (!fout){
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        if (ans){
            for (auto sample : result)
                fout << "(" << sample.second << "," << sample.first << ") ";
        }
        else{
            fout << " " << minimum_cost << endl;
        }
        fout.close();
    }

    if(ans){
        for (auto sample : result)
            cout << "(" << sample.second << "," << sample.first << ") ";
    }
    else{
        cout << " " << minimum_cost << endl;
    }

    return 0;
}
