#ifndef CARA_H
#define CARA_H
#include "arista.h"
#include "vertice.h"
#include <deque>

class Cara{
    private:
        std::deque <Arista> aristas;
        std::deque <int> vertices; //Hace referencia a los indices de los vertices
    public:
        std::deque<Arista>&getAristas();
        std::deque<int>&getVertices();
        void agregarArista(const Arista & a);
        void agregarVertice(int v);
        void asignarAristas();
        int getNAristas() const;
        int getNVertices() const;
        const std::deque<Arista>& getAristas() const; 
};

#endif


