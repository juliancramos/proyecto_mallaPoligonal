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



std::ostream& operator<<(std::ostream& os, const Vertice& v) {
    os << "Vertice: (" << v.x << ", " << v.y << ", " << v.z << ") - Indice: " << v.indice;
    return os;
}

float Vertice::getCoord(int dimension) const {
    switch (dimension) {
        case 0: return x; 
        case 1: return y; 
        case 2: return z; 
        default: throw std::out_of_range("Dimensión fuera de rango");
    }
}

float Vertice::calcularDistancia(float x2, float y2, float z2) const {
    return std::sqrt(std::pow(x - x2, 2) + std::pow(y - y2, 2) + std::pow(z - z2, 2));
}




Vertice& Vertice::operator=(const Vertice& other) {
        if (this != &other) {  // Prevenir auto-asignación
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            this->indice = other.indice;
        }
        return *this;
    }
    
    
bool Vertice::operator==(const Vertice& v) const {
        return (this->x == v.x && this->y == v.y && this->z == v.z);
}

   
