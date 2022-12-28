#include "Vertice.h"
#include "Grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

float calcula_qualidade(Vertice *vertice)
{
  return vertice->obter_grau_entrada() / vertice->obter_peso();
}

vector<int> obter_solucao_inicial(map<int, Vertice *> candidatos)
{
  vector<int> solucao;
  for(auto vertice : candidatos)
  {
    bool esta_na_solucao = false;
    esta_na_solucao |= vertice.second->obter_grau_entrada() == 0;
    esta_na_solucao |= vertice.second->obter_peso() <= 0;
    if(esta_na_solucao)
    {
      solucao.push_back(vertice.second->obter_id());
      vertice.second->set_foi_visitado(true);
    } else {
      vertice.second->set_foi_visitado(false);
      vertice.second->set_qualidade(calcula_qualidade(vertice.second));
    }
  }
  return solucao;
}

void atualiza_candidatos(vector<Vertice *> &candidatos)
{
  auto it = candidatos.begin();
  while(it != candidatos.end())
  {
    Vertice *vertice_aux = *it;
    if(vertice_aux->obter_foi_visitado())
    {
      it = candidatos.erase(it);
      continue;
    }

    bool vizinho_na_solucao = false;
    for(auto vizinho : vertice_aux->vertices_adjacentes)
    {
      vizinho_na_solucao |= vizinho.second->obter_foi_visitado();
      if(vizinho_na_solucao)
      {
        break;
      }
    }

    if(vizinho_na_solucao)
    {
      it = candidatos.erase(it);
      continue;
    }
    vertice_aux->set_qualidade(calcula_qualidade(vertice_aux));
    it++;
  }
}

bool ordena_candidatos(Vertice *vertice1, Vertice *vertice2)
{
  return vertice1->obter_qualidade() > vertice2->obter_qualidade();
}

vector<int> guloso(Grafo *grafo)
{
  cout << "Executando o algoritmo guloso..." << endl;
  vector<int> solucao = obter_solucao_inicial(grafo->hash_vertices_grafo);

  vector<Vertice *> lista_candidatos;
  for(auto vertice : grafo->hash_vertices_grafo)
  {
    if(!vertice.second->obter_foi_visitado())
    {
      lista_candidatos.push_back(vertice.second);
    }
  }

  while(lista_candidatos.size() > 0)
  {
    sort(lista_candidatos.begin(), lista_candidatos.end(), ordena_candidatos);
    solucao.push_back(lista_candidatos.at(0)->obter_id());
    lista_candidatos.at(0)->set_foi_visitado(true);
    atualiza_candidatos(lista_candidatos);
  }

  cout << "Algoritmo guloso finalizado!" << endl;
  return solucao;
}

vector<int> guloso_randomizado(Grafo *grafo)
{
  return obter_solucao_inicial(grafo->hash_vertices_grafo);
}


vector<int> guloso_randomizado_reativo(Grafo *grafo)
{
  return obter_solucao_inicial(grafo->hash_vertices_grafo);
}


vector<int> subconjunto_dominante_ponderado(int algoritmo, Grafo *grafo)
{
  switch(algoritmo) 
  {
    case 1:
      return guloso(grafo);
    case 2:
      return guloso_randomizado(grafo);
    case 3:
      return guloso_randomizado_reativo(grafo);
    default:
      return guloso(grafo);
  }
}