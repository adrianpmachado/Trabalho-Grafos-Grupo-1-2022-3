#pragma once
#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include "Aresta.h"
#include <list>
#include <map>

using namespace std;

class Vertice
{
private:
    int id;                    // inteiro para identificar o vértice
    float peso = 0;            // peso do vertice
    bool foi_visitado = false; // boleano para identificar se o vertice foi visitado ou não
    bool foi_coberto = false;  // boleano para identificar se o vertice foi coberto ou não
    int grau_entrada = 0;
    int grau_saida = 0;
    double qualidade = 0;

public:
    Vertice(int id);
    ~Vertice();

    // metodos para manutenção dos Vertices e Arestas
    void adiciona_adjacencia(Vertice *adjacente);
    void adiciona_antecessor(Vertice *sucessor);
    void remove_adjacencia(int id);
    void remove_antecessor(int id);
    bool existe_aresta(int id_destino);
    Aresta *insere_aresta(int id_saida, int id_destino, float peso);

    // lista de vertices que se conectam a esse
    map<int, Vertice *> vertices_antecessor; // Lista de predecessores
    map<int, Vertice *> vertices_adjacentes; // lista de adjacencia de vertice

    // metodos padrões
    int obter_id();
    float obter_peso();
    bool obter_foi_visitado();
    int obter_grau_entrada();
    int obter_grau_saida();
    bool obter_foi_coberto();
    double obter_qualidade();

    void set_id(int id);
    void set_peso(float peso);
    void set_foi_visitado(bool foi_visitado);
    void set_foi_coberto(bool foi_coberto);
    void set_grau_entrada(int grau_entrada);
    void set_grau_saida(int grau_saida);
    void set_qualidade(double qualidade);
    void imprime_adjacencias();
    void reiniciar();
};
#endif // VERTICE_H_INCLUDED