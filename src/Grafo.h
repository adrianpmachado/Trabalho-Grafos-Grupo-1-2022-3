#include <iostream>
#include <vector>

#include "Aresta.h"
#include "Vertice.h"

using namespace std;

class Grafo
{
private:
    /* data */
    int ordem; //ordem do grafo 
    bool ehDirecionado; //boleano para identificar se o grafo é direciondo ou não
    bool peso_vertice; //se tem peso nos vertices 
    bool peso_aresta; //se tem peso nas arestas
public:
    //iniciando o construtor com alguns valores já predefinidos
    Grafo(int ordem, bool ehDirecionado = false, bool peso_vertice = false, bool peso_aresta = false);
    ~Grafo();

    vector<Aresta*> arestas_grafo;
    vector<Vertice*> vertices_grafo;

    //metodos padroẽs
    int getOrdem();
    bool get_ehDirecionado();
    bool get_peso_vertice();
    bool get_peso_aresta();

    //metodos auxiliares
    void insere_vertice(int id);
    bool existe_vertice(int id);

    void insere_aresta(int id_saida,int id_destino, bool direcionado, float peso);
    bool existe_Aresta(int id_saida, int id_destino, bool direcionado, float peso);
};
