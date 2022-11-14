#include "Grafo.h"
#include <list>

using namespace std;

Grafo::Grafo(int ordem, bool ehDirecionado, bool peso_vertice, bool peso_aresta){
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
            //continuar
                       
        }
        else{
            //criando um ponteiro para um vertice para podermos manipular o vertice de saida
            Vertice* vertice_aux_01 = this->busca_vertice(id_saida);
            //criand um ponteiro para um vettice para podermos manipular o vertice de entrada
            Vertice* vertice_aux_02 = this->busca_vertice(id_destino);
            //criando um vertice auxiliar para podemos depois salvar na lista de arestas do grafo
            Aresta* aresta_aux_01;
            //inserindo uma aresta não direcinonada no vertice
            aresta_aux_01 = vertice_aux_01->insere_aresta_nao_direcionada(id_saida,id_destino,peso);
            //adicionando +1 ao grau de saida e entrada, já que direcionado == 0
            vertice_aux_01->set_grau_saida(vertice_aux_01->get_grau_saida()+1);
            vertice_aux_01->set_grau_entrada(vertice_aux_01->get_grau_entrada()+1);
            //adicionando +1 ao grau de saida e entrada, já que não é direcionado
            vertice_aux_02->set_grau_saida(vertice_aux_02->get_grau_saida()+1);
            vertice_aux_02->set_grau_entrada(vertice_aux_02->get_grau_entrada()+1);
            //adicionando a aresta na lista de arestas do grafo
            this->arestas_grafo.push_back(aresta_aux_01);
        }
    }
}
bool Grafo::existe_Aresta(int id_saida, int id_destino, bool direcionado, float peso){
    if(direcionado){
        //continuar
        return false;
    }
    else{
        for(Aresta* aresta_aux :arestas_grafo){
            if((aresta_aux->get_id_saida()==id_saida)&&(aresta_aux->get_id_destino()==id_destino))
                return true;
        }
        return false;
    }
}