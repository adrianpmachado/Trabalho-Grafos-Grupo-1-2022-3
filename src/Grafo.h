#pragma once
#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <vector>
#include <list>

#include "Aresta.h"
#include "Vertice.h"

using namespace std;

class Grafo
{
private:
    /* data */
    int ordem; //ordem do grafo 
    bool ehDirecionado; //boleano para identificar se o grafo é direciondo ou não
    bool peso_vertice; //se tem peso nos vertices 
    bool peso_aresta; //se tem peso nas arestas
public:
    //iniciando o construtor com alguns valores já predefinidos
    Grafo(int ordem, bool ehDirecionado, bool peso_vertice, bool peso_aresta);
    ~Grafo();

    vector<Aresta*> arestas_grafo;
    vector<Vertice*> vertices_grafo;

    Vertice* get_primeiro_vertice();
    Vertice* get_ultimo_vertice();
    void insere_vertice(int id); //funcionando
    void remove_vertice(int id);
    bool existe_vertice(int id); //funcionando
    Vertice* busca_vertice(int id); //funcionando
    void insere_aresta(int id_saida,int id_destino, bool direcionado, float peso); //funcionando apenas para grafos não direcionados
    bool existe_Aresta(int id_saida, int id_destino, bool direcionado, float peso); //funcionando apenas para grafos não direcionados
    void imprimir_grafo_lista_de_adjacencia();
    void carrega_grafo(string arquivo_entrada);

};

#endif //GRAFO_H_INCLUDED