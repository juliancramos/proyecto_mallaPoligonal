#include "figura.h"
#include <string>
#include <set>
#include <iostream>


Figura::Figura(const std::string & n): nombre(n){}

void Figura:: agregarCara(const Cara & c){
    caras.push_back(c);
}
void Figura:: agregarVertice(const Vertice &v){
    //vertices.push_back(v);
    arbolVertices->insertar(v);
}

std::deque<Cara>&Figura:: getCaras(){
    return caras;
}

ArbolKD<Vertice>* Figura::getVertices() const{
    return arbolVertices;  
}

Grafo<int> Figura::getGrafo() const {
    return grafoIndices;
}

std::deque<Vertice> Figura::envolventeObjeto() {
    if (arbolVertices == nullptr) return {};  

    Vertice mayor = arbolVertices->encontrarMaximo();  
    Vertice menor = arbolVertices->encontrarMinimo();  

    

    Vertice vMayor(mayor.getX(), mayor.getY(), mayor.getZ(), 0);
    Vertice vMenor(menor.getX(), menor.getY(), menor.getZ(), 1);
   

    std::deque<Vertice> envolvente;
    envolvente.push_back(vMayor);
    envolvente.push_back(vMenor);
    
    return envolvente;
}

Figura Figura::construirCajaEnvolvente(const std::deque<Vertice>& vertices, const std::string& nombreObjeto){
    float mayorX=vertices[0].getX(), menorX=vertices[1].getX();
    float mayorY=vertices[0].getY(), menorY=vertices[1].getY();
    float mayorZ=vertices[0].getZ(), menorZ=vertices[1].getZ();
    


    std::string nuevoNombre="env_"+nombreObjeto;
    Figura f(nuevoNombre);
    f.agregarVertice(Vertice(menorX, menorY, menorZ, 0));
    f.agregarVertice(Vertice(mayorX, menorY, menorZ, 1));
    f.agregarVertice(Vertice(menorX, mayorY, menorZ, 2));
    f.agregarVertice(Vertice(mayorX, mayorY, menorZ, 3));
    f.agregarVertice(Vertice(menorX, menorY, mayorZ, 4));
    f.agregarVertice(Vertice(mayorX, menorY, mayorZ, 5));
    f.agregarVertice(Vertice(menorX, mayorY, mayorZ, 6));
    f.agregarVertice(Vertice(mayorX, mayorY, mayorZ, 7));

    auto agregarCara = [&](int v1, int v2, int v3, int v4) {
        Cara cara;
        cara.agregarVertice(v1);
        cara.agregarVertice(v2);
        cara.agregarVertice(v3);
        cara.agregarVertice(v4);
        f.agregarCara(cara);
    };

    // Agregar caras
    agregarCara(0, 1, 3, 2); // Cara inferior
    agregarCara(4, 5, 7, 6); // Cara superior
    agregarCara(0, 1, 5, 4); // Cara frontal
    agregarCara(2, 3, 7, 6); // Cara trasera
    agregarCara(0, 2, 6, 4); // Cara izquierda
    agregarCara(1, 3, 7, 5); // Cara derecha
    
    return f;
}
    

int Figura:: buscarIndiceVertice(float x, float y, float z){
    Vertice v(x,y,z, -1); //El indice es -1
    if(arbolVertices!=nullptr){
        NodoKD<Vertice>* nodo = arbolVertices->buscar(v);
        if (nodo != nullptr) {
            return nodo->getDato().getIndice();
        }
    }
    return -1;
}

Vertice Figura::buscarVerticePorIndice(int indice) {
    if (arbolVertices != nullptr) {
        NodoKD<Vertice>* nodo = arbolVertices->buscarPorIndice(indice);
        if (nodo != nullptr) {
            return nodo->getDato();  // Retorna el vértice encontrado
        }
    }
    throw std::runtime_error("Vértice con el índice especificado no encontrado");
}


std::string Figura::getNombre() const{
    return nombre;
}
int Figura::getNCaras() const{
    return caras.size();
}
int Figura::getNVertices() const{
    return arbolVertices->tam();
}


int Figura::getNAristasFigura() const {
    
    int nVertices, nAristas, nCaras;
    nVertices=getNVertices();
    nCaras=getNCaras();
    nAristas=nVertices+nCaras-2;
    return nAristas;
}
//Este metodo calcula la distancia euclidiana para todas las aristas de la figura
void Figura::calcularDistancias() {
    for (Cara& cara : caras) {
        for (Arista& arista : cara.getAristas()) {
            int v1 = arista.getVertice1();
            int v2 = arista.getVertice2();

            // Obtener los vértices de la figura
            Vertice vertice1 = buscarVerticePorIndice(v1);
            Vertice vertice2 = buscarVerticePorIndice(v2);

            // Calcular la distancia
            float distancia = vertice1.calcularDistancia(vertice2.getX(), vertice2.getY(), vertice2.getZ());

            // Establecer la distancia en la arista
            arista.setDistancia(distancia);
        }
    }
}



Vertice Figura::verticeCercano(float px, float py, float pz) const {
    if (!arbolVertices || arbolVertices->esVacio()) {
        std::cerr << "El árbol KD de la figura está vacío." << std::endl;
        return Vertice();  //Vertice por defecto
    }
    
    float mejorDistancia = -1;  //Inicia con valor inválido 
    return arbolVertices->verticeCercano(px, py, pz, 0, mejorDistancia);
}

void Figura::llenarGrafo() {
    std::set<std::pair<int, int>> aristasUnicas; // Para almacenar aristas únicas (set para que no se repitan)

    for (Cara& c : caras) {
        std::deque<Arista> aristas = c.getAristas();
        for (Arista& a : aristas) {
            int v1 = a.getVertice1(); // Obtiene los índices de la arista
            int v2 = a.getVertice2();

            // para asegurarse de que (v1, v2) y (v2, v1) sean consideradas la misma arista
            if (v1 > v2) std::swap(v1, v2);

            // std::cout << "ACTUAL V1: " << v1 << std::endl;
            // std::cout << "ACTUAL V2: " << v2 << std::endl;
            // Verificar si la arista ya fue agregada
            if (aristasUnicas.find({v1, v2}) == aristasUnicas.end()) { //Si pasa esto significa que no está
                aristasUnicas.insert({v1, v2});

                // Obtener el peso de la arista (distancia)
                double distancia = a.getDistancia();

                //std::cout << "Insertando arista: (" << v1 << ", " << v2 << ")\n";
                this->grafoIndices.agregarArista(v1, v2, distancia);
            }
        }
    }
}





    