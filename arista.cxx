#include "Arista.h"

Arista::Arista(int v1, int v2, float distancia)
    : v1(v1), v2(v2), distancia(distancia) {}

int Arista::getVertice1() const {
    return v1;
}

int Arista::getVertice2() const {
    return v2;
}

float Arista::getDistancia() const {
    return distancia;
}

void Arista::setDistancia(float dist) {
    distancia = dist;
}
