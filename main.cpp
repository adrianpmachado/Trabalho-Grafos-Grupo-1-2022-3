#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"

using namespace std;


int main (int argc, char * argv[])
{
    //g++ src/*.cpp -o execGrupo1
    //Grafo(string path_arquivo_entrada, bool ehDirecionado, bool peso_vertice, bool peso_aresta)
    //./execGrupo1 "instancias Grafos não ponderados/grafo_1000_1.txt" arquivo.dot 0 0 0
    //./execGrupoX <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>,

    string caminho_entrada = argv [1];
    string caminho_saida = argv[2];
    bool Opc_Direc = istringstream(argv[3]);
    bool Opc_Peso_Aresta = istringstream(argv[4]);
    bool Opc_Peso_Aresta = istringstream(argv[5]);
    Grafo* grafo01 = new Grafo(caminho_entrada,0,0,0);
    grafo01->salva_grafo(caminho_saida);
    return 0;
}
