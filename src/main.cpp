#include <iostream>
#include <string>
#include <list>
#include "Grafo.h"

using namespace std;


int main (int argc, char * argv[])
{
    Grafo* grafo01 = new Grafo(1,0,0,0);

    cout << grafo01->get_ehDirecionado()<<endl;

    return 0;
}
