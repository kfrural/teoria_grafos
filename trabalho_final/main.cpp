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

// Implementação do BFS no grafo invertido
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
            for (int viz : it->second) {
                if (visitados.find(viz) == visitados.end()) {
                    visitados.insert(viz);
                    fila.push(viz);
                }
            }
        }
    }
    
    return visitados.size() - 1; // Ignora o próprio vértice
}

// Função para encontrar os dois alunos mais alcançáveis
pair<pair<int, int>, pair<int, int>> 
mais_alcancados(const unordered_map<int, vector<int>>& g_inv, int total = 29) {
    vector<pair<int, int>> alcances;
    alcances.reserve(total);
    
    for (int aluno = 1; aluno <= total; ++aluno) {
        int count = bfs_invertido(g_inv, aluno);
        alcances.emplace_back(aluno, count);
    }
    
    // Ordena em ordem decrescente baseado na contagem
    sort(alcances.begin(), alcances.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) { 
             return a.second > b.second; 
         });
    
    return {alcances[0], alcances[1]};
}

// Implementação do algoritmo de Warshall
vector<vector<bool>> warshall(int n, const vector<pair<int, int>>& arestas) {
    vector<vector<bool>> matriz(n, vector<bool>(n, false));
    
    // Inicializa a matriz com as arestas diretas
    for (const pair<int, int>& par : arestas) {
        matriz[par.first-1][par.second-1] = true;
    }
    
    // Algoritmo de Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matriz[i][j] = matriz[i][j] || (matriz[i][k] && matriz[k][j]);
            }
        }
    }
    
    return matriz;
}

// Função para ler arestas ponderadas
vector<tuple<int, int, double>> 
ler_arestas_pesadas(const string& caminho = "arquivo.txt") {
    vector<tuple<int, int, double>> arestas;
    ifstream arquivo(caminho);
    
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo");
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
            arestas.emplace_back(u, v, 1.0); // Peso padrão 1.0
        } else if (partes.size() == 3) {
            int u = stoi(partes[0]);
            int v = stoi(partes[1]);
            double peso = stod(partes[2]);
            arestas.emplace_back(u, v, peso);
        }
    }
    
    return arestas;
}

// Função para construir o grafo ponderado (CORRIGIDA)
unordered_map<int, vector<Edge>> 
construir_grafo_ponderado(const vector<tuple<int, int, double>>& arestas_pesadas) {
    unordered_map<int, vector<Edge>> grafo;
    
    // Primeiro, adicione todos os vértices encontrados nas arestas
    for (const tuple<int, int, double>& tupla : arestas_pesadas) {
        int origem = get<0>(tupla);
        int destino = get<1>(tupla);
        
        // Adiciona ambos os vértices ao mapa se ainda não existem
        grafo[origem];  // Operação vazia cria o vértice se não existe
        grafo[destino]; // Operação vazia cria o vértice se não existe
        
        // Adiciona a aresta
        grafo[origem].push_back({destino, get<2>(tupla)});
    }
    
    return grafo;
}

// Implementação do algoritmo de Dijkstra
unordered_map<int, double> 
dijkstra(const unordered_map<int, vector<Edge>>& grafo, int origem) {
    unordered_map<int, double> dist;
    priority_queue<pair<double, int>, vector<pair<double, int>>, 
                  greater<pair<double, int>>> heap;
    
    // Inicializa as distâncias como infinito
    for (const pair<int, vector<Edge>>& par : grafo) {
        dist[par.first] = numeric_limits<double>::infinity();
    }
    dist[origem] = 0.0;
    heap.push({0.0, origem});
    
    while (!heap.empty()) {
        double custo = heap.top().first;
        int atual = heap.top().second;
        heap.pop();
        
        if (custo > dist[atual]) continue;
        
        auto it = grafo.find(atual);
        if (it != grafo.end()) {
            for (const Edge& e : it->second) {
                double novo_custo = custo + e.peso;
                if (novo_custo < dist[e.destino]) {
                    dist[e.destino] = novo_custo;
                    heap.push({novo_custo, e.destino});
                }
            }
        }
    }
    
    return dist;
}

int main() {
    try {
        // Leitura do grafo
        auto arestas = ler_arestas();
        auto g_inv = grafo_invertido(arestas);

        cout << "=== Questão 1: Dois alunos com melhor desempenho ===\n";
        auto top2 = mais_alcancados(g_inv);
        cout << "Aluno " << top2.first.first << " é a Karla, alcançado por " 
             << top2.first.second << " outros alunos\n";
        cout << "Aluno " << top2.second.first << " é a Karla no semestre passado, alcançado por " 
             << top2.second.second << " outros alunos\n";

        cout << "\n=== Questão 5: BFS no grafo invertido ===\n";
        int teste;
        cout << "Digite um vértice: ";
        cin >> teste;
        
        cout << "Número de alunos que alcançam o aluno " << teste 
             << ": " << bfs_invertido(g_inv, teste) << "\n";

        cout << "\n=== Questão 6: Fecho Transitivo (Warshall) ===\n";
        auto matriz = warshall(29, arestas);
        cout << "Trecho da matriz (linha 0):\n";
        for (bool val : matriz[0]) {
            cout << val << " ";
        }
        cout << "\n";

        cout << "\n=== Questão 13: Dijkstra com pesos ===\n";
        auto arestas_pesadas = ler_arestas_pesadas();
        auto grafo_peso = construir_grafo_ponderado(arestas_pesadas);
        int origem = 1;
        auto distancias = dijkstra(grafo_peso, origem);
        
        cout << "Distâncias mínimas a partir do aluno " << origem << ":\n";
        for (const pair<int, double>& par : distancias) {
            cout << origem << " --> " << par.first << " = " << par.second << "\n";
        }

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
