#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"

using namespace std;


int main (int argc, char * argv[])
{
    //./execGrupoX "instancias Grafos não ponderados/grafo_1000_1.txt" arquivo.dot 0 0 0
    
    //Grafo* grafo01 = new Grafo("instancias Grafos não ponderados/grafo_1000_1.txt",1,0,0,0);
    // grafo01->imprimir_grafo_lista_de_adjacencia();
    //grafo01->salva_grafo("saidas/saidas.txt");
    // cout << argv [0] << endl;
    // cout << argv [1] << endl;
    // cout << argv [2] << endl;
    // cout << argv [3] << endl;
    // cout << argv [4] << endl;
    // cout << argv [5] <<endl;
    string caminho = argv [1];
    cout << caminho << endl;
    Grafo* grafo01 = new Grafo(caminho,50000,0,0,0);
    
    grafo01->imprimir_grafo_lista_de_adjacencia();
    return 0;
}
