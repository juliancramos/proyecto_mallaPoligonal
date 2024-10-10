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

ArbolKD<Vertice>* Figura::getVertices() {
    return arbolVertices;  
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
    /*
    Se usa la relación de Euler para los poliedros, la cual dice:
    V−E+F=2 con V:nVertices, E: nAristas y F:nCaras
    entonces E=V+F-2
    */
    int nVertices, nAristas, nCaras;
    nVertices=getNVertices();
    nCaras=getNCaras();
    nAristas=nVertices+nCaras-2;
    return nAristas;
}
    
    