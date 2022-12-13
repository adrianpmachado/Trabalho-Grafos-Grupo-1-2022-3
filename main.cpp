#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"
#include <sstream>
#include "part1.h"

using namespace std;

int main(int argc, char *argv[])
{
    // g++ src/*.cpp -o execGrupo1
    // Grafo(string path_arquivo_entrada, bool ehDirecionado, bool peso_vertice, bool peso_aresta)
    //./execGrupo1 "instancias Grafos não ponderados/grafo_1000_1.txt" arquivo.dot 0 0 0
    //./execGrupoX <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>,
    bool Opc_Direc;
    bool Opc_Peso_Aresta;
    bool Opc_Peso_Nos;
    string caminho_entrada = argv[1];
    string caminho_saida = argv[2];
    std::istringstream(argv[3]) >> Opc_Direc;
    std::istringstream(argv[4]) >> Opc_Peso_Aresta;
    std::istringstream(argv[5]) >> Opc_Peso_Nos;
    Grafo *grafo_inicial = new Grafo(caminho_entrada, Opc_Direc, Opc_Peso_Aresta, Opc_Peso_Nos);
    realiza_operacao(menu(), grafo_inicial, caminho_saida);

    return 0;
}
