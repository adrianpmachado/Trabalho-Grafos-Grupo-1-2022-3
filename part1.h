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

	if (peso_vertice)
	{
		mensagem += " não";
	}

	mensagem += " ponderado em vértices e";

	if (peso_aresta)
	{
		mensagem += " não";
	}

	mensagem += " ponderado em arestas: ";

	cout << mensagem << endl;

	string caminho;
	cin >> caminho;
	Grafo *novoGrafo = new Grafo(caminho, direcionado, peso_vertice, peso_aresta());

	return novoGrafo;
};

void grafoIntersecao(Grafo *grafo)
{
	Grafo *novo_grafo = obter_novo_grafo(grafo->obter_direcionado(), grafo->obter_peso_vertice(), grafo->obter_peso_aresta());

	Vertice *vertice_aux = novo_grafo->obter_primeiro_vertice()

														 return;
}

void grafo_uniao(Grafo *grafo)
{
	Grafo *novo_grafo = obter_novo_grafo(grafo->obter_direcionado(), grafo->obter_peso_vertice(), grafo->obter_peso_aresta());

	// unir grafo com novo grafo

	return;
}

void grafoDiferenca()
{
	return;
}

void redePert()
{
	return;
}

void escolheOperacao(int option, Grafo *grafo)
{
	switch (option)
	{
	case 1:
		grafoIntersecao(grafo);
		break;
	case 2:
		grafoUniao(grafo);
		break;
	case 3:
		grafoDiferenca();
		break;
	default:
		cout << "Opção inválida! Tente novamente" << endl;
		break;
	}
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
