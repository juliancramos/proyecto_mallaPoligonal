#ifndef _NODO_KD_H
#define _NODO_KD_H


template<class T>
class NodoKD {
private:
    T dato;
    NodoKD<T>* hijoIzq;  
    NodoKD<T>* hijoDer;  
    int dimension; // 0:x 1:y 2:z

public: 
    NodoKD();
    T& getDato();
    void setDato(const T& val);
    NodoKD<T>* getHijoIzq();
    NodoKD<T>* getHijoDer();
    void setHijoIzq(NodoKD<T>* izq);
    void setHijoDer(NodoKD<T>* der);
    int getDimension();
    void setDimension(int d);
    int altura();
    int tam() const;

    void insertar(const T& val, int profundidad);
    NodoKD<T>* buscar(const T& val, int profundidad);

    std::deque<T> preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();

    T verticeCercano(float px, float py, float pz, int nivel, float& mejorDistancia);
    



};
#include "NodoKD.hxx"

#endif