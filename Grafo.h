#pragma once
#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "Aresta.h"
#include "Vertice.h"

using namespace std;

class Grafo
{
private:
    /* data */
    int ordem;         // ordem do grafo
    bool direcionado;  // boleano para identificar se o grafo é direciondo ou não
    bool peso_vertice; // se tem peso nos vertices
    bool peso_aresta;  // se tem peso nas arestas
    string path_arquivo_entrada;

public:
    // iniciando o construtor com alguns valores já predefinidos
    Grafo(string path_arquivo_entrada, bool ehDirecionado, bool peso_aresta, bool peso_vertice, int parte_trabalho);
    Grafo(bool direcionado, bool peso_aresta, bool peso_vertice);
    ~Grafo();
    vector<Aresta *> arestas_grafo;
    map<int, Vertice *> hash_vertices_grafo;

    int obter_ordem(); // funcionando
    Vertice *obter_primeiro_vertice();
    Vertice *obter_ultimo_vertice();
    Vertice* insere_vertice(int id); // funcionando
    bool remove_vertice(int id);
    Vertice *busca_vertice(int id); // funcionando
    int obter_indice_vertice(int id);
    void insere_aresta(int id_saida, int id_destino, float peso);
    bool existe_Aresta(int id_saida, int id_destino);
    Aresta *obter_aresta(int id_saida, int id_destino);
    void imprimir_grafo_lista_de_adjacencia();
    void carrega_grafo_1();
    void carrega_grafo_2();
    void salva_grafo(string path_arquivo_saida);
    bool obter_direcionado();
    bool obter_peso_vertice();
    bool obter_peso_aresta();
    Grafo *clonar();
};

#endif // GRAFO_H_INCLUDED