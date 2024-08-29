#include "arista.h"
#include <tuple>

Arista::Arista(int v1, int v2): vertice1(v1), vertice2(v2){}

int Arista::getVertice1() const{
    return vertice1;
}
int Arista::getVertice2() const{
    return vertice2;
}

