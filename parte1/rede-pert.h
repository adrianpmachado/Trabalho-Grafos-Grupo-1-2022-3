#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../Grafo.h"
#include "math.h"

bool estao_na_solucao(map<int, Vertice *> vertices)
{
  for (auto vertice_aux : vertices)
  {
    if (!vertice_aux.second->obter_foi_visitado())
      return false;
  }

  return true;
}

Vertice *max_custo_minimo(std::map<int, int> custos, map<int, Vertice *> vertices)
{
  int max = -1;
  Vertice *vertice_max = NULL;
  for (auto vertice_aux : vertices)
  {
    cout << "vertice: " << custos.at(vertice_aux.second->obter_id()) << endl;
    if (custos.at(vertice_aux.second->obter_id()) > max)
    {
      cout << "custo: " << custos.at(vertice_aux.second->obter_id()) << endl;
      max = custos[vertice_aux.second->obter_id()];
      vertice_max = vertice_aux.second;
    }
  }
  return vertice_max;
}

void rede_pert(Grafo *grafo)
{
  vector<int> solucao;
  std::map<int, int> custo_minimo;

  // obter o vértice de entrada e saída
  Vertice *vertice_entrada = NULL;
  Vertice *vertice_saida = NULL;
  int contador_entrada = 0;
  int contador_saida = 0;

  cout << "Obtendo vertice de saida e de entrada..." << endl;
  for (auto vertice_aux : grafo->hash_vertices_grafo)
  {

    if (vertice_aux.second->obter_grau_entrada() == 0 && vertice_aux.second->obter_grau_saida() > 0)
    {
      vertice_entrada = vertice_aux.second;
      contador_entrada++;
    }
    else if (vertice_aux.second->obter_grau_entrada() > 0 && vertice_aux.second->obter_grau_saida() == 0)
    {
      vertice_saida = vertice_aux.second;
      contador_saida++;
    }
  }

  if (vertice_entrada == NULL || vertice_saida == NULL || contador_entrada > 1 || contador_saida > 1)
  {
    cout << "Grafo não é uma rede PERT!" << endl;
    exit(1);
  }

  cout << "Vertices encontrados" << endl;
  cout << "Vertice de entrada: " << vertice_entrada->obter_id() << endl;
  cout << "Vertice de saida: " << vertice_saida->obter_id() << endl;

  solucao.push_back(vertice_entrada->obter_id());
  vertice_entrada->set_foi_visitado(true);
  custo_minimo[vertice_entrada->obter_id()] = 0;

  cout << "Encontrando solucao..." << endl;

  while (solucao.size() < grafo->obter_ordem())
  {
    cout << "solucao.size(): " << solucao.size() << endl;
    for (auto vertice_aux : grafo->hash_vertices_grafo)
    {
      if (estao_na_solucao(vertice_aux.second->vertices_antecessor) && !vertice_aux.second->obter_foi_visitado())
      {
        int custo = 0;
        Vertice *vertice_max = max_custo_minimo(custo_minimo, vertice_aux.second->vertices_antecessor);
        Aresta *aresta = grafo->obter_aresta(vertice_max->obter_id(), vertice_aux.second->obter_id());
        custo += custo_minimo.at(vertice_max->obter_id());
        custo += aresta->obter_peso();
        custo_minimo.insert(pair<int, int>(vertice_aux.second->obter_id(), custo));

        solucao.push_back(vertice_aux.second->obter_id());
        vertice_aux.second->set_foi_visitado(true);
      }
    }
  }
  cout << "Solucao encontrada" << endl;

  string separador(50, '-');
  cout << separador << endl;
  cout << "Ordem de execução das atividades: \n";
  for (auto vertice_aux : solucao)
  {
    cout << vertice_aux << endl;
  }
  cout << separador << endl;
  cout << "Custo mínimo: " << custo_minimo[vertice_saida->obter_id()] << endl;
  cout << separador << endl;
  return;
}