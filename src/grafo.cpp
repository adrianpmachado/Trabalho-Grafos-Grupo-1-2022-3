#include "Grafo.h"

using namespace std;

Grafo::Grafo(int ordem, bool ehDirecionado = false, bool peso_vertice = false, bool peso_aresta = false){
    this->ordem = ordem;
    this->ehDirecionado = ehDirecionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;
};


//inserindo vertice
void Grafo::insere_vertice(int id){
    if(existe_vertice(id)){
        cout  << "O vertice de id " << id << " já foi inserido no grafo" << endl;
    }
    else {
        Vertice* vertice_aux = new Vertice(id);
        vertices_grafo.push_back(vertice_aux);
    }
};

bool Grafo::existe_vertice(int id){
    //percorer todos os vertices para ver se ja foi inserido
    for(Vertice* vertice_aux :vertices_grafo){
        if(vertice_aux->get_id() == id){
            return true; //encontrou com o mesmo id, retorna true
        } 
    }
    return false; // não encotrou, retorna falso
};

Vertice* Grafo::busca_vertice(int id){
    for(Vertice* vertice_aux :vertices_grafo){
        if(vertice_aux->get_id() == id){
            return vertice_aux; //encontrou com o mesmo id, retorna o ponteiro
        } 
    }
    return nullptr; // não encotrou
}

//inserindo Aresta 
void Grafo::insere_aresta(int id_saida,int id_destino, bool direcionado, float peso){
    if(!vertices_grafo.empty() && existe_vertice(id_saida) && existe_vertice(id_destino)){
        //verificar se existe algum vertice no grafo, se existir verificar e existe o de saida e o de destino em especifico
        if(direcionado){
            
            
        }
        else{

        }
    }
}
bool Grafo::existe_Aresta(int id_saida, int id_destino, bool direcionado, float peso){
    
}