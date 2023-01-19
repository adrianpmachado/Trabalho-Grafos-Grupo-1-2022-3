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
    xrandomize(time(NULL));
    string caminho_entrada = argv[1];
    string caminho_saida = argv[2];
    int algoritmo;
    std::istringstream(argv[3]) >> algoritmo;
    Grafo *grafo_inicial = new Grafo(caminho_entrada, false, false, true, 2);

    vector<int> solucao;
    switch (algoritmo)
    {
    case 1:
        solucao = subconjunto_dominante_ponderado(GULOSO, grafo_inicial);
        break;
    case 2:
        solucao = subconjunto_dominante_ponderado(GULOSO_RANDOMIZADO, grafo_inicial, 0.15, 500);
        break;
    case 3:
        solucao = subconjunto_dominante_ponderado(GULOSO_RANDOMIZADO, grafo_inicial, 0.30, 500);
        break;
    case 4:
        solucao = subconjunto_dominante_ponderado(GULOSO_RANDOMIZADO, grafo_inicial, 0.50, 500);
        break;
    case 5:
        solucao = subconjunto_dominante_ponderado(GULOSO_RANDOMIZADO_REATIVO, grafo_inicial, 0, 2500, 250, {0.05, 0.10, 0.15, 0.30, 0.50});
        break;
    default:
        break;
    }

    return 0;
}
