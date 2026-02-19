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
    }else {
        throw std::runtime_error("Error: El árbol está vacío, no se puede acceder a la raíz.");
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
void ArbolKD<T>::insertar(const T& val) {
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

template <class T>
NodoKD<T>* ArbolKD<T>::buscarPorIndice(int indice) {
    return raiz ? raiz->buscarPorIndice(indice) : nullptr;
}





template<class T>
std::deque<T> ArbolKD<T>::preOrden() {
    if (raiz != nullptr) {
        return raiz->preOrden();  
    }else {
        return std::deque<T>(); 
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


template <typename T>
T ArbolKD<T>::encontrarMaximo(NodoKD<T>* nodo, int dimension) {
    if (nodo == nullptr) {
        throw std::runtime_error("El árbol está vacío");
    }

    // Inicializamos el vértice con el dato del nodo actual
    Vertice maxDato = nodo->getDato();

    // Recorremos el subárbol izquierdo y derecho para encontrar los máximos en cada dimensión
    if (nodo->getHijoIzq() != nullptr) {
        Vertice maxIzquierda = encontrarMaximo(nodo->getHijoIzq(), (dimension + 1) % 3);
        if (maxIzquierda.getX() > maxDato.getX()) maxDato.setX(maxIzquierda.getX());
        if (maxIzquierda.getY() > maxDato.getY()) maxDato.setY(maxIzquierda.getY());
        if (maxIzquierda.getZ() > maxDato.getZ()) maxDato.setZ(maxIzquierda.getZ());
    }

    if (nodo->getHijoDer() != nullptr) {
        Vertice maxDerecha = encontrarMaximo(nodo->getHijoDer(), (dimension + 1) % 3);
        if (maxDerecha.getX() > maxDato.getX()) maxDato.setX(maxDerecha.getX());
        if (maxDerecha.getY() > maxDato.getY()) maxDato.setY(maxDerecha.getY());
        if (maxDerecha.getZ() > maxDato.getZ()) maxDato.setZ(maxDerecha.getZ());
    }

    return maxDato;
}

template <typename T>
T ArbolKD<T>::encontrarMinimo(NodoKD<T>* nodo, int dimension) {
    if (nodo == nullptr) {
        throw std::runtime_error("El árbol está vacío");
    }

    // Inicializamos el vértice con el dato del nodo actual
    Vertice minDato = nodo->getDato();

    // Recorremos el subárbol izquierdo y derecho para encontrar los mínimos en cada dimensión
    if (nodo->getHijoIzq() != nullptr) {
        Vertice minIzquierda = encontrarMinimo(nodo->getHijoIzq(), (dimension + 1) % 3);
        if (minIzquierda.getX() < minDato.getX()) minDato.setX(minIzquierda.getX());
        if (minIzquierda.getY() < minDato.getY()) minDato.setY(minIzquierda.getY());
        if (minIzquierda.getZ() < minDato.getZ()) minDato.setZ(minIzquierda.getZ());
    }

    if (nodo->getHijoDer() != nullptr) {
        Vertice minDerecha = encontrarMinimo(nodo->getHijoDer(), (dimension + 1) % 3);
        if (minDerecha.getX() < minDato.getX()) minDato.setX(minDerecha.getX());
        if (minDerecha.getY() < minDato.getY()) minDato.setY(minDerecha.getY());
        if (minDerecha.getZ() < minDato.getZ()) minDato.setZ(minDerecha.getZ());
    }

    return minDato;
}




template <typename T>
T ArbolKD<T>::encontrarMaximo() {
    return encontrarMaximo(raiz, 0);  //Se comienza por la raiz y con la dimensión x
}

template <typename T>
T ArbolKD<T>::encontrarMinimo() {
    return encontrarMinimo(raiz, 0);  
}



template<class T>
T ArbolKD<T>::verticeCercano(float px, float py, float pz, int nivel, float& mejorDistancia) {
    if (!raiz) {
        return T(); // Vertice vacío
    }

    NodoKD<T>* nodoActual = raiz;
    float distanciaActual = nodoActual->getDato().calcularDistancia(px, py, pz);
    
    T mejorVertice = nodoActual->getDato();

    buscarVerticeCercano(nodoActual, px, py, pz, nivel, mejorVertice, distanciaActual);

    return mejorVertice;
}

template<class T>
void ArbolKD<T>::buscarVerticeCercano(NodoKD<T>* nodo, float px, float py, float pz, int nivel, T& mejorVertice, float& mejorDistancia) {
    if (!nodo) return;

    // Calcular la distancia entre el punto dado y el nodo actual
    float distancia = nodo->getDato().calcularDistancia(px, py, pz);

    if (distancia < mejorDistancia) {
        mejorDistancia = distancia;
        mejorVertice = nodo->getDato();
    }

    // Se mira la dimensión actual
    int dimension = nivel % 3;
    float coordenadaNodo = nodo->getDato().getCoord(dimension);
    float coordenadaPunto = (dimension == 0) ? px : (dimension == 1) ? py : pz;

    //Se va aun subarbol u otro dependiendo de la coordenada
    NodoKD<T>* primeraOpcion = (coordenadaPunto < coordenadaNodo) ? nodo->getHijoIzq() : nodo->getHijoDer();
    NodoKD<T>* segundaOpcion = (coordenadaPunto < coordenadaNodo) ? nodo->getHijoDer() : nodo->getHijoIzq();

    buscarVerticeCercano(primeraOpcion, px, py, pz, nivel + 1, mejorVertice, mejorDistancia);

    // Verificar si necesitamos explorar el otro lado del árbol (lado secundario)
    if (std::abs(coordenadaPunto - coordenadaNodo) < mejorDistancia) {
        buscarVerticeCercano(segundaOpcion, px, py, pz, nivel + 1, mejorVertice, mejorDistancia);
    }
}





