#include "Grafo.h"
#include <list>
#include <fstream>

using namespace std;

Grafo::Grafo(string path_arquivo_entrada, bool direcionado, bool peso_vertice, bool peso_aresta)
{
    this->path_arquivo_entrada = path_arquivo_entrada;
    this->direcionado = direcionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;
    this->carrega_grafo();
};

Grafo::Grafo(bool direcionado, bool peso_vertice, bool peso_aresta)
{
    this->direcionado = direcionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;
};

bool Grafo::insere_vertice(int id)
{
    // verificar se o vertice já foi inserido
    if (busca_vertice(id) == NULL)
    {
        Vertice *vertice_aux = new Vertice(id);
        this->hash_vertices_grafo.insert(pair<int, Vertice *>(id, vertice_aux));
        return true;
    }
    else
    {
        return true;
    }
};
bool Grafo::remove_vertice(int id)
{
    for (auto it = this->hash_vertices_grafo.begin(); it != this->hash_vertices_grafo.end(); it++)
    {
        // renover a adjacencia de todos os vertices que apontam para esse
        it->second->remove_adjacencia(id);
        // remover a adjacencia de todos os vertices que esse aponta
        it->second->remove_antecessor(id);
    }
    // remover o vertice do hash
    if (busca_vertice(id) != NULL)
    {
        this->hash_vertices_grafo.erase(id);
        return true;
    }
    else
    {
        return false;
    }
}
Vertice *Grafo::busca_vertice(int id)
{
    if (this->hash_vertices_grafo.find(id) != hash_vertices_grafo.end())
    {
        return this->hash_vertices_grafo.at(id);
    }
    else
    {
        return NULL;
    }
};
void Grafo::insere_aresta(int id_saida, int id_destino, float peso)
{
    this->insere_vertice(id_saida);
    this->insere_vertice(id_destino);
    // criando um ponteiro para um vertice para podermos manipular o vertice de saida
    Vertice *vertice_aux_01 = this->busca_vertice(id_saida);
    // criand um ponteiro para um vettice para podermos manipular o vertice de entrada
    Vertice *vertice_aux_02 = this->busca_vertice(id_destino);
    if (vertice_aux_01 != nullptr && vertice_aux_02 != nullptr)
    {
        // verificar se existe algum vertice no grafo, se existir verificar e existe o de saida e o de destino em especifico
        if (this->direcionado)
        {
            // criando um vertice auxiliar para podemos depois salvar na lista de arestas do grafo
            Aresta *aresta_aux_01;
            // inserindo uma aresta não direcinonada no vertice
            aresta_aux_01 = vertice_aux_01->insere_aresta(id_saida, id_destino, peso);
            // adicionando +1 ao grau de saida já que é direcionado
            vertice_aux_01->set_grau_saida(vertice_aux_01->obter_grau_saida() + 1);
            // adicionando +1 ao grau entrada, já que é direcionado
            vertice_aux_02->set_grau_entrada(vertice_aux_02->obter_grau_entrada() + 1);
            // adicionando a aresta na lista de arestas do grafo
            this->arestas_grafo.push_back(aresta_aux_01);
        }
        else
        {
            // criando dois vertices auxiliares para podemos depois salvar na lista de arestas dos grafos
            Aresta *aresta_aux_01;
            Aresta *aresta_aux_02;
            // inserindo uma aresta não direcinonada nos vertices
            aresta_aux_01 = vertice_aux_01->insere_aresta(id_saida, id_destino, peso);
            aresta_aux_02 = vertice_aux_02->insere_aresta(id_destino, id_saida, peso);
            // adicionando +1 ao grau de saida e entrada, já que direcionado == 0
            vertice_aux_01->set_grau_saida(vertice_aux_01->obter_grau_saida() + 1);
            vertice_aux_01->set_grau_entrada(vertice_aux_01->obter_grau_entrada() + 1);
            // adicionando +1 ao grau de saida e entrada, já que não é direcionado
            vertice_aux_02->set_grau_saida(vertice_aux_02->obter_grau_saida() + 1);
            vertice_aux_02->set_grau_entrada(vertice_aux_02->obter_grau_entrada() + 1);
            // adicionando a aresta na lista de arestas do grafo
            this->arestas_grafo.push_back(aresta_aux_01);
        }
    }
}
bool Grafo::existe_Aresta(int id_saida, int id_destino)
{
    // verificar se a aresta está no vector de arestas
    for (Aresta *aresta_aux : arestas_grafo)
    {
        if ((aresta_aux->obter_id_saida() == id_saida) && (aresta_aux->obter_id_destino() == id_destino))
            return true;
    }
    return false;
}

void Grafo::imprimir_grafo_lista_de_adjacencia()
{
    // percorre os vertices
    for (auto vertice_aux : this->hash_vertices_grafo)
    {
        cout << "\n[" << vertice_aux.second->obter_id() << "]";
        // chama uma função auxiliar dentro da classe dos vertices para imprimir adjacencias
        vertice_aux.second->imprime_adjacencias();
    }
    cout << endl;
    // TODO: FALTA IMPRIMIR DIRECIONADOS
}
void Grafo::carrega_grafo()
{
    cout << "Lendo grafo em \"" + path_arquivo_entrada + "\"" << endl;
    // abrir o arquivo
    int ordem_grafo;
    int id_saida;
    int id_destino;
    int valor_peso;
    fstream arquivo_grafos;
    arquivo_grafos.open(path_arquivo_entrada, ios::in);
    if (arquivo_grafos.is_open())
    {
        arquivo_grafos >> ordem_grafo;
        if ((!direcionado) && (!peso_vertice) && (!peso_aresta))
        {
            while (arquivo_grafos >> id_saida >> id_destino)
            {
                this->insere_aresta(id_saida, id_destino, 0);
            }
        }
        else if ((!direcionado) && (peso_vertice) && (!peso_aresta))
        {
            while (arquivo_grafos >> id_saida >> id_destino >> valor_peso)
            {
                this->insere_aresta(id_saida, id_destino, valor_peso);
            }
        }
        else if ((!direcionado) && (!peso_vertice) && (peso_aresta))
        {
            while (arquivo_grafos >> id_saida >> id_destino >> valor_peso)
            {
                this->insere_aresta(id_saida, id_destino, valor_peso);
            }
        }
        else if ((direcionado) && (!peso_vertice) && (!peso_aresta))
        {
            while (arquivo_grafos >> id_saida >> id_destino)
            {
                this->insere_aresta(id_saida, id_destino, 0);
            }
        }
        else if ((direcionado) && (peso_vertice) && (!peso_aresta))
        {
            while (arquivo_grafos >> id_saida >> id_destino >> valor_peso)
            {
                this->insere_aresta(id_saida, id_destino, valor_peso);
            }
        }
        else if ((direcionado) && (!peso_vertice) && (peso_aresta))
        {
            while (arquivo_grafos >> id_saida >> id_destino >> valor_peso)
            {
                this->insere_aresta(id_saida, id_destino, valor_peso);
            }
        }
    }
    else
    {
        cout << "não foi possivel abrir o arquivo " << endl;
    }
}
void Grafo::salva_grafo(string path_arquivo_saida)
{
    cout << "Salvando grafo em \"" + path_arquivo_saida + "\"" << endl;
    fstream arquivo_graphviz;
    arquivo_graphviz.open(path_arquivo_saida, ios::out);

    if (!arquivo_graphviz.is_open())
    {
        cout << "Erro abrindo arquivo de escrita!" << endl;
        exit(1);
    }

    string conector;
    if (direcionado)
    {
        arquivo_graphviz << "digraph grafo {" << endl;
        conector = "->";
    }
    else
    {
        arquivo_graphviz << "graph grafo {" << endl;
        conector = "--";
    }

    for (auto aresta_aux : arestas_grafo)
    {
        arquivo_graphviz << aresta_aux->obter_id_saida() << conector << aresta_aux->obter_id_destino();
        if (peso_aresta)
        {
            arquivo_graphviz << " [label=" << aresta_aux->obter_peso() << "]";
        }
        arquivo_graphviz << ";" << endl;
    }
    arquivo_graphviz << "}";
}
bool Grafo::obter_direcionado()
{
    return direcionado;
}
bool Grafo::obter_peso_aresta()
{
    return peso_aresta;
}

bool Grafo::obter_peso_vertice()
{
    return peso_vertice;
}

Grafo *Grafo::clonar()
{
    Grafo *grafo_aux = new Grafo(this->direcionado, this->peso_aresta, this->peso_vertice);
    for (auto vertice_aux : this->hash_vertices_grafo)
    {
        grafo_aux->insere_vertice(vertice_aux.second->obter_id());
    }
    for (auto aresta_aux : this->arestas_grafo)
    {
        grafo_aux->insere_aresta(aresta_aux->obter_id_saida(), aresta_aux->obter_id_destino(), aresta_aux->obter_peso());
    }
    return grafo_aux;
}
