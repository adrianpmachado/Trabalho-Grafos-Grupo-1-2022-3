#include "Aresta.h"

using namespace std;

Aresta::Aresta(int id_saida, int id_destino, bool eh_direcionado, float peso){
    this->id_saida = id_saida;
    this->id_destino = id_destino;
    this->eh_direcionado = eh_direcionado;
    this->peso = peso;
}

float Aresta::get_peso(){
    return this->peso;
}
int Aresta::get_id_saida(){
    return this->id_saida;
}
int Aresta::get_id_destino(){
    return this->id_destino;
}
float Aresta::get_peso(){
    return this->peso;
}
bool Aresta::get_eh_direcionado(){
    return this->eh_direcionado;
}

void Aresta::set_peso(float peso){
    this->peso=peso;
}
void Aresta::set_id_saida(int id_saida){
    this->id_saida = id_saida;
}
void Aresta::set_id_destino(int id_destino){
    this->id_destino = id_destino;
}
void Aresta::set_eh_direcionado(bool eh_direcionado){
    this->eh_direcionado = eh_direcionado;
}