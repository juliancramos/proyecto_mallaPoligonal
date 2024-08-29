#ifndef ARISTA_H
#define ARISTA_H
#include <deque>

class Arista{
    private:
        //Hace referencia a los indices de los vertices
        int vertice1;
        int vertice2;

    public:
    Arista(int v1, int v2);
    int getVertice1() const;
    int getVertice2() const;

    

};

#endif


