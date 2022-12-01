#include <iostream>
#include <list>
#include "Vertice.h"
#include "Aresta.h"

using namespace std;

Vertice::Vertice(int id){
    this->id = id;
}

int Vertice::get_id(){return this->id;}

float Vertice::get_peso(){return this->peso;}

bool Vertice::get_foi_visitado(){return this->foi_visitado;}

int Vertice::get_grau_entrada(){return this->grau_entrada;}

int Vertice::get_grau_saida(){return grau_saida;}

void Vertice::set_id(int id){
    this->id = id;
}
void Vertice::set_peso(float peso){
    this->peso = peso;
}
void Vertice::set_foi_visitado(bool foi_visitado){
    this->foi_visitado = foi_visitado;
}
void Vertice::set_grau_entrada(int grau_entrada){
    this->grau_entrada = grau_entrada;
}
void Vertice::set_grau_saida(int grau_saida){
    this->grau_saida = grau_saida;
}
void Vertice::adiciona_adjacencia(int id_destino){
    this->vertices_adjacentes[id_destino] = new Vertice(id_destino);
    this->grau_saida++;
}
void Vertice::adiciona_antecessor(int id_antecessor){
    this->vertices_antecessor[id_antecessor] = new Vertice(id_antecessor);
    this->grau_entrada++;
}
bool Vertice::existe_aresta(int id_destino){
    for(auto it = this->vertices_adjacentes.begin(); it != this->vertices_adjacentes.end(); it++){
        if(it->second->get_id() == id_destino){
            return true;
        }
    }
    return false;
}
Aresta* Vertice::insere_aresta(int id_saida,int id_destino,float peso){
    Aresta* aresta_aux = new Aresta(id_saida,id_destino,false,peso);
    adiciona_adjacencia(id_destino);
    return aresta_aux;
}

void Vertice::imprime_adjacencias(){
    for(auto it = this->vertices_adjacentes.begin(); it != this->vertices_adjacentes.end(); it++){
        cout << " [" <<it->second->get_id() << "]";
    }
}

void Vertice::remove_adjacencia(int id){
    for(auto it = this->vertices_adjacentes.begin(); it != this->vertices_adjacentes.end(); it++){
        if(it->second->get_id() == id){
            this->vertices_adjacentes.erase(it);
            this->grau_saida--;
            break;
        }
    }
}

void Vertice::remove_antecessor(int id){
    for(auto it = this->vertices_antecessor.begin(); it != this->vertices_antecessor.end(); it++){
        if(it->second->get_id() == id){
            this->vertices_antecessor.erase(it);
            this->grau_entrada--;
            break;
        }
    }
}