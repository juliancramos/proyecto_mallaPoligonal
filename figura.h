#ifndef FIGURA_H
#define FIGURA_H
#include "cara.h"
#include "ArbolKD.h"
#include "Grafo.h"
#include "vertice.h"
#include <cmath>
#include <string>
#include <deque>

class Figura{
    private:
        
        std::string nombre;
        std::deque<Cara> caras;
        ArbolKD<Vertice>* arbolVertices= new ArbolKD<Vertice>();
        Grafo <int> grafoIndices; //Grafo que almacena los indices de los vertices
        Vertice centroide;
    public:

        Figura (const std::string & n);
        std::deque<Cara>& getCaras();
        ArbolKD<Vertice>* getVertices() const;
        
        void agregarCara(const Cara & c);
        void agregarVertice(const Vertice &v);
        int buscarIndiceVertice(float x, float y, float z);
        Vertice buscarVerticePorIndice(int indice);
        std::string getNombre() const;
        int getNCaras() const;
        int getNVertices() const;
        int getNAristasFigura() const;

        Vertice getCentroide() const;

        void setCentroide(const Vertice &centroide);


        std::deque<Vertice> envolventeObjeto();//En la posición 0 se encuentra el vertice mayor y en la 1 el menor


        static Figura construirCajaEnvolvente(const std::deque<Vertice>& vertices, const std::string& nombreObjeto);

        Vertice verticeCercano(float px, float py, float pz) const;
        void calcularDistancias();

        void llenarGrafo();

        Grafo<int> getGrafo() const;
        void agregarAristaGrafo(int nodo1, int nodo2, double peso);

        std::pair<std::vector<int>, float>calcularRutaMasCorta(int indiceOrigen, int indiceDestino);
        Vertice calcularCentroide();
};
#endif


