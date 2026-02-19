
#include "NodoKD.h"
#include <string>
#include <iostream>
#include <queue>

template<class T>
NodoKD<T>::NodoKD() : hijoIzq(nullptr), hijoDer(nullptr), dimension(0) {}

template<class T>
T& NodoKD<T>::getDato() {
    return dato;
}

template<class T>
void NodoKD<T>::setDato(const T& val) {
    dato= val;
}

template<class T>
NodoKD<T>* NodoKD<T>::getHijoIzq() {
    return hijoIzq;
}

template<class T>
NodoKD<T>* NodoKD<T>::getHijoDer() {
    return hijoDer;
}

template<class T>
void NodoKD<T>::setHijoIzq(NodoKD<T>* izq) {
    hijoIzq = izq;
}

template<class T>
void NodoKD<T>::setHijoDer(NodoKD<T>* der) {
    hijoDer = der;
}

template<class T>
int NodoKD<T>::getDimension() {
    return dimension;
}

template<class T>
void NodoKD<T>::setDimension(int d) {
    dimension = d;  
}


template<class T>
int NodoKD<T>::altura() {
    if (this == nullptr) {
        return -1;  // La altura de un nodo nulo es -1
    }
    return 1 + std::max((hijoIzq ? hijoIzq->altura() : -1), (hijoDer ? hijoDer->altura() : -1));
}

template<class T>
int NodoKD<T>::tam() const {
    if (this == nullptr) {
        return 0;  // Si el nodo es nulo, el tamaño es 0
    }
    return 1 + (hijoIzq ? hijoIzq->tam() : 0) + (hijoDer ? hijoDer->tam() : 0);
}


template<class T>
void NodoKD<T>::insertar(const T& val, int profundidad) {
    // Si el nodo actual está vacío se inserta el nuego valor
    if (dato.getIndice() == -1) {  //El constructor por defecto de Vertice indica que el indice es -1 
        setDato(val); 
        setDimension(profundidad % 3);  // Para alternar entre x, y, z 
        return;
    }

    // Comparar por la dimensión actual (x, y, z)
    int dim = getDimension();
    float valCoord, nodoCoord;

    // Se obtienen las coordenadas del nodo actual y del vertice a insertar según la dimensión
    if (dim == 0) {
        valCoord = val.getX();  
        nodoCoord = dato.getX(); 
    } else if (dim == 1) {
        valCoord = val.getY();  
        nodoCoord = dato.getY();  
    } else {
        valCoord = val.getZ(); 
        nodoCoord = dato.getZ();  
    }

    //Se evalúa si según la dimensión, se debe insertar por derecha o izquierda
    if (valCoord < nodoCoord) {
        if (hijoIzq == nullptr) {
            hijoIzq = new NodoKD<T>();  
        }
        hijoIzq->insertar(val, profundidad + 1);  
    } else {
        if (hijoDer == nullptr) {
            hijoDer = new NodoKD<T>();  
        }
        hijoDer->insertar(val, profundidad + 1);  
    }
}


template<class T>
NodoKD<T>* NodoKD<T>::buscar(const T& val, int profundidad) {
    if (this == nullptr) {
        return nullptr;  
    }

    // Comparar el vértice actual con el vértice a buscar
    if (getDato().getIndice() == val.getIndice() && 
        getDato().getX() == val.getX() && 
        getDato().getY() == val.getY() && 
        getDato().getZ() == val.getZ()) {
        return this; 
    }

    int dim = getDimension();
    
    // Se compara si es mayor o menor dependiendo en la dimensión actual
    if ((dim == 0 && val.getX() < getDato().getX()) || 
        (dim == 1 && val.getY() < getDato().getY()) || 
        (dim == 2 && val.getZ() < getDato().getZ())) {
        return hijoIzq ? hijoIzq->buscar(val, profundidad + 1) : nullptr;  // Busca en el subárbol izquierdo
    } else {
        return hijoDer ? hijoDer->buscar(val, profundidad + 1) : nullptr;  // Busca en el subárbol derecho
    }
}

template<class T>
NodoKD<T>* NodoKD<T>::buscarPorIndice(int indice) {
    if (this == nullptr) {
        return nullptr;
    }

    // Comparar el índice actual con el índice a buscar
    if (getDato().getIndice() == indice) {
        return this;  // Retorna el nodo actual si el índice coincide
    }

    // Busca en ambos hijos ya que no estamos comparando por dimensión
    NodoKD<T>* nodoIzq = hijoIzq ? hijoIzq->buscarPorIndice(indice) : nullptr;
    if (nodoIzq != nullptr) {
        return nodoIzq;
    }

    return hijoDer ? hijoDer->buscarPorIndice(indice) : nullptr;
}





template<class T>
std::deque<T> NodoKD<T>::preOrden() {
    std::deque<T> resultado;

    // Agregamos el dato actual al deque
    resultado.push_back(this->dato);

    //Se agregan los elementos del subarbol izquierdo
    if (this->hijoIzq != nullptr) {
        std::deque<T> izquierdo = this->hijoIzq->preOrden();
        resultado.insert(resultado.end(), izquierdo.begin(), izquierdo.end());
    }

    //Se agregan los elementos del subarbol derecho
    if (this->hijoDer != nullptr) {
        std::deque<T> derecho = this->hijoDer->preOrden();
        resultado.insert(resultado.end(), derecho.begin(), derecho.end());
    }

    return resultado;
}

template<class T>
void NodoKD<T>::posOrden() {
    if (this->hijoIzq != nullptr) {
        this->hijoIzq->posOrden();
    }

    if (this->hijoDer != nullptr) {
        this->hijoDer->posOrden();
    }

    std::cout << this->dato << " " << std::endl;
}

template<class T>
void NodoKD<T>::inOrden() {
    //std::cout<<"Para el nodo actual: "<<dato<<std::endl;
    if (this->hijoIzq != nullptr) {
        //std::cout<<"Para el izq: "<<this->hijoIzq->dato<<std::endl;
        this->hijoIzq->inOrden();
    }

    std::cout << this->dato << " " << std::endl;

    if (this->hijoDer != nullptr) {
        //std::cout<<"Para el der: "<<this->hijoDer->dato<<std::endl;
        this->hijoDer->inOrden();
    }
}
  

template<class T>
void NodoKD<T>::nivelOrden() {
    std::queue<NodoKD<T>*> cola;
    cola.push(this);  // Agrega el nodo actual a la cola

    while (!cola.empty()) {
        NodoKD<T>* nodoActual = cola.front();
        cola.pop();

        std::cout << nodoActual->dato << " " << std::endl;

        // Agrega los hijos a la cola
        if (nodoActual->hijoIzq != nullptr) {
            cola.push(nodoActual->hijoIzq);
        }
        if (nodoActual->hijoDer != nullptr) {
            cola.push(nodoActual->hijoDer);
        }
    }
}
