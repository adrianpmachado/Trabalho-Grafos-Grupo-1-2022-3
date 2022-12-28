#include "Vertice.h"
#include "Grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

float calcula_peso(Grafo *grafo, vector<int> const &solucao)
{
  float peso = 0;
  for(auto vertice_id : solucao)
  {
    peso+= grafo->busca_vertice(vertice_id)->obter_peso();
  }
  return peso;
}

float calcula_qualidade(Vertice *vertice)
{
  if(vertice->obter_foi_visitado())
    return 0;

  int vertices_nao_cobertos = 0;
  for(auto vizinho : vertice->vertices_adjacentes)
  {
    if(!vizinho.second->obter_foi_coberto())
      vertices_nao_cobertos++;
  }

  if(!vertice->obter_foi_coberto())
    vertices_nao_cobertos++;

  return vertices_nao_cobertos / vertice->obter_peso();
}

int adiciona_solucao(vector<int> &solucao, Vertice *vertice)
{
  int vertices_cobertos = 0;
  solucao.push_back(vertice->obter_id());
  vertice->set_foi_visitado(true);

  if(!vertice->obter_foi_coberto())
    vertices_cobertos++;

  vertice->set_foi_coberto(true);

  for(auto vizinho : vertice->vertices_adjacentes)
  {
    if(!vizinho.second->obter_foi_coberto())
      vertices_cobertos++;
    vizinho.second->set_foi_coberto(true);
  }
  return vertices_cobertos;
}

vector<int> obter_solucao_inicial(map<int, Vertice *> candidatos, int &total_vertices_cobertos)
{
  total_vertices_cobertos = 0;
  vector<int> solucao;
  for(auto vertice : candidatos)
  {
    bool esta_na_solucao = false;
    esta_na_solucao |= vertice.second->obter_grau_entrada() == 0;
    esta_na_solucao |= vertice.second->obter_peso() <= 0;
    if(esta_na_solucao)
    {
      total_vertices_cobertos += adiciona_solucao(solucao, vertice.second);
    } else {
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
 
  int vertices_cobertos = 0;
  vector<int> solucao = obter_solucao_inicial(grafo->hash_vertices_grafo, vertices_cobertos);

  vector<Vertice *> lista_candidatos;
  for(auto vertice : grafo->hash_vertices_grafo)
  {
    if(!vertice.second->obter_foi_visitado())
    {
      lista_candidatos.push_back(vertice.second);
    }
  }

  while(vertices_cobertos < grafo->obter_ordem())
  {
    float melhor_qualidade = 0;
    Vertice *melhor_candidato = lista_candidatos.at(0);

    // obter melhor candidato
    for(int i = 1; i < lista_candidatos.size(); i++)
    {
      if(lista_candidatos.at(i)->obter_qualidade() > melhor_qualidade)
      {
        melhor_qualidade = lista_candidatos.at(i)->obter_qualidade();
        melhor_candidato = lista_candidatos.at(i);
      }
    }

    vertices_cobertos += adiciona_solucao(solucao, melhor_candidato);
    atualiza_candidatos(lista_candidatos);
  }

  cout << "Algoritmo guloso finalizado!" << endl;
  return solucao;
}

vector<int> guloso_randomizado(Grafo *grafo)
{
  int vertices_cobertos = 0;
  return obter_solucao_inicial(grafo->hash_vertices_grafo, vertices_cobertos);
}


vector<int> guloso_randomizado_reativo(Grafo *grafo)
{
  int vertices_cobertos = 0;
  return obter_solucao_inicial(grafo->hash_vertices_grafo, vertices_cobertos);
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