class Vertice
{
private:
    int id; //inteiro para identificar o vértice
    float peso; //peso do vertice
    bool foi_visitado; //boleano para identificar se o vertice foi visitado ou não

public:
    Vertice(int id);
    ~Vertice();

    //metodos padrões
    int get_id();
    float get_peso();
    bool get_foi_visitado();

    void set_id();
    void set_peso();
    void set_foi_visitado();

};
