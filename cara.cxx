#include "cara.h"

#include <stdexcept>

void Cara::agregarArista(const Arista & a){
    aristas.push_back(a);
}

void Cara::agregarVertice(int v){
    vertices.push_back(v);
}

void Cara::asignarAristas() {
    if (vertices.size() < 3) {
        throw std::runtime_error("Una cara debe tener al menos 3 vértices.");
    }

    int v1, v2;
    for (int i = 0; i < vertices.size() - 1; i++) {
        v1 = vertices[i];
        v2 = vertices[i + 1];

        // Crear la arista sin la distancia (se asigna -1 por defecto)
        Arista a(v1, v2);
        agregarArista(a);
    }

    // Conectar el último vértice con el primero para cerrar la cara
    Arista aFinal(vertices.back(), vertices[0]);
    agregarArista(aFinal);
}


const std::deque<Arista>& Cara::getAristas() const{
    return aristas;
}
int Cara::getNAristas() const{
    return aristas.size();
}
int Cara::getNVertices() const{
    return vertices.size();
}
std::deque<Arista>&Cara::getAristas(){
    return aristas;
}
std::deque<int>&Cara::getVertices(){
    return vertices;
}