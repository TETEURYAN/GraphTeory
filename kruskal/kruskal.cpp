#include <bits/stdc++.h>
using namespace std;

bool compare(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b){
    return a.second < b.second;
}

struct UF {
    int tamanho;
    int* pai;
    int* rank;

    // Construtor da struct
    UF(int tamanho) {
        this->tamanho = tamanho;
        this->pai = new int[tamanho];
        this->rank = new int[tamanho];

    }

    // Destrutor da struct para liberar a memória alocada
    ~UF() {
        delete[] pai;
    }

    int Find(int x){ //Apontar para a raiz
        if(this->pai[x]!=x){
            this->pai[x] = this->Find(this->pai[x]);
        }
        return this->pai[x];
    }

    void Make_Set(int x){
        this->pai[x] = x;
        rank[x] = 0;
    }

    void Union(int x, int y){ //rank apra pegar fazer o union
        if(this->rank[x] >= this->rank[y]){
            this->pai[y] = x;
            if (this->rank[x] == this->rank[y]){
                this->rank[x]++;
            }
        }
        else{
            this->pai[x] = y;
        }
    }

};

vector<pair<int, int>> kruskal(int N, vector<pair<pair<int, int>, int>> & arestas,  int &sum){
    UF CJ(N);
    vector<pair<int, int>> MST;

    sort(arestas.begin(), arestas.end(), compare);

    for (int i = 0; i < N; i++){
        CJ.Make_Set(i);
    }

    for (auto sample: arestas){
        if (CJ.Find(sample.first.first) != CJ.Find(sample.first.second)){
            MST.push_back({sample.first.first, sample.first.second});
            sum += sample.second;
            CJ.Union(CJ.Find(sample.first.first), CJ.Find(sample.first.second));
        }
    }
    
    return MST;
}


int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
    bool ans = false;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1){
            output_file = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1){
            input_file = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0){
            ans = true;
        }
    }

    if (input_file == ""){
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin){
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }


    int N, m;
    fin >> N >> m;
    vector<pair<pair<int, int>, int>> arestas;

    int a, b, wt;
    for (int i = 0; i < m; i++){
        fin >> a >> b >> wt;
        arestas.push_back({{a-1, b-1}, wt});
    }

    fin.close();

    int sum = 0;
    vector<pair<int, int>> vertex = kruskal(N, arestas, sum);
    int tam = vertex.size();

    if(ans){
        for(int i = 0; i < tam; i++){
            cout << "(" << vertex[i].first+1 << "," << vertex[i].second+1 << ")" << endl;
        }
    }
    else{
        cout << sum << endl;
    }
        
    return 0;
}
