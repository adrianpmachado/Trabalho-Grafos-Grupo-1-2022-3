#include "Vertice.h"
#include "Grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "random.h"
#include <time.h>

using namespace std;

enum Algoritmo
{
  GULOSO,
  GULOSO_RANDOMIZADO,
  GULOSO_RANDOMIZADO_REATIVO
};

float normalizar_alfa(float alfa)
{
  if (alfa < 0)
    return 0;
  if (alfa > 1)
    return 1;
  return alfa;
}

void reincia_vertices(map<int, Vertice *> const &vertices)
{
  for (auto vertice_aux : vertices)
  {
    vertice_aux.second->reiniciar();
  }
}

void atualiza_probabilidades(vector<float> &probabilidades, vector<float> const &media_solucoes, float peso_melhor_solucao)
{
  vector<float> aux;
  float total_aux = 0;
  for (int i = 0; i < probabilidades.size(); i++)
  {
    float calc = peso_melhor_solucao / media_solucoes.at(i);
    aux.push_back(calc);
    total_aux += calc;
  }
  for (int i = 0; i < probabilidades.size(); i++)
  {
    probabilidades.at(i) = aux.at(i) / total_aux;
  }
}

void atualiza_medias(vector<float> &media_solucoes, int indice_alfa, float peso_solucao)
{
  float media_antiga = media_solucoes.at(indice_alfa);
  float nova_media;
  if (media_antiga == 0)
    nova_media = peso_solucao;
  else
    nova_media = (media_antiga + peso_solucao) / 2;
  media_solucoes.at(indice_alfa) = nova_media;
}

int escolhe_alfa(vector<float> const &probabilidades)
{
  float prob = xrandom(10001) / 10000.0;
  float soma = 0;
  for (int i = 0; i < probabilidades.size(); i++)
  {
    soma += probabilidades.at(i);
    if (soma >= prob)
      return i;
  }
  return probabilidades.size() - 1;
}

float calcula_peso(Grafo *grafo, vector<int> const &solucao)
{
  float peso = 0;
  for (auto vertice_id : solucao)
  {
    peso += grafo->busca_vertice(vertice_id)->obter_peso();
  }
  return peso;
}

float calcula_qualidade(Vertice *vertice)
{
  if (vertice->obter_foi_visitado())
    return 0;

  int vertices_nao_cobertos = 0;
  for (auto vizinho : vertice->vertices_adjacentes)
  {
    if (!vizinho.second->obter_foi_coberto())
      vertices_nao_cobertos++;
  }

  if (!vertice->obter_foi_coberto())
    vertices_nao_cobertos++;

  return vertices_nao_cobertos / vertice->obter_peso();
}

int adiciona_solucao(vector<int> &solucao, Vertice *vertice)
{
  int vertices_cobertos = 0;
  solucao.push_back(vertice->obter_id());
  vertice->set_foi_visitado(true);

  if (!vertice->obter_foi_coberto())
    vertices_cobertos++;

  vertice->set_foi_coberto(true);

  for (auto vizinho : vertice->vertices_adjacentes)
  {
    if (!vizinho.second->obter_foi_coberto())
      vertices_cobertos++;
    vizinho.second->set_foi_coberto(true);
  }
  return vertices_cobertos;
}

vector<int> obter_solucao_inicial(map<int, Vertice *> candidatos, int &total_vertices_cobertos)
{
  total_vertices_cobertos = 0;
  vector<int> solucao;
  for (auto vertice : candidatos)
  {
    bool esta_na_solucao = false;
    esta_na_solucao |= vertice.second->obter_grau_entrada() == 0;
    esta_na_solucao |= vertice.second->obter_peso() <= 0;
    if (esta_na_solucao)
    {
      total_vertices_cobertos += adiciona_solucao(solucao, vertice.second);
    }
    else
    {
      vertice.second->set_qualidade(calcula_qualidade(vertice.second));
    }
  }
  return solucao;
}

void atualiza_candidatos(vector<Vertice *> &candidatos)
{
  auto it = candidatos.begin();
  while (it != candidatos.end())
  {
    Vertice *vertice_aux = *it;
    if (vertice_aux->obter_foi_visitado())
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

Vertice *guloso(vector<Vertice *> &candidatos)
{
  Vertice *melhor_candidato = candidatos.at(0);
  float melhor_qualidade = melhor_candidato->obter_qualidade();

  // obter melhor candidato
  for (int i = 1; i < candidatos.size(); i++)
  {
    if (candidatos.at(i)->obter_qualidade() > melhor_qualidade)
    {
      melhor_qualidade = candidatos.at(i)->obter_qualidade();
      melhor_candidato = candidatos.at(i);
    }
  }

  return melhor_candidato;
}

Vertice *guloso_randomizado(vector<Vertice *> &candidatos, const float alfa)
{
  sort(candidatos.begin(), candidatos.end(), ordena_candidatos);
  int indice_candidato = xrandom(alfa * candidatos.size());
  return candidatos.at(indice_candidato);
}

/**
 * @brief Função que realiza a busca local de um subconjunto dominante
 * @param algoritmo Algoritmo de busca local, sendo:
 * - GULOSO
 * - GULOSO_RANDOMIZADO
 * - GULOSO_RANDOMIZADO_REATIVO
 * @param grafo Grafo a ser analisado
 * @param alfa Parâmetro alfa para o algoritmo guloso randomizado (ignorado para os outros algoritmos)
 * @param num_iteracoes Número de iterações para o algoritmo guloso randomizado e randomizado reativo (ignorado para o algoritmo guloso)
 * @param bloco Tamanho do bloco para o algoritmo guloso randomizado reativo (ignorado para os outros algoritmos)
 * @param lista_alfas Lista de alfas para o algoritmo guloso randomizado reativo (ignorado para os outros algoritmos)
 * @return Vetor com os vértices do subconjunto dominante
 */
vector<int> subconjunto_dominante_ponderado(Algoritmo algoritmo, Grafo *grafo, float alfa = 0, int num_iteracoes = 1, int bloco = 1, vector<float> lista_alfas = {0})
{
  clock_t tInicio, tFim, tDecorrido;
  tInicio = clock();
  vector<float> alfas_probabilidades;
  vector<float> alfas_solucoes;

  num_iteracoes = num_iteracoes <= 0 ? 1 : num_iteracoes;
  switch (algoritmo)
  {
  case GULOSO_RANDOMIZADO:
    alfa = normalizar_alfa(alfa);
    cout << "Iniciando algoritmo guloso randomizado..." << endl;
    break;
  case GULOSO_RANDOMIZADO_REATIVO:
    if (lista_alfas.size() == 0)
      lista_alfas.push_back(0);
    for (int i = 0; i < lista_alfas.size(); i++)
    {
      alfas_solucoes.push_back(0);
      alfas_probabilidades.push_back(1.0 / lista_alfas.size());
      lista_alfas.at(i) = normalizar_alfa(lista_alfas.at(i));
    }
    cout << "Iniciando algoritmo guloso randomizado reativo..." << endl;
    break;
  default:
    cout << "Iniciando algoritmo guloso..." << endl;
  }

  float peso_melhor_solucao = 0;
  vector<int> melhor_solucao;
  for (int iteracao = 0; iteracao < num_iteracoes; iteracao++)
  {
    reincia_vertices(grafo->hash_vertices_grafo);
    int vertices_cobertos = 0;
    vector<int> solucao = obter_solucao_inicial(grafo->hash_vertices_grafo, vertices_cobertos);

    vector<Vertice *> lista_candidatos;
    for (auto vertice : grafo->hash_vertices_grafo)
    {
      if (!vertice.second->obter_foi_visitado())
      {
        lista_candidatos.push_back(vertice.second);
      }
    }

    int indice_alfa = iteracao;
    if (algoritmo == GULOSO_RANDOMIZADO_REATIVO)
    {
      if (iteracao >= lista_alfas.size())
      {
        if (iteracao % bloco == 0)
        {
          cout << "Iteracao " << iteracao << " - Atualizando probabilidades..." << endl;
          atualiza_probabilidades(alfas_probabilidades, alfas_solucoes, peso_melhor_solucao);
        }
        indice_alfa = escolhe_alfa(alfas_probabilidades);
      }
      alfa = lista_alfas.at(indice_alfa);
    }

    while (vertices_cobertos < grafo->obter_ordem())
    {
      Vertice *vertice_aux;

      switch (algoritmo)
      {
      case GULOSO_RANDOMIZADO:
        vertice_aux = guloso_randomizado(lista_candidatos, alfa);
        break;
      case GULOSO_RANDOMIZADO_REATIVO:
        vertice_aux = guloso_randomizado(lista_candidatos, alfa);
        break;
      default:
        vertice_aux = guloso(lista_candidatos);
      }

      vertices_cobertos += adiciona_solucao(solucao, vertice_aux);
      atualiza_candidatos(lista_candidatos);
    }

    if (algoritmo == GULOSO)
    {
      melhor_solucao = solucao;
      break;
    }

    float peso_solucao = calcula_peso(grafo, solucao);
    if (iteracao == 0 || peso_solucao < peso_melhor_solucao)
    {
      peso_melhor_solucao = peso_solucao;
      melhor_solucao = solucao;
      cout << "Melhor solucao encontrada: " << peso_melhor_solucao << endl;
    }

    if (algoritmo == GULOSO_RANDOMIZADO_REATIVO)
    {
      atualiza_medias(alfas_solucoes, indice_alfa, peso_solucao);
    }
  }

  tFim = clock();
  tDecorrido = ((tFim - tInicio) * 1000) / CLOCKS_PER_SEC;

  cout << "Algoritmo finalizado!\n"
       << endl;
  cout << "Tempo decorrido: " << tDecorrido << " ms" << endl;

  return melhor_solucao;
}
