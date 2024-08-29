#ifndef FIGURA_H
#define FIGURA_H
#include "cara.h"

#include <string>
#include <deque>

class Figura{
    private:
        
        std::string nombre;
        std::deque<Cara> caras;
        std::deque<Vertice> vertices;

    public:

        Figura (const std::string & n);
        std::deque<Cara>& getCaras();
        std::deque<Vertice>& getVertices();
        
        void agregarCara(const Cara & c);
        void agregarVertice(const Vertice &v);
        int buscarIndiceVertice(float x, float y, float z);
        std::string getNombre() const;
        int getNCaras() const;
        int getNVertices() const;
        int getNAristasFigura() const;

        std::deque<Vertice> envolventeObjeto();//En la posición 0 se encuentra el vertice mayor y en la 1 el menor

        static Figura construirCajaEnvolvente(const std::deque<Vertice>& vertices, const std::string& nombreObjeto);
};
#endif


