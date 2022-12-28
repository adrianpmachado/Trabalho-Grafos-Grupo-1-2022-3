#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"
#include <sstream>
#include "funcionalidades.h"

using namespace std;

int main(int argc, char *argv[])
{
    // g++ src/*.cpp -o execGrupo1
    // Grafo(string path_arquivo_entrada, bool ehDirecionado, bool peso_vertice, bool peso_aresta)
    //./execGrupo1 "instancias Grafos não ponderados/grafo_1000_1.txt" arquivo.dot 0 0 0
    //./execGrupoX <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>,
    string caminho_entrada = argv[1];
    string caminho_saida = argv[2];
    Grafo *grafo_inicial = new Grafo(caminho_entrada, false, false, true, 2);
    vector<int> solucao = subconjunto_dominante_ponderado(1, grafo_inicial);

    cout << "\nO conjunto de vertices dominantes eh: \n";
    for(auto vertice : solucao) {
        cout << vertice << endl;
    }

    return 0;
}
