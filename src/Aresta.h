class Aresta
{
private:
    /* data */
    float peso;
    int id_saida;
    int id_destino;
    bool eh_direcionado;
public:
    Aresta(int id_saida, int id_destino, bool eh_direcionado, float peso);
    ~Aresta();

    //metodos padrões
    float get_peso();
    int get_id_saida();
    int get_id_destino();
    bool get_eh_direcionado();

    void set_peso(float peso);
    void set_id_saida(int id_saida);
    void set_id_destino(int id_destino);
    void set_eh_direcionado(bool eh_direcionado);

};
