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

    //metodos padroẽs
    int getOrdem();
    bool get_ehDirecionado();
    bool get_peso_vertice();
    bool get_peso_aresta();

    //metodos auxiliares
    void insere_aresta();
    void insere_vertice();
    
};
