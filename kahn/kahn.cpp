#include <bits/stdc++.h>
using namespace std;


vector<int> kahn(vector<vector<int>> & edges, int V){

    int indegree[V] = {0};
		for (int i = 0; i < V; i++) {
			for (auto it : edges[i]) {
				indegree[it]++;
			}
		}

		queue<int> q;
		for (int i = 0; i < V; i++) 
			if (indegree[i] == 0) 
				q.push(i);
			
		
		vector<int> topo;
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			topo.push_back(node);
			// node is in your topo sort
			// so please remove it from the indegree

			for (auto it : edges[node]) {
				indegree[it]--;
				if (indegree[it] == 0) q.push(it);
			}
		}

		return topo;
}


int main(int argc, char *argv[])
{
    string in = "";
    string out = "";
    cout << "palavras não bastam" << endl;

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

    int a, b;
    vector<vector<int>> edges(V+1);

    for (int i = 0; i < E; i++){
        fin >> a >> b;
        edges[a].push_back(b);
    }
    fin.close();


    vector<int> order = kahn(edges, V);

    if (not (out == "")){
        ofstream fout(out);
        if (not fout){
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        else{
            for (int i = 0, tam = order.size(); i < tam; ++i){
            fout << order[i] << " ";
            }
        }
        fout << endl;
        fout.close();
    }
    else{
        for (int i = 0, tam = order.size(); i < tam; ++i){
            cout << order[i] << " ";
        }
    }
    cout << endl;
    
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

    return 0;
}
