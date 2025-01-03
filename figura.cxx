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

Vertice Figura::getCentroide() const {
    return centroide;
}

void Figura::setCentroide(const Vertice &centroide) {
    this->centroide = centroide;
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


Vertice Figura::verticeCercano(float px, float py, float pz) const {
    if (!arbolVertices || arbolVertices->esVacio()) {
        std::cerr << "El árbol KD de la figura está vacío." << std::endl;
        return Vertice();  //Vertice por defecto
    }
    
    float mejorDistancia = -1;  //Inicia con valor inválido 
    return arbolVertices->verticeCercano(px, py, pz, 0, mejorDistancia);
}

//Este metodo calcula la distancia euclidiana para todas las aristas de la figura
void Figura::calcularDistancias() {
    // Recorrer todas las caras
    for (auto& cara : caras) {
        // Recorrer todas las aristas de cada cara
        for (auto& arista : cara.getAristas()) {
            // Verificar si la distancia es -1 (no se ha calculado aún ya que por defecto es -1)
            if (arista.getDistancia() == -1.0f) {
                int origen = arista.getVertice1();
                int destino = arista.getVertice2();

                // Obtener los vértices  usando los índices
                Vertice verticeOrigen = buscarVerticePorIndice(origen);
                Vertice verticeDestino = buscarVerticePorIndice(destino);

                // Calcular la distancia euclidiana
                float distancia = verticeOrigen.calcularDistancia(verticeDestino.getX(), verticeDestino.getY(), verticeDestino.getZ());

                arista.setDistancia(distancia);
            }
        }
    }
}



void Figura::llenarGrafo() {
    std::set<std::pair<int, int>> aristasUnicas; // Para almacenar aristas únicas (set para que no se repitan)

    for (Cara& c : caras) {
        std::deque<Arista> aristas = c.getAristas();
        for (Arista& a : aristas) {
            int v1 = a.getVertice1(); // Obtiene los índices de los vertices en la arista
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


std::pair<std::vector<int>, float> Figura::calcularRutaMasCorta(int indiceOrigen, int indiceDestino) {
    //Esto es solo una prueba
    // std::cout << "Pesos de las aristas en la figura:\n";
    // for (const auto& cara : caras) {
    //     for (const auto& arista : cara.getAristas()) {
    //         std::cout << "Arista de " << arista.getVertice1() << " a "
    //                   << arista.getVertice2() << " con peso: "
    //                   << arista.getDistancia() << "\n";
    //     }
    // }
    std::vector<int> ruta;
    float distanciaTotal = 0.0f;

    try {
        // Calcular la ruta más corta
        //Pair de vector de enteros para las rutas (en primera posicion) y la distancia (en segunda)
        auto resultado = grafoIndices.rutaMasCorta(indiceOrigen, indiceDestino);
        ruta = resultado.first;
        distanciaTotal = resultado.second;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return {ruta, distanciaTotal};
}
//Calcula y retorna el vertice centroide
Vertice Figura::calcularCentroide() {
    if (arbolVertices->esVacio()) {
        throw std::runtime_error("La figura no contiene vértices.");
    }

    std::deque<Vertice> vertices = arbolVertices->preOrden();
    float sumaX = 0, sumaY = 0, sumaZ = 0;
    int totalVertices = vertices.size();

    for (const auto& vertice : vertices) {
        sumaX += vertice.getX();
        sumaY += vertice.getY();
        sumaZ += vertice.getZ();
    }

    // Se calcula mediante las coordenadas promedio
    float centroX = sumaX / totalVertices;
    float centroY = sumaY / totalVertices;
    float centroZ = sumaZ / totalVertices;

    // Crear el vértice centroide
    Vertice centroide(centroX, centroY, centroZ, -2); //centroide con indice -2

    return centroide;
}

void Figura::agregarAristaGrafo(int nodo1, int nodo2, double peso) {
    grafoIndices.agregarArista(nodo1, nodo2, peso);
}




    