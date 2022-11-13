#include "Vertice.h"

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