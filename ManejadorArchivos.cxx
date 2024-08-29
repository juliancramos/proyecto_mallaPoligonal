#include "ManejadorArchivos.h"
#include "figura.h"
#include "vertice.h"
#include "malla_poligonal.h"
#include "cara.h"
#include "arista.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

void ManejadorArchivos::leerArchivo(const std::string &nombreArchivo, MallaPoligonal &malla){
    //Declaración de variables necesarias

    int nVertices, nVerticesCara,indice;
    float x,y,z;
    std::string linea, nombreObjeto;


    //Abrir el flujo del archivo
    std::ifstream entrada (nombreArchivo);
    if(!entrada){
        throw std::runtime_error("El archivo \""+nombreArchivo+"\" no existe o es ilegible");
    }

    //Guardar nombre y numero de vertices del objeto
    entrada>>nombreObjeto;
    if(nombreObjeto.empty()){
        throw std::runtime_error("Nombre del objeto no encontrado");
    }
    //Se verifica si la figura ya se encuentra en el sistema
    bool figura=malla.figuraExiste(nombreObjeto);
    if (figura) {
        throw std::runtime_error("El objeto \""+nombreObjeto+"\" ya ha sido cargado en memoria");
    } 

    entrada>>nVertices;
    Figura fig(nombreObjeto);
    if(nVertices<=0){
        throw std::runtime_error("Numero invalido de vertices");
    }
    /* PRUEBAS
    std::cout<<nombreObjeto<<std::endl;
    std::cout<<nVertices<<std::endl;
    std::cout<<"Guardar vertices"<<std::endl;
  */
    //Guardar vertices
    for(int i=0; i<nVertices; i++){
        entrada>>x;
        entrada>>y;
        entrada>>z;
        //::cout<<x<<" "<<y<<" "<<z<<std::endl;
        Vertice v(x, y, z, i);
        fig.agregarVertice(v);
    }
    //Se linea una linea como escape para comenzar a leer las caras
    std::getline(entrada, linea);
    //Guardar caras
    while(std::getline(entrada, linea)){
        Cara cara;
        std::istringstream stream(linea);
        stream>>nVerticesCara;
        //std::cout<<"Vertices de la cara: "<<nVerticesCara<<std::endl;
        if(nVerticesCara==-1){
            break; //Significa qua ya se terminó el proceso
        }
        if (nVerticesCara < 3) {
            throw std::runtime_error("Una cara debe tener al menos 3 vértices.");
        }

        for(int i=0; i<nVerticesCara; i++){
            stream>>indice;
            if(indice>nVertices-1){
                throw std::runtime_error("El vertice de la cara no fue encontrado");
            }

            cara.agregarVertice(indice);
        }
        //Ya que se tienen todos los vertices de la cara se asignan sus aristas
        cara.asignarAristas();//Asigna todas las aristas de la cara según los vertices

        //Una vez guardados todos los vertices de la cara, se guarda la cara.
        fig.agregarCara(cara);
    }
    malla.agregarFigura(fig);
    //figuras.push_back(fig);
}

void ManejadorArchivos::escribirArchivoObjeto(Figura * figura, const std::string& nombreArchivo){
    std::deque<Vertice> vertices=figura->getVertices();
  std::deque<Cara> caras=figura->getCaras();
  std::deque<int> verticesCara; //De números enteros ya que se almacenan los indices del vertice
  std::deque<Vertice>::iterator it=vertices.begin();
  std::deque<Cara>::iterator itCara=caras.begin();
  
    std::ofstream salida(nombreArchivo);
    if(!salida){
        throw std::runtime_error("No se pudo crear el archivo \""+nombreArchivo+"\"");
    }
  salida<<figura->getNombre()<<std::endl;
  salida<<vertices.size()<<std::endl;
  for(; it!=vertices.end(); it++){
    salida<<it->getX()<<" "<<it->getY()<<" "<<it->getZ()<<std::endl;
  }
  
  for(; itCara!=caras.end(); itCara++){
    salida<<itCara->getNVertices()<<" ";
    verticesCara=itCara->getVertices();
    for(int i=0; i<itCara->getNVertices(); i++){
      salida<<verticesCara[i]<<" ";
    }
    salida<<std::endl;
    salida<<"-1";
  }
  
}