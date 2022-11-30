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
    this->vertices_adjacentes.push_back(id_destino);
}
void Vertice::adiciona_antecessor(int id_antecessor){
    this->vertices_antecessor.push_back(id_antecessor);
}
bool Vertice::existe_aresta(int id_destino){
    for(auto i:vertices_adjacentes){
        if(i == id_destino){
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
    for(auto i :vertices_adjacentes){
        cout << "[ " << i << " ] ";
    }
    cout<< "" << endl;
}

void Vertice::remove_adjacencia(int id){
    for(auto i = vertices_adjacentes.begin(); i != vertices_adjacentes.end(); i++){
        if(*i == id){
            vertices_adjacentes.erase(i);
            break;
        }
    }
}

void Vertice::remove_antecessor(int id){
    for(auto i = vertices_antecessor.begin(); i != vertices_antecessor.end(); i++){
        if(*i == id){
            vertices_antecessor.erase(i);
            break;
        }
    }
}