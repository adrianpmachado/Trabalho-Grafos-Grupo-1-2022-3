#include "Grafo.h"
#include <list>
#include <fstream>

using namespace std;

Grafo::Grafo(string path_arquivo_entrada, bool ehDirecionado, bool peso_vertice, bool peso_aresta){
    this->path_arquivo_entrada = path_arquivo_entrada;
    this->ehDirecionado = ehDirecionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;
    this->carrega_grafo();
};

bool Grafo::insere_vertice(int id){
    //verificar se o vertice já foi inserido
    if(busca_vertice(id) == NULL){
        Vertice* vertice_aux = new Vertice(id);
        this->hash_vertices_grafo.insert(pair<int,Vertice*>(id,vertice_aux));
        return true;
    }
    else {
        return true;
    }
};
bool Grafo::remove_vertice(int id){
    for(auto it = this->hash_vertices_grafo.begin(); it != this->hash_vertices_grafo.end(); it++){
        //renover a adjacencia de todos os vertices que apontam para esse
        it->second->remove_adjacencia(id);
        //remover a adjacencia de todos os vertices que esse aponta
        it->second->remove_antecessor(id);
        
    }
    //remover o vertice do hash
    if(busca_vertice(id) != NULL){
        this->hash_vertices_grafo.erase(id);
        return true;
    }
    else {
        return false;
    }
}
Vertice* Grafo::busca_vertice(int id){
    if(this->hash_vertices_grafo.find(id) != hash_vertices_grafo.end()){
        return this->hash_vertices_grafo.at(id);
    }
    else{
        return NULL;
    }
};
void Grafo::insere_aresta(int id_saida,int id_destino, float peso){
    this->insere_vertice(id_saida);
    this->insere_vertice(id_destino);
     //criando um ponteiro para um vertice para podermos manipular o vertice de saida
    Vertice* vertice_aux_01 = this->busca_vertice(id_saida);
    //criand um ponteiro para um vettice para podermos manipular o vertice de entrada
    Vertice* vertice_aux_02 = this->busca_vertice(id_destino);
    if(vertice_aux_01 != nullptr && vertice_aux_02 != nullptr){
        //verificar se existe algum vertice no grafo, se existir verificar e existe o de saida e o de destino em especifico
        if(this->ehDirecionado){
            //criando um vertice auxiliar para podemos depois salvar na lista de arestas do grafo
            Aresta* aresta_aux_01;
            //inserindo uma aresta não direcinonada no vertice
            aresta_aux_01 = vertice_aux_01->insere_aresta(id_saida,id_destino,peso);
            //adicionando +1 ao grau de saida já que é direcionado
            vertice_aux_01->set_grau_saida(vertice_aux_01->get_grau_saida()+1);
            //adicionando +1 ao grau entrada, já que é direcionado
            vertice_aux_02->set_grau_entrada(vertice_aux_02->get_grau_entrada()+1);
            //adicionando a aresta na lista de arestas do grafo
            this->arestas_grafo.push_back(aresta_aux_01);  
        }
        else{
            //criando dois vertices auxiliares para podemos depois salvar na lista de arestas dos grafos
            Aresta* aresta_aux_01;
            Aresta* aresta_aux_02;
            //inserindo uma aresta não direcinonada nos vertices
            aresta_aux_01 = vertice_aux_01->insere_aresta(id_saida,id_destino,peso);
            aresta_aux_02 = vertice_aux_02->insere_aresta(id_destino,id_saida,peso);
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
bool Grafo::existe_Aresta(int id_saida, int id_destino, float peso){
    //verificar se a aresta está no vector de arestas
    for(Aresta* aresta_aux :arestas_grafo){
        if((aresta_aux->get_id_saida()==id_saida)&&(aresta_aux->get_id_destino()==id_destino))
            return true;
    }
    return false;
}

void Grafo::imprimir_grafo_lista_de_adjacencia(){
    //percorre os vertices 
    for(auto vertice_aux : this->hash_vertices_grafo){
        cout << "Vertice: " << vertice_aux.second->get_id() << endl;
        //chama uma função auxiliar dentro da classe dos vertices para imprimir adjacencias
        vertice_aux.second->imprime_adjacencias();
    }
    //TODO: FALTA IMPRIMIR DIRECIONADOS 
}
void Grafo::carrega_grafo(){
    //abrir o arquivo
    int ordem_grafo;
    int id_saida;
    int id_destino;
    int valor_peso;
    fstream arquivo_grafos;
    arquivo_grafos.open(path_arquivo_entrada,ios::in);
    if(arquivo_grafos.is_open()){
        arquivo_grafos >> ordem_grafo;
        if((!ehDirecionado)&&(!peso_vertice)&&(!peso_aresta)){
            while(arquivo_grafos>>id_saida>>id_destino){
                this->insere_aresta(id_saida,id_destino,0);
            }
        }
        else if((!ehDirecionado)&&(peso_vertice)&&(!peso_aresta)){
            while(arquivo_grafos>>id_saida>>id_destino>>valor_peso){
                this->insere_aresta(id_saida,id_destino,valor_peso);
            }
        }
        else if((!ehDirecionado)&&(!peso_vertice)&&(peso_aresta)){
            while(arquivo_grafos>>id_saida>>id_destino>>valor_peso){
                this->insere_aresta(id_saida,id_destino,valor_peso);
            }
        }
        else if((ehDirecionado)&&(!peso_vertice)&&(!peso_aresta)){
            while(arquivo_grafos>>id_saida>>id_destino){
                this->insere_aresta(id_saida,id_destino,0);
            }
        }
        else if((ehDirecionado)&&(peso_vertice)&&(!peso_aresta)){
            while(arquivo_grafos>>id_saida>>id_destino>>valor_peso){
                this->insere_aresta(id_saida,id_destino,valor_peso);
            }
        }
        else if((ehDirecionado)&&(!peso_vertice)&&(peso_aresta)){
            while(arquivo_grafos>>id_saida>>id_destino>>valor_peso){
                this->insere_aresta(id_saida,id_destino,valor_peso);
            }
        }
    }
    else{
            cout << "não foi possivel abrir o arquivo " << endl;
        }
}
void Grafo::salva_grafo(string path_arquivo_saida) {
    fstream arquivo_graphviz;
    arquivo_graphviz.open(path_arquivo_saida,ios::out);
    if(arquivo_graphviz.is_open()){
        arquivo_graphviz << "graph grafo {" << endl;
        if(ehDirecionado){
            for(auto aresta_aux : arestas_grafo){
                arquivo_graphviz << aresta_aux->get_id_saida() << "->" << aresta_aux->get_id_destino()<< endl;
            }
        }
        else {
            for(auto aresta_aux : arestas_grafo){
                arquivo_graphviz << aresta_aux->get_id_saida() << "--" << aresta_aux->get_id_destino()<< endl;
            }
        }
        arquivo_graphviz << "}";
    }
    else{
        cout << "arquivo de escrita não foi aberto" << endl;
    }
    //TODO: FALTA SALVAR GRAFO DIRECIONADO
}