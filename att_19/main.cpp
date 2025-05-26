#include <iostream>
#include <string>
#include "grafo.h"

using namespace std;

int main() {
    string nomeArquivo;
    cout << "Digite o nome do arquivo (ex.: entrada.txt): ";
    cin >> nomeArquivo;

    Grafo g(nomeArquivo);
    g.imprimirMatriz();
    g.imprimirArestas();
    g.calcularGraus();
    g.propriedades();

    return 0;
}