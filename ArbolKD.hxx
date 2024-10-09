#include "NodoKD.h"
#include "ArbolKD.h"

template<class T>
ArbolKD<T>::ArbolKD() : raiz(nullptr) {}

template<class T>
bool ArbolKD<T>::esVacio() {
    return raiz == nullptr;
}

template<class T>
T& ArbolKD<T>::datoRaiz() {
    if (raiz != nullptr) {
        return raiz->getDato();
    }
}

template<class T>
int ArbolKD<T>::altura() {
    if(raiz==nullptr){
        return -1;
    }
    return raiz->altura();
}

template<class T>
int ArbolKD<T>::tam() const {
    if(raiz==nullptr){
        return 0;
    };
    if(raiz->getHijoIzq()==nullptr && raiz->getHijoDer()==nullptr){
        return 1;
    }
    return raiz->tam();
}


template<class T>
void ArbolKD<T>::insertar(T& val) {
    if(raiz!=nullptr){
        raiz->insertar(val, 0);
    }else{
        raiz= new NodoKD<T>();
        raiz->setDato(val);
        raiz->setDimension(0); //Se comienza por x
    }
}



// Buscar un valor en el árbol
template<class T>
NodoKD<T>* ArbolKD<T>::buscar(T& val) {
    if(raiz!=nullptr){
        return raiz->buscar(val, 0);
    }
    return nullptr;
}




template<class T>
void ArbolKD<T>::preOrden() {
    if (raiz != nullptr) {
        raiz->preOrden();  
    }
}

template<class T>
void ArbolKD<T>::posOrden() {
    if (raiz != nullptr) {
        raiz->posOrden();  
    }
}

template<class T>
void ArbolKD<T>::inOrden() {
    if (raiz != nullptr) {
        raiz->inOrden();  
    }
}

template<class T>
void ArbolKD<T>::nivelOrden() {
    if (raiz != nullptr) {
        raiz->nivelOrden();  
    }
}
