#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Grafo.h"
#include "math.h"
#include "rede-pert.h"

using namespace std;

Grafo *obter_novo_grafo(bool direcionado, bool peso_aresta, bool peso_vertice)
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
	Grafo *novoGrafo = new Grafo(caminho, direcionado, peso_aresta, peso_vertice, 1);
	return novoGrafo;
};

void grafo_intersecao(Grafo *grafo, string caminho_saida)
{
	Grafo *novo_grafo = obter_novo_grafo(grafo->obter_direcionado(), grafo->obter_peso_vertice(), grafo->obter_peso_aresta());

	cout << "Iniciando intersecao..." << endl;

	Grafo *intersecao = new Grafo(grafo->obter_direcionado(), grafo->obter_peso_vertice(), grafo->obter_peso_aresta());
	for (auto vertice : grafo->hash_vertices_grafo)
	{
		if (novo_grafo->busca_vertice(vertice.second->obter_id()) != NULL)
		{
			Vertice *vertice_inserido = intersecao->insere_vertice(vertice.second->obter_id());
			if (grafo->obter_peso_vertice())
			{
				vertice_inserido->set_peso(vertice.second->obter_peso());
			}
		}
	}
	for (auto aresta : grafo->arestas_grafo)
	{
		if (novo_grafo->existe_aresta(aresta->obter_id_saida(), aresta->obter_id_destino()))
		{
			Aresta *aresta_inserida = intersecao->insere_aresta(aresta->obter_id_saida(), aresta->obter_id_destino(), aresta->obter_peso());
			if (grafo->obter_peso_aresta())
			{
				aresta_inserida->set_peso(aresta->obter_peso());
			}
		}
	}

	cout << "Intersecao finalizada." << endl;
	cout << "Grafo resultado:" << endl;
	novo_grafo->imprimir_grafo_lista_de_adjacencia();
	cout << endl;
	grafo->salva_grafo(caminho_saida);

	return;
}

void grafo_uniao(Grafo *grafo, string caminho_saida)
{
	Grafo *novo_grafo = obter_novo_grafo(grafo->obter_direcionado(), grafo->obter_peso_aresta(), grafo->obter_peso_vertice());
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

void grafo_diferenca(Grafo *grafo, string caminho_saida)
{
	Grafo *novo_grafo = obter_novo_grafo(grafo->obter_direcionado(), grafo->obter_peso_aresta(), grafo->obter_peso_vertice());

	for (auto vertice_aux : novo_grafo->hash_vertices_grafo)
	{
		if (grafo->busca_vertice(vertice_aux.second->obter_id()) == NULL)
		{
			cout << "Os grafos precisam ter os mesmos vértices!" << endl;
			exit(1);
		}
	}

	cout << "Obtendo grafo diferenca..." << endl;

	for (auto aresta_aux : novo_grafo->arestas_grafo)
	{
		grafo->remove_aresta(aresta_aux->obter_id_saida(), aresta_aux->obter_id_destino());
	}

	cout << "Diferenca finalizada." << endl;
	cout << "\nGrafo resultado:\n";
	grafo->imprimir_grafo_lista_de_adjacencia();
	cout << endl;
	grafo->salva_grafo(caminho_saida);
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
		grafo_diferenca(grafo, caminho_saida);
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

	return;
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
		cout << "Encerrando programa...";
		exit(0);
	}
	if (option > 4 || option < 0 || (option == 4 && !eh_direcionado))
	{
		cout << "Opção inválida! Tente novamente" << endl;
		return menu(eh_direcionado);
	}
	return option;
}
