#include "vertice.h"

// Constructor
Vertice::Vertice(float x, float y, float z, int i) : x(x), y(y), z(z), indice(i) {}



// Getters
float Vertice::getX() const {
    return x;
}

float Vertice::getY() const {
    return y;
}

float Vertice::getZ() const {
    return z;
}
int Vertice::getIndice() const {
    return indice;
}

// Setters
void Vertice::setX(float x) {
    this->x = x;
}

void Vertice::setY(float y) {
    this->y = y;
}

void Vertice::setZ(float z) {
    this->z = z;
}