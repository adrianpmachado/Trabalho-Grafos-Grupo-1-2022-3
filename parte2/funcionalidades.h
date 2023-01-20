#include "../Vertice.h"
#include "../Grafo.h"
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

void atualiza_probabilidades(vector<double> &probabilidades, vector<pair<int, double>> const &media_solucoes, double peso_melhor_solucao)
{
  vector<double> aux;
  double total_aux = 0;
  for (int i = 0; i < probabilidades.size(); i++)
  {
    double calc = peso_melhor_solucao / media_solucoes.at(i).second;
    aux.push_back(calc);
    total_aux += calc;
  }
  for (int i = 0; i < probabilidades.size(); i++)
  {
    probabilidades.at(i) = aux.at(i) / total_aux;
  }
}

void atualiza_medias(vector<pair<int, double>> &media_solucoes, int indice_alfa, double peso_solucao)
{
  int num_solucoes = media_solucoes.at(indice_alfa).first;
  double media_antiga = media_solucoes.at(indice_alfa).second;

  double nova_media;
  if (num_solucoes == 0)
    nova_media = peso_solucao;
  else
    nova_media = (media_antiga * num_solucoes + peso_solucao) / (num_solucoes + 1);

  media_solucoes.at(indice_alfa).second = nova_media;
  media_solucoes.at(indice_alfa).first++;
}

int escolhe_alfa(vector<double> const &probabilidades)
{
  double prob = xrandom(10001) / 10000.0;
  double soma = 0;
  for (int i = 0; i < probabilidades.size(); i++)
  {
    soma += probabilidades.at(i);
    if (soma >= prob)
      return i;
  }
  return probabilidades.size() - 1;
}

double calcula_peso(Grafo *grafo, vector<int> const &solucao)
{
  double peso = 0.0;
  for (auto vertice_id : solucao)
  {
    peso += grafo->busca_vertice(vertice_id)->obter_peso();
  }
  return peso;
}

double calcula_qualidade(Vertice *vertice)
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
  solucao.push_back(vertice->obter_id());
  vertice->set_foi_visitado(true);
  vertice->set_foi_coberto(true);

  for (auto vizinho : vertice->vertices_adjacentes)
  {
    vizinho.second->set_foi_coberto(true);
  }
}

vector<int> obter_solucao_inicial(map<int, Vertice *> candidatos)
{
  vector<int> solucao;
  for (auto vertice : candidatos)
  {
    if (vertice.second->obter_grau_entrada() == 0 || vertice.second->obter_peso() <= 0)
    {
      adiciona_solucao(solucao, vertice.second);
    }
  }
  return solucao;
}

void remove_candidato(vector<Vertice *> &candidatos, Vertice *vertice)
{
  candidatos.erase(remove(candidatos.begin(), candidatos.end(), vertice), candidatos.end());
}

void atualiza_candidatos(vector<Vertice *> &candidatos)
{
  for (auto vertice : candidatos)
  {
    vertice->set_qualidade(calcula_qualidade(vertice));
  }
}

bool ordena_candidatos(Vertice *vertice1, Vertice *vertice2)
{
  return vertice1->obter_qualidade() > vertice2->obter_qualidade();
}

Vertice *escolhe_vertice(vector<Vertice *> &candidatos, const float alfa)
{
  sort(candidatos.begin(), candidatos.end(), ordena_candidatos);
  int indice_candidato = xrandom(alfa * candidatos.size());
  return candidatos.at(indice_candidato);
}

bool solucao_encontrada(vector<Vertice *> &candidatos)
{
  for (auto vertice : candidatos)
  {
    if (!vertice->obter_foi_coberto())
    {
      return false;
    }
  }
  return true;
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
  vector<double> alfas_probabilidades;
  vector<pair<int, double>> alfas_solucoes;

  num_iteracoes = num_iteracoes <= 0 ? 1 : num_iteracoes;
  switch (algoritmo)
  {
  case GULOSO_RANDOMIZADO:
    alfa = normalizar_alfa(alfa);
    cout << "Iniciando algoritmo guloso randomizado..." << endl;
    break;
  case GULOSO_RANDOMIZADO_REATIVO:
    if (lista_alfas.size() == 0)
    {
      lista_alfas.push_back(0);
    }

    for (int i = 0; i < lista_alfas.size(); i++)
    {
      alfas_solucoes.push_back(make_pair(0, 0.0));
      alfas_probabilidades.push_back(1.0 / lista_alfas.size());
      lista_alfas.at(i) = normalizar_alfa(lista_alfas.at(i));
    }

    cout << "Iniciando algoritmo guloso randomizado reativo..." << endl;
    break;
  default:
    alfa = 0;
    cout << "Iniciando algoritmo guloso..." << endl;
  }

  double peso_melhor_solucao = 0;
  float alfa_melhor_solucao = 0;
  vector<int> melhor_solucao;
  for (int iteracao = 0; iteracao < num_iteracoes; iteracao++)
  {
    reincia_vertices(grafo->hash_vertices_grafo);

    vector<int> solucao = obter_solucao_inicial(grafo->hash_vertices_grafo);

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
          atualiza_probabilidades(alfas_probabilidades, alfas_solucoes, peso_melhor_solucao);
        }
        indice_alfa = escolhe_alfa(alfas_probabilidades);
      }
      alfa = lista_alfas.at(indice_alfa);
    }

    while (!solucao_encontrada(lista_candidatos))
    {
      Vertice *vertice_aux = escolhe_vertice(lista_candidatos, alfa);
      adiciona_solucao(solucao, vertice_aux);
      remove_candidato(lista_candidatos, vertice_aux);
      atualiza_candidatos(lista_candidatos);
    }

    double peso_solucao = calcula_peso(grafo, solucao);
    if (algoritmo == GULOSO)
    {
      melhor_solucao = solucao;
      peso_melhor_solucao = peso_solucao;
      break;
    }

    if (iteracao == 0 || peso_solucao < peso_melhor_solucao)
    {
      peso_melhor_solucao = peso_solucao;
      melhor_solucao = solucao;
      alfa_melhor_solucao = alfa;
    }

    if (algoritmo == GULOSO_RANDOMIZADO_REATIVO)
    {
      atualiza_medias(alfas_solucoes, indice_alfa, peso_solucao);
    }
  }

  tFim = clock();
  tDecorrido = ((tFim - tInicio) * 1000) / CLOCKS_PER_SEC;

  cout << "Tempo decorrido: " << (double)tDecorrido << " ms" << endl;
  cout << "Alfa: " << alfa_melhor_solucao << endl;
  cout << "Peso solucao: " << peso_melhor_solucao << endl;
  cout << "Solucao: ";
  for (int i = 0; i < melhor_solucao.size(); i++)
  {
    cout << melhor_solucao.at(i) << " ";
  }
  cout << endl;

  return melhor_solucao;
}
