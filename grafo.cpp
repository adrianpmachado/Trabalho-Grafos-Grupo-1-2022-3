#include "Grafo.h"
#include <list>
#include <fstream>
#include <limits>

using namespace std;

Grafo::Grafo(string path_arquivo_entrada, bool direcionado, bool peso_aresta, bool peso_vertice, int parte_trabalho)
{
    this->path_arquivo_entrada = path_arquivo_entrada;
    this->direcionado = direcionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;

    if (parte_trabalho == 1)
    {
        this->carrega_grafo_1();
    }
    else if (parte_trabalho == 2)
    {
        this->carrega_grafo_2();
    }
};

Grafo::Grafo(bool direcionado, bool peso_aresta, bool peso_vertice)
{
    this->direcionado = direcionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;
};

Vertice *Grafo::insere_vertice(int id)
{
    Vertice *vertice_aux;
    // verificar se o vertice já foi inserido
    if (busca_vertice(id) == NULL)
    {
        vertice_aux = new Vertice(id);
        this->hash_vertices_grafo.insert(pair<int, Vertice *>(id, vertice_aux));
    }
    else
    {
        vertice_aux = busca_vertice(id);
    }
    return vertice_aux;
};
bool Grafo::remove_vertice(int id)
{
    for (auto it = this->hash_vertices_grafo.begin(); it != this->hash_vertices_grafo.end(); it++)
    {
        it->second->remove_adjacencia(id);
        it->second->remove_antecessor(id);
    }
    for (int i = this->arestas_grafo.size() - 1; i >= 0; i--)
    {
        if (arestas_grafo.at(i)->obter_id_destino() || arestas_grafo.at(i)->obter_id_saida())
        {
            this->arestas_grafo.erase(arestas_grafo.begin() + i);
        }
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
Aresta *Grafo::insere_aresta(int id_saida, int id_destino, float peso)
{
    this->insere_vertice(id_saida);
    this->insere_vertice(id_destino);
    // criando um ponteiro para um vertice para podermos manipular o vertice de saida
    Vertice *vertice_aux_01 = this->busca_vertice(id_saida);
    // criand um ponteiro para um vettice para podermos manipular o vertice de entrada
    Vertice *vertice_aux_02 = this->busca_vertice(id_destino);

    if (vertice_aux_01 != nullptr && vertice_aux_02 != nullptr)
    {
        Aresta *nova_aresta = new Aresta(id_saida, id_destino, this->direcionado, peso);
        vertice_aux_01->adiciona_adjacencia(vertice_aux_02);
        vertice_aux_02->adiciona_antecessor(vertice_aux_01);
        if (!this->direcionado)
        {
            vertice_aux_01->adiciona_antecessor(vertice_aux_02);
            vertice_aux_02->adiciona_adjacencia(vertice_aux_01);
        }
        this->arestas_grafo.push_back(nova_aresta);
        return nova_aresta;
    }
}
bool Grafo::existe_aresta(int id_saida, int id_destino)
{
    // verificar se a aresta está no vector de arestas
    for (Aresta *aresta_aux : arestas_grafo)
    {
        if ((aresta_aux->obter_id_saida() == id_saida) && (aresta_aux->obter_id_destino() == id_destino))
            return true;
    }
    return false;
}
Aresta *Grafo::obter_aresta(int id_saida, int id_destino)
{
    for (Aresta *aresta_aux : arestas_grafo)
    {
        if ((aresta_aux->obter_id_saida() == id_saida) && (aresta_aux->obter_id_destino() == id_destino))
            return aresta_aux;
    }
    return NULL;
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
void Grafo::carrega_grafo_1()
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

    for (auto vertice_aux : hash_vertices_grafo)
    {
        arquivo_graphviz << vertice_aux.second->obter_id();
        if (peso_vertice)
        {
            arquivo_graphviz << " [weight=" << vertice_aux.second->obter_peso() << "]";
        }
        if (vertice_aux.second->obter_foi_visitado())
        {
            arquivo_graphviz << " [color=red]";
        }
        else if (vertice_aux.second->obter_foi_coberto())
        {
            arquivo_graphviz << " [color=purple]";
        }
        else
        {
            arquivo_graphviz << " [color=black]";
        }
        arquivo_graphviz << ";" << endl;
    }

    for (auto aresta_aux : arestas_grafo)
    {
        arquivo_graphviz << aresta_aux->obter_id_saida() << conector << aresta_aux->obter_id_destino();
        if (peso_aresta)
        {
            arquivo_graphviz << " [weight=" << aresta_aux->obter_peso() << "]";
        }
        arquivo_graphviz << ";" << endl;
    }
    arquivo_graphviz << "}";
    arquivo_graphviz.close();
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

int Grafo::obter_ordem()
{
    return this->hash_vertices_grafo.size();
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

void Grafo::carrega_grafo_2()
{
    int ordem_grafo;
    fstream arquivo_grafos;
    string me_ignore;

    cout << "Lendo grafo em \"" + path_arquivo_entrada + "\"..." << endl;
    arquivo_grafos.open(path_arquivo_entrada, ios::in);
    if (!arquivo_grafos.is_open())
    {
        cout << "não foi possivel abrir o arquivo " << endl;
        return;
    }

    arquivo_grafos >> me_ignore;
    arquivo_grafos >> ordem_grafo;

    // pular linhas de posições
    arquivo_grafos.seekg(ios::beg);
    for (int i = 0; i < ordem_grafo + 4; ++i)
    {
        arquivo_grafos.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Vertice *vertice_aux;
    for (int id_vertice = 1; id_vertice <= ordem_grafo; id_vertice++)
    {
        float peso_vertice = 0;
        arquivo_grafos >> peso_vertice;
        vertice_aux = this->insere_vertice(id_vertice);
        vertice_aux->set_peso(peso_vertice);
    }

    arquivo_grafos >> me_ignore;

    for (int id_saida = 1; id_saida <= ordem_grafo; id_saida++)
    {
        for (int id_destino = 1; id_destino <= ordem_grafo; id_destino++)
        {
            bool aresta_existe = false;
            arquivo_grafos >> aresta_existe;
            if (aresta_existe && id_destino > id_saida)
            {
                this->insere_aresta(id_saida, id_destino, 0);
            }
        }
    }

    arquivo_grafos.close();
    return;
}

bool Grafo::remove_aresta(int id_saida, int id_destino)
{
    for (int i = arestas_grafo.size() - 1; i >= 0; i--)
    {
        Aresta *aresta_aux = arestas_grafo.at(i);
        if (aresta_aux->obter_id_saida() == id_saida && aresta_aux->obter_id_destino() == id_destino)
        {
            arestas_grafo.erase(arestas_grafo.begin() + i);
            delete aresta_aux;
        }
        else if (!direcionado && aresta_aux->obter_id_saida() == id_destino && aresta_aux->obter_id_destino() == id_saida)
        {
            arestas_grafo.erase(arestas_grafo.begin() + i);
            delete aresta_aux;
        }
    }

    busca_vertice(id_saida)->remove_adjacencia(id_destino);
    busca_vertice(id_destino)->remove_antecessor(id_saida);

    if (!direcionado)
    {
        busca_vertice(id_destino)->remove_adjacencia(id_saida);
        busca_vertice(id_saida)->remove_antecessor(id_destino);
    }

    return true;
}
