#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Grafo.h"

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

	string caminho;
	cin >> caminho;
	cout << endl;
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

void redePert()
{
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
	default:
		cout << "Opção inválida!" << endl;
		exit(1);
	}

	exit(0);
}

int menu()
{
	cout << "Escolha uma opção: " << endl
			 << endl;
	cout << "1 - Grafo interseção" << endl;
	cout << "2 - Grafo união" << endl;
	cout << "3 - Grafo diferença" << endl;
	cout << "4 - Rede pert" << endl;
	cout << "0 - Sair" << endl
			 << endl;

	int option;

	cin >> option;

	if (option == 0)
	{
		exit(0);
	}

	if (option > 4 || option < 0)
	{
		cout << "Opção inválida! Tente novamente" << endl;
		return menu();
	}

	return option;
}
