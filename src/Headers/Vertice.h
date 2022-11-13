#include <list>

class Vertice
{
private:
    int id; //inteiro para identificar o vértice
    float peso = 0; //peso do vertice
    bool foi_visitado = false; //boleano para identificar se o vertice foi visitado ou não
    int grau_entrada = 0;
    int grau_saida = 0;

public:
    Vertice(int id);
    ~Vertice();
    
    //lista de vertices que se conectam a esse 
    list<int> vertices_anteriores; // Lista de predecessores
    list<int> vertices_adjacentes; //lista de adjacencia de vertice
    
    //metodos padrões
    int get_id();
    float get_peso();
    bool get_foi_visitado();
    int get_grau_entrada();
    int get_grau_saida();

    void set_id(int id);
    void set_peso(float peso);
    void set_foi_visitado(bool foi_visitado);
    void set_grau_entrada(int grau_entrada);
    void set_grau_saida(int grau_saida);

};
