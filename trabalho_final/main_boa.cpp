#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <algorithm>
using namespace std;


// Estrutura para armazenar uma aresta ponderada
struct Edge {
    int destino;
    double peso;
};


// Função para ler arestas do arquivo
vector<pair<int, int>> ler_arestas(const string& caminho = "arquivo.txt") {
    vector<pair<int, int>> arestas;
    ifstream arquivo(caminho);
    
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo");
    }

    int u, v;
    while (arquivo >> u >> v) {
        arestas.emplace_back(u, v);
    }
    
    arquivo.close();
    return arestas;
}


// Função para construir o grafo invertido
unordered_map<int, vector<int>> grafo_invertido(const vector<pair<int, int>>& arestas) {
    unordered_map<int, vector<int>> invertido;
    
    for (const pair<int, int>& par : arestas) {
        invertido[par.second].push_back(par.first);
    }
    
    return invertido;
}


// Implementação do BFS no grafo invertido (conta quantos alcançam o vértice)
int bfs_invertido(const unordered_map<int, vector<int>>& grafo_inv, int inicio) {
    unordered_set<int> visitados;
    queue<int> fila;
    
    fila.push(inicio);
    visitados.insert(inicio);
    
    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        
        auto it = grafo_inv.find(atual);
        if (it != grafo_inv.end()) {
            for (size_t idx = 0; idx < it->second.size(); ++idx) {
                int viz = it->second[idx];
                if (visitados.find(viz) == visitados.end()) {
                    visitados.insert(viz);
                    fila.push(viz);
                }
            }
        }
    }
    
    return static_cast<int>(visitados.size()) - 1; // Ignora o próprio vértice
}

// BFS para distância mínima entre dois vértices (grafo invertido)
int bfs_distancia(const unordered_map<int, vector<int>>& grafo_inv, int origem, int destino) {
    if (origem == destino) return 0;
    
    unordered_set<int> visitados;
    queue<pair<int,int>> fila;  // pair = (vértice, distância)
    
    fila.push(make_pair(origem, 0));
    visitados.insert(origem);
    
    while (!fila.empty()) {
        pair<int,int> front = fila.front();
        int atual = front.first;
        int dist = front.second;
        fila.pop();
        
        if (atual == destino) return dist;
        
        auto it = grafo_inv.find(atual);
        if (it != grafo_inv.end()) {
            for (size_t idx = 0; idx < it->second.size(); ++idx) {
                int viz = it->second[idx];
                if (visitados.find(viz) == visitados.end()) {
                    visitados.insert(viz);
                    fila.push(make_pair(viz, dist + 1));
                }
            }
        }
    }
    return numeric_limits<int>::max();
}


// Função para encontrar os dois alunos mais alcançáveis
pair<pair<int, int>, pair<int, int>> 
mais_alcancados(const unordered_map<int, vector<int>>& g_inv, int total = 29) {
    vector<pair<int, int>> alcances;
    alcances.reserve(total);
    
    for (int aluno = 1; aluno <= total; ++aluno) {
        int count = bfs_invertido(g_inv, aluno);
        alcances.push_back(make_pair(aluno, count));
    }
    
    sort(alcances.begin(), alcances.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) { 
             return a.second > b.second; 
         });
    
    return make_pair(alcances[0], alcances[1]);
}


// Implementação do algoritmo de Warshall (fecho transitivo)
vector<vector<bool>> warshall(int n, const vector<pair<int, int>>& arestas) {
    vector<vector<bool>> matriz(n, vector<bool>(n, false));
    
    for (const pair<int, int>& par : arestas) {
        matriz[par.first-1][par.second-1] = true;
    }
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (matriz[i][k]) {
                for (int j = 0; j < n; ++j) {
                    matriz[i][j] = matriz[i][j] || matriz[k][j];
                }
            }
        }
    }
    
    return matriz;
}

// Função para ler arestas ponderadas
vector<tuple<int, int, double>> 
ler_arestas_pesadas(const string& caminho = "arquivo_pesos.txt") {
    vector<tuple<int, int, double>> arestas;
    ifstream arquivo(caminho);
    
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de pesos");
    }

    string linha;
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        vector<string> partes;
        string parte;
        
        while (iss >> parte) {
            partes.push_back(parte);
        }
        
        if (partes.size() == 2) {
            int u = stoi(partes[0]);
            int v = stoi(partes[1]);
            arestas.push_back(make_tuple(u, v, 1.0)); // Peso padrão 1.0
        } else if (partes.size() == 3) {
            int u = stoi(partes[0]);
            int v = stoi(partes[1]);
            double peso = stod(partes[2]);
            arestas.push_back(make_tuple(u, v, peso));
        }
    }
    
    arquivo.close();
    return arestas;
}

// Função para construir o grafo ponderado
unordered_map<int, vector<Edge>> 
construir_grafo_ponderado(const vector<tuple<int, int, double>>& arestas_pesadas) {
    unordered_map<int, vector<Edge>> grafo;
    
    for (size_t i = 0; i < arestas_pesadas.size(); ++i) {
        int origem = get<0>(arestas_pesadas[i]);
        int destino = get<1>(arestas_pesadas[i]);
        double peso = get<2>(arestas_pesadas[i]);
        
        grafo[origem];  // boostrap dos vértices
        grafo[destino];
        grafo[origem].push_back({destino, peso});
    }
    
    return grafo;
}

// Implementação do algoritmo de Dijkstra
unordered_map<int, double> 
dijkstra(const unordered_map<int, vector<Edge>>& grafo, int origem) {
    unordered_map<int, double> dist;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> heap;
    
    for (auto it = grafo.begin(); it != grafo.end(); ++it) {
        dist[it->first] = numeric_limits<double>::infinity();
    }
    dist[origem] = 0.0;
    heap.push(make_pair(0.0, origem));
    
    while (!heap.empty()) {
        pair<double,int> top = heap.top();
        double custo = top.first;
        int atual = top.second;
        heap.pop();
        
        if (custo > dist[atual]) continue;
        
        auto it = grafo.find(atual);
        if (it != grafo.end()) {
            for (size_t i = 0; i < it->second.size(); ++i) {
                const Edge& e = it->second[i];
                double novo_custo = custo + e.peso;
                if (novo_custo < dist[e.destino]) {
                    dist[e.destino] = novo_custo;
                    heap.push(make_pair(novo_custo, e.destino));
                }
            }
        }
    }
    
    return dist;
}

// Função para calcular a centralidade de grau (entrada)
unordered_map<int, int> centralidade_grau_entrada(const unordered_map<int, vector<int>>& grafo_inv, int total = 29) {
    unordered_map<int, int> grau_entrada;
    for (int i = 1; i <= total; ++i) {
        if (grafo_inv.count(i)) {
            grau_entrada[i] = (int) grafo_inv.at(i).size();
        } else {
            grau_entrada[i] = 0;
        }
    }
    return grau_entrada;
}

// Função para calcular centralidade de aproximação (closeness)
unordered_map<int, int> centralidade_aproximacao(const unordered_map<int, vector<int>>& grafo_inv, int total = 29) {
    unordered_map<int, int> closeness;
    for (int i = 1; i <= total; ++i) {
        int soma = 0;
        bool tem_distancia = false;
        for (int j = 1; j <= total; ++j) {
            if (i != j) {
                int d = bfs_distancia(grafo_inv, i, j);
                if (d != numeric_limits<int>::max()) {
                    soma += d;
                    tem_distancia = true;
                }
            }
        }
        if (tem_distancia) {
            closeness[i] = soma;
        }
    }
    return closeness;
}


int main() {
    try {
        cout << "Lendo arestas do arquivo 'arquivo.txt'...\n";
        vector<pair<int,int>> arestas = ler_arestas();
        unordered_map<int, vector<int>> g_inv = grafo_invertido(arestas);

        cout << "\n=== Questão 1: Dois alunos com melhor desempenho ===\n";
        pair<pair<int,int>, pair<int,int>> top2 = mais_alcancados(g_inv);
        cout << "Aluno " << top2.first.first << " eh a Karla: alcançado por " << top2.first.second << " alunos\n";
        cout << "Aluno " << top2.second.first << " eh alguem muito parecido com a Karla: alcançado por " << top2.second.second << " alunos\n";

        cout << "\n=== Questão 5: BFS no grafo invertido ===\n";
        cout << "Digite um vértice: ";
        int vert;
        cin >> vert;
        cout << "Número de alunos que alcançam o aluno " << vert << ": " << bfs_invertido(g_inv, vert) << "\n";

        cout << "\n=== Questão 6: Fecho Transitivo (Warshall) ===\n";
        vector<vector<bool>> fecho = warshall(29, arestas);
        cout << "Digite um vértice para saber quem ele alcança: ";
        int x;
        cin >> x;
        cout << "Ele alcança: ";
        for (int j = 0; j < 29; ++j) {
            if (fecho[x-1][j]) cout << (j+1) << " ";
        }
        cout << "\nDigite um vértice para saber quem o alcança: ";
        int y;
        cin >> y;
        cout << "É alcançado por: ";
        for (int i = 0; i < 29; ++i) {
            if (fecho[i][y-1]) cout << (i+1) << " ";
        }
        cout << "\n";

        cout << "\n=== Questão 9: Centralidades ===\n";

        cout << "\n--- Centralidade de Grau (entrada) ---\n";
        cout << "Os 5 alunos com maior influência direta:\n";
        unordered_map<int,int> grauEntrada = centralidade_grau_entrada(g_inv);
        vector<pair<int,int>> grauVec(grauEntrada.begin(), grauEntrada.end());
        sort(grauVec.begin(), grauVec.end(), 
            [](const pair<int,int>& a, const pair<int,int>& b) {
                return a.second > b.second;
            });
        for (size_t i = 0; i < grauVec.size() && i < 5; ++i) {
            cout << "Aluno " << grauVec[i].first << ": grau de entrada = " << grauVec[i].second << "\n";
        }

        cout << "\n--- Centralidade de Aproximação ---\n";
        cout << "Os 5 alunos com as menores somas das distâncias mínimas até os demais alunos:\n";
        unordered_map<int,int> closeness = centralidade_aproximacao(g_inv);
        vector<pair<int,int>> closenessVec(closeness.begin(), closeness.end());
        sort(closenessVec.begin(), closenessVec.end(),
            [](const pair<int,int>& a, const pair<int,int>& b){
                return a.second < b.second;
            });
        for (size_t i = 0; i < closenessVec.size() && i < 5; ++i) {
            cout << "Aluno " << closenessVec[i].first << ": soma das distâncias = " << closenessVec[i].second << "\n";
        }


        cout << "\n=== Questão 13: Dijkstra com pesos ===\n";
        cout << "Lendo arestas com peso do arquivo 'arquivo_pesos.txt'...\n";
        vector<tuple<int,int,double>> arestas_pesadas = ler_arestas_pesadas("arquivo_pesos.txt");
        unordered_map<int, vector<Edge>> grafo_peso = construir_grafo_ponderado(arestas_pesadas);

        cout << "Digite o vértice de origem: ";
        int origem;
        cin >> origem;

        unordered_map<int,double> distancias = dijkstra(grafo_peso, origem);
        cout << "Distâncias a partir de " << origem << ":\n";
        for (unordered_map<int,double>::const_iterator it = distancias.begin(); it != distancias.end(); ++it) {
            cout << origem << " -> " << it->first << " = " << it->second << "\n";
        }

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
