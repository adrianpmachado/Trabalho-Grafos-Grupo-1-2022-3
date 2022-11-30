#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"

using namespace std;


int main (int argc, char * argv[])
{
    //Grafo(string path_arquivo_entrada, bool ehDirecionado, bool peso_vertice, bool peso_aresta)
    //./execGrupoX "instancias Grafos não ponderados/grafo_1000_1.txt" arquivo.dot 0 0 0
    //grafo01->salva_grafo("saidas/saidas.txt");
    string caminho = argv [1];
    Grafo* grafo01 = new Grafo(caminho,0,0,0);
    grafo01->imprimir_grafo_lista_de_adjacencia();
    return 0;
}
