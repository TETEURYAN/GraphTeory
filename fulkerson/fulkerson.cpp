#include <bits/stdc++.h>
using namespace std;


bool bfs(vector<vector<int>> edges,int V, int s,int t,int pai[]){
	vector<bool> visited(V, false);

	visited[s] = true;

	queue<int> q;
	q.push(s);

	int front;
	while(not q.empty()){
		front = q.front();
		q.pop();
		for (int v = 0 ;v< V; v++){
			if(edges[front][v]>0 and not visited[v]){
				pai [v] = front;
				visited [v] = true;
				q.push(v);
			}
		}
	}
	return visited[t];
}

int fulkerson(vector<vector<int>> edges,int V, int s,int t) {
	int u,v,maxflow = 0;
	int *pai = new int[V];

	vector<vector<int>> residual(V);

	for(int i = 0; i<V;i++) {
		residual[i].resize(V);
		for(int j = 0; j<V;j++){
            residual[i][j] = edges[i][j];
        }
	}

	while(bfs(residual,V, s,t,pai)){
		int path = INT_MAX;
		for ( v = t;v!=s;v = pai[v]){
			u = pai[v];
			path = min(residual[u][v],path);
		}
		for( v = t;v!=s;v= pai[v]){
			u = pai[v];
			residual[u][v] -= path;
			residual[v][u] += path;
		}
		maxflow += path;
	}
	return maxflow;
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
    int s,t;
    fin >> s >> t;
    fin.close();


    int order = fulkerson(edges, V, s, t);

    if (not (out == "")){
        ofstream fout(out);
        if (not fout){
            cerr << "Could not open output file: " << out << endl;
            return 1;
        }
        else{
            cout << order << " " << endl;
        }
        fout << endl;
        fout.close();
    }
    else{
        cout << order << " " << endl;
    }
    cout << endl;


    return 0;
}