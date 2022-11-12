class Aresta
{
private:
    /* data */
    float peso;
    int id_aresta;
    int id_proxima_aresta;
public:
    Aresta(int id_aresta, int id_proxima_aresta,float peso);
    ~Aresta();

    //metodos padrões
    float get_peso();
    int get_id_aresta();
    int get_id_proxima_aresta();

    void set_peso();
    void set_id_aresta();
    void set_id_proxima_aresta();

};
