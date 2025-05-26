
#define GRAFO_H

#include <vector>
#include <queue>
#include <fstream>

class Grafo {
private:
    int n;
    int m;
    std::vector<std::vector<int>> matrizAdj;

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
};