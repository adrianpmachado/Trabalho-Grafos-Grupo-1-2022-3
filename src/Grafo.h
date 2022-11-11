class Grafo
{
private:
    /* data */
    int ordem; //ordem do grafo 
    bool ehDirecionado; //boleano para identificar se o grafo é direciondo ou não
    bool peso_vertice; //se tem peso nos vertices 
    bool peso_aresta; //se tem peso nas arestas
public:
    Grafo(int ordem, bool ehDirecionado = false, bool peso_vertice = false, );
    ~Grafo();
};
