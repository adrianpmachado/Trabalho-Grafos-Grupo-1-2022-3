#pragma once
#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

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

    // metodos padrões
    float obter_peso();
    int obter_id_saida();
    int obter_id_destino();
    bool obter_eh_direcionado();

    void set_peso(float peso);
    void set_id_saida(int id_saida);
    void set_id_destino(int id_destino);
    void set_eh_direcionado(bool eh_direcionado);
};
#endif // ARESTA_H_INCLUDED
