#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Grafo.h"
#include "math.h"

using namespace std;

Grafo *obter_novo_grafo(bool direcionado, bool peso_vertice, bool peso_aresta)
{
	string mensagem = "Insira um caminho para um grafo ";
	if (!direcionado)
	{
		mensagem += "não ";
	}
	mensagem += "direcionado,";
	if (!peso_vertice)
	{
		mensagem += " não";
	}
	mensagem += " ponderado em vértices e";
	if (!peso_aresta)
	{
		mensagem += " não";
	}
	mensagem += " ponderado em arestas: ";

	cout << mensagem << endl;
	cout << endl;
	string caminho;
	cin >> caminho;
	Grafo *novoGrafo = new Grafo(caminho, direcionado, peso_vertice, peso_aresta);
	return novoGrafo;
};

void grafo_intersecao(Grafo *grafo, string caminho_saida)
{
	grafo->salva_grafo(caminho_saida);

	return;
}

void grafo_uniao(Grafo *grafo, string caminho_saida)
{
	Grafo *novo_grafo = obter_novo_grafo(grafo->obter_direcionado(), grafo->obter_peso_vertice(), grafo->obter_peso_aresta());
	cout << "Unindo os grafos..." << endl;
	for (auto aresta_aux : novo_grafo->arestas_grafo)
	{
		grafo->insere_aresta(aresta_aux->obter_id_saida(), aresta_aux->obter_id_destino(), aresta_aux->obter_peso());
	}
	for (auto vertice_aux : novo_grafo->hash_vertices_grafo)
	{
		if (vertice_aux.second->obter_grau_entrada() == 0 && vertice_aux.second->obter_grau_saida() == 0)
		{
			grafo->insere_vertice(vertice_aux.second->obter_id());
		}
	}
	cout << "União finalizada." << endl;
	cout << "\nGrafo resultado:\n";
	grafo->imprimir_grafo_lista_de_adjacencia();
	cout << endl;
	grafo->salva_grafo(caminho_saida);
	return;
}

void grafo_diferenca()
{
	return;
}

void rede_pert(Grafo *grafo)
{
	vector<int> solucao;
	map<int, int> custo_minimo;

	// obter o vértice de entrada e saída
	Vertice *vertice_entrada = NULL;
	Vertice *vertice_saida = NULL;

	for (auto vertice_aux : grafo->hash_vertices_grafo)
	{
		if (vertice_aux.second->obter_grau_entrada() == 0 && vertice_aux.second->obter_grau_saida() > 0)
		{
			vertice_entrada = vertice_aux.second;
		}
		else if (vertice_aux.second->obter_grau_entrada() > 0 && vertice_aux.second->obter_grau_saida() == 0)
		{
			vertice_saida = vertice_aux.second;
		}
		if (vertice_entrada != NULL && vertice_saida != NULL)
		{
			break;
		}
	}

	if (vertice_entrada == NULL || vertice_saida == NULL)
	{
		cout << "Grafo não é uma rede PERT!" << endl;
		exit(1);
	}

	bool estao_na_solucao(map<int, Vertice *> vertices)
	{
		for (auto vertice_aux : vertices)
		{
			if (find(solucao.begin(), solucao.end(), vertice_aux.second->obter_id()) == solucao.end())
			{
				return false;
			}
		}
		return true;
	}

	Vertice *max_custo_minimo(map<int, Vertice *> vertices)
	{
		int max = 0;
		Vertice *vertice_max = NULL;
		for (auto vertice_aux : vertices)
		{
			if (custo_minimo[vertice_aux.second->obter_id()] > max)
			{
				max = custo_minimo[vertice_aux.second->obter_id()];
				vertice_max = vertice_aux.second;
			}
		}
		return vertice_max;
	}

	solucao.push_back(vertice_entrada->obter_id());
	custo_minimo[vertice_entrada->obter_id()] = 0;

	for (auto vertice_aux : grafo->hash_vertices_grafo)
	{
		if (!estao_na_solucao(vertice_aux.second->vertices_antecessor))
		{
			continue;
		}

		Vertice *vertice_max = max_custo_minimo(vertice_aux.second->vertices_antecessor);
		custo_minimo[vertice_aux.second->obter_id()] = custo_minimo[vertice_max->obter_id()];
		Aresta *aresta = grafo->obter_aresta(vertice_max->obter_id(), vertice_aux.second->obter_id());
		custo_minimo[vertice_aux.second->obter_id()] += aresta->obter_peso();

		solucao.push_back(vertice_aux.second->obter_id());
	}

	return;
}

void realiza_operacao(int option, Grafo *grafo, string caminho_saida)
{
	switch (option)
	{
	case 1:
		grafo_intersecao(grafo, caminho_saida);
		break;
	case 2:
		grafo_uniao(grafo, caminho_saida);
		break;
	case 3:
		grafo_diferenca();
		break;
	case 4:
		if (grafo->obter_direcionado())
		{
			rede_pert(grafo);
			break;
		}
	default:
		cout << "Opção inválida!" << endl;
		exit(1);
	}

	exit(0);
}

int menu(bool eh_direcionado)
{
	int option;
	cout << "Escolha uma opção: \n\n";
	cout << "1 - Grafo interseção\n";
	cout << "2 - Grafo união\n";
	cout << "3 - Grafo diferença\n";
	if (eh_direcionado)
	{
		cout << "4 - Rede pert\n";
	}
	cout << "0 - Sair\n\n";

	cin >> option;
	option = ceil(option);
	if (option == 0)
	{
		exit(0);
	}
	if (option > 3 || option < 0 || (option == 4 && !eh_direcionado))
	{
		cout << "Opção inválida! Tente novamente" << endl;
		return menu(eh_direcionado);
	}
	return option;
}
