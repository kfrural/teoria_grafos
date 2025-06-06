#include <iostream>
#include "grafo.h"
#include <map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

Grafo::Grafo(const string& nomeArquivo) {
    nomeParaIndice["mat_163"] = 1;
    indiceParaNome.push_back("mat_163");
    
    nomeParaIndice["dcc_251"] = 2;
    indiceParaNome.push_back("dcc_251");
    
    nomeParaIndice["dcc_316"] = 3;
    indiceParaNome.push_back("dcc_316");
    
    nomeParaIndice["dcc_158"] = 4;
    indiceParaNome.push_back("dcc_158");
    
    nomeParaIndice["let_150"] = 5;
    indiceParaNome.push_back("let_150");
    
    nomeParaIndice["let_152"] = 6;
    indiceParaNome.push_back("let_152");
    
    nomeParaIndice["dcc_310"] = 7;
    indiceParaNome.push_back("dcc_310");
    
    nomeParaIndice["mat_153"] = 8;
    indiceParaNome.push_back("mat_153");
    
    nomeParaIndice["mat_121"] = 9;
    indiceParaNome.push_back("mat_121");
    
    nomeParaIndice["dcc_162"] = 10;
    indiceParaNome.push_back("dcc_162");
    
    nomeParaIndice["dcc_254"] = 11;
    indiceParaNome.push_back("dcc_254");
    
    nomeParaIndice["dcc_496"] = 12;
    indiceParaNome.push_back("dcc_496");
    
    nomeParaIndice["mat_152"] = 13;
    indiceParaNome.push_back("mat_152");
    
    nomeParaIndice["dcc_398"] = 14;
    indiceParaNome.push_back("dcc_398");
    
    nomeParaIndice["fis_153"] = 15;
    indiceParaNome.push_back("fis_153");
    
    nomeParaIndice["dcc_450"] = 16;
    indiceParaNome.push_back("dcc_450");
    
    nomeParaIndice["dcc_288"] = 17;
    indiceParaNome.push_back("dcc_288");
    
    nomeParaIndice["mat_157"] = 18;
    indiceParaNome.push_back("mat_157");
    
    nomeParaIndice["dcc_497"] = 19;
    indiceParaNome.push_back("dcc_497");
    
    nomeParaIndice["fis_155"] = 20;
    indiceParaNome.push_back("fis_155");
    
    nomeParaIndice["mat_169"] = 21;
    indiceParaNome.push_back("mat_169");
    
    nomeParaIndice["dcc_441"] = 22;
    indiceParaNome.push_back("dcc_441");
    
    nomeParaIndice["dcc_289"] = 23;
    indiceParaNome.push_back("dcc_289");
    
    nomeParaIndice["dcc_478"] = 24;
    indiceParaNome.push_back("dcc_478");
    
    nomeParaIndice["dcc_491"] = 25;
    indiceParaNome.push_back("dcc_491");
    
    nomeParaIndice["dcc_461"] = 26;
    indiceParaNome.push_back("dcc_461");
    
    nomeParaIndice["dcc_315"] = 27;
    indiceParaNome.push_back("dcc_315");
    
    nomeParaIndice["mat_155"] = 28;
    indiceParaNome.push_back("mat_155");
    
    nomeParaIndice["mat_174"] = 29;
    indiceParaNome.push_back("mat_174");
    
    nomeParaIndice["dcc_455"] = 30;
    indiceParaNome.push_back("dcc_455");
    
    nomeParaIndice["dcc_494"] = 31;
    indiceParaNome.push_back("dcc_494");
    
    nomeParaIndice["dcc_393"] = 32;
    indiceParaNome.push_back("dcc_393");
    
    nomeParaIndice["dcc_453"] = 33;
    indiceParaNome.push_back("dcc_453");
    
    nomeParaIndice["dcc_486"] = 34;
    indiceParaNome.push_back("dcc_486");
    
    nomeParaIndice["dcc_476"] = 35;
    indiceParaNome.push_back("dcc_476");
    
    nomeParaIndice["dcc_440"] = 36;
    indiceParaNome.push_back("dcc_440");
    
    nomeParaIndice["dcc_458"] = 37;
    indiceParaNome.push_back("dcc_458");
    
    nomeParaIndice["dcc_300"] = 38;
    indiceParaNome.push_back("dcc_300");
    
    nomeParaIndice["dcc_468"] = 39;
    indiceParaNome.push_back("dcc_468");
    
    nomeParaIndice["dcc_495"] = 40;
    indiceParaNome.push_back("dcc_495");
    
    nomeParaIndice["dcc_270"] = 41;
    indiceParaNome.push_back("dcc_270");
    
    nomeParaIndice["dcc_462"] = 42;
    indiceParaNome.push_back("dcc_462");
    
    nomeParaIndice["dcc_409"] = 43;
    indiceParaNome.push_back("dcc_409");
    
    nomeParaIndice["dcc_272"] = 44;
    indiceParaNome.push_back("dcc_272");
    
    nomeParaIndice["dcc_400"] = 45;
    indiceParaNome.push_back("dcc_400");
    
    nomeParaIndice["dcc_498"] = 46;
    indiceParaNome.push_back("dcc_498");
    
    nomeParaIndice["dcc_499"] = 47;
    indiceParaNome.push_back("dcc_499");
    
    nomeParaIndice["dcc_401"] = 48;
    indiceParaNome.push_back("dcc_401");

    n = 48; // número total de vértices
    matrizAdj.resize(n, vector<int>(n, 0));
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
