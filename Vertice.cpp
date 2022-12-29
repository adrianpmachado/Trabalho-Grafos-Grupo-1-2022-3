#include <iostream>
#include <list>
#include "Vertice.h"
#include "Aresta.h"

using namespace std;

Vertice::Vertice(int id)
{
    this->id = id;
}

int Vertice::obter_id() { return this->id; }

float Vertice::obter_peso() { return this->peso; }

bool Vertice::obter_foi_visitado() { return this->foi_visitado; }

int Vertice::obter_grau_entrada() { return this->grau_entrada; }

int Vertice::obter_grau_saida() { return grau_saida; }

void Vertice::set_id(int id)
{
    this->id = id;
}
void Vertice::set_peso(float peso)
{
    this->peso = peso;
}
void Vertice::set_foi_visitado(bool foi_visitado)
{
    this->foi_visitado = foi_visitado;
}
void Vertice::set_grau_entrada(int grau_entrada)
{
    this->grau_entrada = grau_entrada;
}
void Vertice::set_grau_saida(int grau_saida)
{
    this->grau_saida = grau_saida;
}
void Vertice::adiciona_adjacencia(Vertice *adjacente)
{
    this->vertices_adjacentes[adjacente->obter_id()] = adjacente;
    this->grau_saida++;
}
void Vertice::adiciona_antecessor(Vertice *antecessor)
{
    this->vertices_antecessor[antecessor->obter_id()] = antecessor;
    this->grau_entrada++;
}
bool Vertice::existe_aresta(int id_destino)
{
    for (auto it = this->vertices_adjacentes.begin(); it != this->vertices_adjacentes.end(); it++)
    {
        if (it->second->obter_id() == id_destino)
        {
            return true;
        }
    }
    return false;
}

void Vertice::imprime_adjacencias()
{
    for (auto it : vertices_adjacentes)
    {
        cout << " -> [" << it.second->obter_id() << "]";
    }
}

void Vertice::remove_adjacencia(int id)
{
    for (auto it = this->vertices_adjacentes.begin(); it != this->vertices_adjacentes.end(); it++)
    {
        if (it->second->obter_id() == id)
        {
            this->vertices_adjacentes.erase(it);
            this->grau_saida--;
            break;
        }
    }
}

void Vertice::remove_antecessor(int id)
{
    for (auto it = this->vertices_antecessor.begin(); it != this->vertices_antecessor.end(); it++)
    {
        if (it->second->obter_id() == id)
        {
            this->vertices_antecessor.erase(it);
            this->grau_entrada--;
            break;
        }
    }
}

void Vertice::set_qualidade(float qualidade)
{
    this->qualidade = qualidade;
}

float Vertice::obter_qualidade()
{
    return this->qualidade;
}   

void Vertice::set_foi_coberto(bool foi_coberto)
{
    this->foi_coberto = foi_coberto;
}

bool Vertice::obter_foi_coberto()
{
    return this->foi_coberto;
}

void Vertice::reiniciar()
{
    this->foi_visitado = false;
    this->foi_coberto = false;
    this->qualidade = 0;
}