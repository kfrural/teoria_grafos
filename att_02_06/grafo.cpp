#include "grafo.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
using namespace std;


Grafo::Grafo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo. Verifique o nome ou o local." << endl;
        return;
    }

    arquivo >> n >> m;

    map<string, int> nomeParaIndice;
    vector<string> vertices;
    int proximoIndice = 0;

    for (int i = 0; i < n; i++) {
        string nome;
        arquivo >> nome;
        if (nomeParaIndice.find(nome) == nomeParaIndice.end()) {
            nomeParaIndice[nome] = proximoIndice++;
            vertices.push_back(nome);
        }
    }

    matrizAdj.resize(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        string nome1, nome2;
        arquivo >> nome1 >> nome2;

        int idx1 = nomeParaIndice[nome1];
        int idx2 = nomeParaIndice[nome2];

        if (idx1 == -1 || idx2 == -1) {
            cout << "Warning: Ignorando aresta inválida entre vértices " 
                 << nome1 << " e " << nome2 << endl;
            continue;
        }

        matrizAdj[idx1][idx2]++;
        matrizAdj[idx2][idx1]++;
    }

    arquivo.close();
}

void Grafo::imprimirMatriz() const {
    cout << "\nMatriz de Adjacência:" << endl;
    for (const auto& linha : matrizAdj) {
        for (int val : linha) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void Grafo::imprimirArestas() const {
    cout << "\nLista de Arestas:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {  
            for (int k = 0; k < matrizAdj[i][j]; k++) {
                cout << i << " - " << j << endl;
            }
        }
    }
}

void Grafo::calcularGraus() const {
    cout << "\nGrau de cada vértice:" << endl;
    for (int i = 0; i < n; i++) {
        int grau = 0;
        for (int j = 0; j < n; j++) {
            grau += matrizAdj[i][j];
        }
        cout << "Vertice " << i << ": grau " << grau << endl;
    }
}

bool Grafo::ehSimples() const {
    for (int i = 0; i < n; i++) {
        if (matrizAdj[i][i] != 0) return false;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matrizAdj[i][j] > 1) return false;
        }
    }
    return true;
}

bool Grafo::ehPseudografo() const {
    for (int i = 0; i < n; i++) {
        if (matrizAdj[i][i] != 0) return true;
    }
    return false;
}

bool Grafo::ehMultigrafo() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matrizAdj[i][j] > 1) return true;
        }
    }
    return false;
}

bool Grafo::ehCompleto() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matrizAdj[i][j] == 0) return false;
        }
    }
    return true;
}

bool Grafo::ehConexo() const {
    vector<bool> visitado(n, false);
    queue<int> fila;

    int primeiroVertice = 0;
    while (primeiroVertice < n && matrizAdj[primeiroVertice].empty()) {
        primeiroVertice++;
        if (primeiroVertice >= n) return false;
    }

    fila.push(primeiroVertice);
    visitado[primeiroVertice] = true;

    while (!fila.empty()) {
        int v = fila.front();
        fila.pop();

        for (int i = 0; i < n; i++) {
            if (matrizAdj[v][i] > 0 && !visitado[i]) {
                visitado[i] = true;
                fila.push(i);
            }
        }
    }

    for (bool v : visitado) {
        if (!v) return false;
    }
    return true;
}

void Grafo::densoOuEsparso() const {
    int maxArestas = n * (n - 1) / 2;
    double densidade = (double)m / maxArestas;

    cout << "\nAnálise de Densidade:" << endl;
    cout << "Densidade: " << (densidade * 100) << "%" << endl;
    if (densidade > 0.5) {
        cout << "O grafo é DENSO." << endl;
    } else {
        cout << "O grafo é ESPARSO." << endl;
    }
}

void Grafo::propriedades() const {
    cout << "\nPropriedades do Grafo:" << endl;

    if (ehSimples()) {
        cout << "- É um grafo simples" << endl;
    } else if (ehPseudografo()) {
        cout << "- É um pseudografo" << endl;
    } else if (ehMultigrafo()) {
        cout << "- É um multigrafo" << endl;
    }

    if (ehCompleto()) {
        cout << "- É um grafo completo" << endl;
    } else {
        cout << "- Não é um grafo completo" << endl;
    }

    if (ehConexo()) {
        cout << "- É um grafo conexo" << endl;
    } else {
        cout << "- É um grafo desconexo" << endl;
    }

    densoOuEsparso();
}
