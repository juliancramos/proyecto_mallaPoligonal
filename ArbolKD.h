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
        void insertar(T& val);
        NodoKD<T>* buscar(T& val);

        void preOrden();
        void inOrden();
        void posOrden();
        void nivelOrden();
    
    
};

#include "ArbolKD.hxx"

#endif
