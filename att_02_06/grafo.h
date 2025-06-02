#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <queue>
#include <fstream>
#include <map>
#include <string>

class Grafo {
private:
    int n;  // número de vértices
    int m;  // número de arestas
    std::vector<std::vector<int>> matrizAdj;
    std::map<std::string, int> nomeParaIndice;
    std::vector<std::string> indiceParaNome;
    
public:
    Grafo(const std::string& nomeArquivo);
    void imprimirMatriz() const;
    void imprimirArestas() const;
    void calcularGraus() const;
    bool ehSimples() const;
    bool ehPseudografo() const;
    bool ehMultigrafo() const;
    bool ehCompleto() const;
    bool ehConexo() const;
    void densoOuEsparso() const;
    void propriedades() const;
    
    // Funções para conversão
    int getVerticeIndex(const std::string& nome) const {
        auto it = nomeParaIndice.find(nome);
        return (it != nomeParaIndice.end()) ? it->second : -1;
    }
    
    std::string getVerticeName(int index) const {
        if (index >= 0 && index < n) {
            return indiceParaNome[index];
        }
        return "";
    }
};

#endif  // GRAFO_H
