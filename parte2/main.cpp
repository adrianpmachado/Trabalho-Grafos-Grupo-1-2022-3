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
    istringstream(argv[3]) >> algoritmo;
    bool verificar_solucao;
    istringstream(argv[4]) >> verificar_solucao;

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

    if (verificar_solucao)
    {
        reincia_vertices(grafo_inicial->hash_vertices_grafo);

        for (auto vertice : solucao)
        {
            grafo_inicial->busca_vertice(vertice)->set_foi_visitado(true);
        }

        double peso_solucao = 0;
        vector<int> vertices_nao_cobertos;
        cout << "\n[Vertice (Peso)]: [Vizinhos na solucao]" << endl;
        for (auto vertice : grafo_inicial->hash_vertices_grafo)
        {
            cout << "[" << vertice.second->obter_id() << " (" << vertice.second->obter_peso() << ")"
                 << "]: [ ";
            if (vertice.second->obter_foi_visitado())
            {
                peso_solucao += vertice.second->obter_peso();
                cout << "Vertice na solucao ]" << endl;
                continue;
            }

            bool coberto = false;
            for (auto vizinho : vertice.second->vertices_adjacentes)
            {
                if (vizinho.second->obter_foi_visitado())
                {
                    coberto = true;
                    cout << vizinho.second->obter_id() << " ";
                }
            }

            if (!coberto)
            {
                vertices_nao_cobertos.push_back(vertice.second->obter_id());
                cout << "Erro: Nao coberto ";
            }
            else
            {
                vertice.second->set_foi_coberto(true);
            }
            cout << "]" << endl;
        }

        cout << "\nPeso da solucao: " << peso_solucao << endl;
        if (!vertices_nao_cobertos.empty())
        {
            cout << "Erro: A solucao eh inviavel" << endl;
            cout << "Vertices nao cobertos: ";
            for (auto vertice : vertices_nao_cobertos)
            {
                cout << vertice << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "Sucesso: A solucao eh viavel" << endl;
        }
        cout << endl;
    }

    grafo_inicial->salva_grafo(caminho_saida);

    return 0;
}
