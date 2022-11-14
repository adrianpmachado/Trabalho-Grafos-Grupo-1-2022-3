#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"

using namespace std;


int main (int argc, char * argv[])
{
    Grafo* grafo01 = new Grafo(1,0,0,0);
    grafo01->insere_vertice(01);
    grafo01->insere_vertice(02);
    grafo01->insere_vertice(02);
    grafo01->insere_vertice(03);
    grafo01->insere_vertice(04);
    grafo01->insere_vertice(05);
    grafo01->insere_vertice(06);

    grafo01->insere_aresta(1,2,0,0);
    grafo01->insere_aresta(1,5,0,0);
    grafo01->insere_aresta(2,5,0,0);
    grafo01->insere_aresta(1,2,0,0);
    grafo01->insere_aresta(2,3,0,0);
    grafo01->insere_aresta(3,4,0,0);
    grafo01->insere_aresta(4,5,0,0);
    grafo01->insere_aresta(4,6,0,0);

    grafo01->imprimir_grafo_lista_de_adjacencia();
    return 0;
}
