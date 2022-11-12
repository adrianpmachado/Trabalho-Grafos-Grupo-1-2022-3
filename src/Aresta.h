class Aresta
{
private:
    /* data */
    float peso;
    int id_saida;
    int id_destino;
    float peso;
public:
    Aresta(int id_saida, int id_destino, bool direcionado, float peso);
    ~Aresta();

    //metodos padrões
    float get_peso();
    int get_id_saida();
    int get_id_destino();

    void set_peso();
    void set_id_aresta();
    void set_id_proxima_aresta();

};
