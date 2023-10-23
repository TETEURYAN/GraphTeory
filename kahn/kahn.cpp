#include <bits/stdc++.h>
using namespace std;


vector<int> kahn(vector<vector<int>> & edges, int V){

    map<int,int> degree;
    queue<int> q;
    vector<int> order;


    for(int i = 0; i < V; ++i){
        degree[i] = 0;
    }

    for(int Vi = 0; Vi < V; ++Vi){
        const auto & adj = edges[Vi];
        for(int j = 0, n = adj.size(); j < n; ++j){
            ++degree[adj[j]];
        }
    }
    
    for (int i = 0, n = degree.size(); i < n; ++i){
        if (not degree[i]){
            q.push(i);
        } 
    } 

    while(not q.empty())
    {
        int index = q.front();
        q.pop();
        order.push_back(index);

        for(int sample : edges[index]){
            if(--degree[sample] == 0){
                q.push(sample);
                degree.erase(sample);
            }
        }
    }
    return order;
}


int main()
{
    // string in = "";
    // string out = "";
    // cout << "palavras não bastam" << endl;

    // for (int i = 1; i < argc; i++){
    //     if (strcmp(argv[i], "-h") == 0){
    //         cout << "Help:" << endl;
    //         cout << "-h: mostra o help" << endl;
    //         cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
    //         cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
    //         cout << "-i: vértice inicial" << endl;
            
    //         return 0;
    //     }
    //     else if (strcmp(argv[i], "-o") == 0 and i < argc - 1){
    //         out = argv[++i];
    //     }
    //     else if (strcmp(argv[i], "-f") == 0 and i < argc - 1){
    //         in = argv[++i];
    //     }
    // }

    // if (in == ""){
    //     cerr << "No input file specified. Use the -f parameter." << endl;
    //     return 1;
    // }

    // ifstream fin(in);

    // if (not fin){
    //     cerr << "Could not open input file: " << in << endl;
    //     return 1;
    // }

    int V, E;
    cin >> V >> E;

    int a, b;
    vector<vector<int>> edges;

    for (int i = 0; i < E; i++){
        cin >> a >> b;
        edges[a-1].push_back(b-1);
    }

//     vector<vector<int>> graph {
//     { 1 },
//     { 6 },
//     { 1, 3, 6 },
//     { 1, 4, 5 },
//     {  },
//     { 4 },
//     { 5 },
//     { 0, 6 },
//   };


    // fin.close();
    //         for (int i = 1; i <= V; ++i){
    //            cout << order[i] << " ";
    //         }

    vector<int> order = kahn(edges, V);
        for (int i = 0; i < 8; ++i){
           cout << order[i] << " ";
        }

    // if (not (out == "")){
    //     ofstream fout(out);
    //     if (not fout){
    //         cerr << "Could not open output file: " << out << endl;
    //         return 1;
    //     }
    //     else{
    //     }
    //     fout << endl;
    //     fout.close();
    // }
    // else{
    // }
    // cout << endl;

    return 0;
}
