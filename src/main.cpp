#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"

using namespace std;


int main (int argc, char * argv[])
{
    Grafo* grafo01 = new Grafo("instancias Grafos não ponderados/grafo_1000_1.txt",1,0,0,0);
    grafo01->imprimir_grafo_lista_de_adjacencia();
    return 0;
}
