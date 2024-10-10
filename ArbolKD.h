#ifndef _ARBOL_KD_H_
#define _ARBOL_KD_H_

#include "NodoKD.h"

template<class T>
class ArbolKD {

    protected:
        NodoKD<T> *raiz;
    public:
        ArbolKD();
        bool esVacio();
        T& datoRaiz();
        int altura();
        int tam() const;
        void insertar(const T& val);
        NodoKD<T>* buscar(T& val);

        std::deque<T> preOrden();
        void inOrden();
        void posOrden();
        void nivelOrden();

        T encontrarMinimo(NodoKD<T>* nodo, int dimension);
        T encontrarMaximo(NodoKD<T>* nodo, int dimension);
        T encontrarMaximo();
        T encontrarMinimo();
    
    
};

#include "ArbolKD.hxx"

#endif
