#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"
#include <sstream>
#include "funcionalidades.h"
#include "random.h"

using namespace std;

int main(int argc, char *argv[])
{
    string caminho_entrada = argv[1];
    string caminho_saida = argv[2];
    Grafo *grafo_inicial = new Grafo(caminho_entrada, false, false, true, 2);

    grafo_inicial->salva_grafo(caminho_saida);

    vector<int> solucao = subconjunto_dominante_ponderado(GULOSO_RANDOMIZADO_REATIVO, grafo_inicial, 0, 2500, 250, {0.05, 0.10, 0.15, 0.30, 0.50} );

    cout << "\nO conjunto de vertices dominantes eh: \n";
    for(auto vertice : solucao) {
        cout << vertice << endl;
    }

    cout << "\nO peso do conjunto eh: " << calcula_peso(grafo_inicial, solucao) << endl;

    return 0;
}
