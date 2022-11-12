#include "Vertice.h"

using namespace std;

Vertice::Vertice(int id){
    this->id = id;
}

int Vertice::get_id(){
    return this->id;
}

float Vertice::get_peso(){
    return this->peso;
}

bool Vertice::get_foi_visitado(){
    return this->foi_visitado;
}