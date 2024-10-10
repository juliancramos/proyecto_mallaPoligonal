#include "malla_poligonal.h"
#include "figura.h"
#include "cara.h"
#include "arista.h"
#include "vertice.h"
#include "ManejadorArchivos.h"

#include <stdexcept>
#include <deque>
#include <fstream>

#include <string>
#include <iostream>
#include <iterator>

std::deque<Figura> MallaPoligonal::getFiguras() const{
    return figuras;
}
void MallaPoligonal::eliminarFigura(int posicion){
    auto it=figuras.begin()+posicion;
    figuras.erase(it);
}



void MallaPoligonal::agregarFigura(const Figura &figura){
    bool existe=figuraExiste(figura.getNombre());
    
    if(!existe)
    figuras.push_back(figura);
    else{
        throw std::runtime_error("El objeto \""+figura.getNombre()+"\" ya ha sido cargado en memoria");
    }
        
}


bool MallaPoligonal::figuraExiste(const std::string &nombreFigura){
    std::deque<Figura>::iterator it=figuras.begin();
    for(; it!=figuras.end(); it++){
        if(it->getNombre()==nombreFigura){
            return true;
        }
    }
    return false;
}

Figura* MallaPoligonal::getFigura(const std::string &nombreFigura){
    std::deque<Figura>::iterator it=figuras.begin();
    
    for(; it!=figuras.end(); it++){
        if(it->getNombre()==nombreFigura){
            return &(*it);
        }
    }
    return nullptr;
}


int MallaPoligonal::getPosicionFigura(const std::string & nombreFigura){
    for(int i=0; i<figuras.size(); i++){
        if(figuras[i].getNombre()==nombreFigura){
            return i;
        }
    }
    return -1;
}



void MallaPoligonal::cargar(const std::string &nombre_archivo, MallaPoligonal &malla) {
    ManejadorArchivos::leerArchivo(nombre_archivo, malla);
}

void MallaPoligonal::listado() {
    std::cout << "Hay n objetos en memoria: " << std::endl;
}

Figura MallaPoligonal::envolvente() {
    if(figuras.size()>0){
        std::deque<Vertice>envolventeFigura;//Se guardan los valores del calculo del envolvente para cada figura. En la casilla 0 el vertice mayor y en la 1 el menor
        std::deque<Figura>::iterator it=figuras.begin();
        envolventeFigura=figuras[0].envolventeObjeto();
             
        float mayorX = envolventeFigura[0].getX(), menorX = envolventeFigura[1].getX();
        float mayorY = envolventeFigura[0].getY(), menorY = envolventeFigura[1].getY();
        float mayorZ = envolventeFigura[0].getZ(), menorZ = envolventeFigura[1].getZ();
        

        for(; it!=figuras.end(); it++){
            envolventeFigura=it->envolventeObjeto();
            //Proceso para calcular cada mayor
            if(envolventeFigura[0].getX()>mayorX){
                mayorX=envolventeFigura[0].getX();    
                
            }
            if(envolventeFigura[0].getY()>mayorY){
                mayorY=envolventeFigura[0].getY();

            }
            if(envolventeFigura[0].getZ()>mayorZ){
                mayorZ=envolventeFigura[0].getZ();

            }
            //Proceso para calcular cada menor
            if(envolventeFigura[1].getX()<menorX){
                menorX=envolventeFigura[1].getX();

            }
            if(envolventeFigura[1].getY()<menorY){
                menorY=envolventeFigura[1].getY();

            }
            if(envolventeFigura[1].getZ()<menorZ){
                menorZ=envolventeFigura[1].getZ();

            }
        }
        Vertice vMayor(mayorX, mayorY, mayorZ, 0);
        Vertice vMenor(menorX, menorY, menorZ, 1);
        std::deque<Vertice> envolvente;
        //Los vertices mayor y menor de toda la malla quedan almacenados
        envolvente.push_back(vMayor);
        envolvente.push_back(vMenor);
        Figura f=Figura::construirCajaEnvolvente(envolvente,"global");
        return f;
        
        
        
    }else{
        throw std::runtime_error("Ningun objeto ha sido cargado en memoria");
    }
    
}

Figura MallaPoligonal::envolventeObjeto(const std::string &nombre_objeto) {
    Figura *figura = getFigura(nombre_objeto);
    if (figura) {
        std::deque<Vertice> verticesEnvolvente = figura->envolventeObjeto();
        
        Figura f=Figura::construirCajaEnvolvente(verticesEnvolvente, nombre_objeto);
        return f;
        
    }else{
        throw std::runtime_error("El objeto \""+nombre_objeto+"\" no ha sido cargado en memoria");
    }
   return Figura(" "); //retorna una figura vacía
}


void MallaPoligonal::descargarObjeto(const std::string &nombre_objeto) {
    bool fig=figuraExiste(nombre_objeto);
    if(fig){
        int posicion=getPosicionFigura(nombre_objeto);
        eliminarFigura(posicion);
    }else{
        throw std::runtime_error("El objeto " + nombre_objeto + " no ha sido cargado en memoria");
    }
}

void MallaPoligonal::guardarObjeto(const std::string &nombre_objeto, const std::string &nombre_archivo) {
    bool existe=figuraExiste(nombre_objeto);
    if(existe){
        Figura *figura=getFigura(nombre_objeto);
        ManejadorArchivos::escribirArchivoObjeto(figura, nombre_archivo);
    }else{
        throw std::runtime_error("El objeto \""+nombre_objeto+"\" no ha sido cargado en memoria");
    }
}

Vertice MallaPoligonal::verticeCercanoObjeto(float x, float y, float z, const std::string& nombreFigura) {
    Figura* figura = getFigura(nombreFigura);

    if (!figura) {
        std::cerr << "Figura no encontrada" << std::endl;
        return Vertice();  //Vertice por defecto con indice -1
    }

    return figura->verticeCercano(x, y, z);
}

Figura MallaPoligonal::verticeCercano(float px, float py, float pz){
    if (figuras.size() > 0) {
        // para comenzar, le vertice más cercano se inicializa como el de la primera figura
        float mejorDistancia=-1;
        Vertice cercanoActual = figuras[0].getVertices()->verticeCercano(px, py, pz, 0, mejorDistancia);
        float distanciaActual = cercanoActual.calcularDistancia(px, py, pz);
        std::string nombreActual = figuras[0].getNombre();

        // Se recorren todas y por cada una se haya el vertice mas cercano para poder comparar
        for (const auto& fig : figuras) {
            //Se llama al arbol ya que vertices es el kd
            Vertice verticeTemp = fig.getVertices()->verticeCercano(px, py, pz, 0, mejorDistancia); 
            float distanciaTemp = verticeTemp.calcularDistancia(px, py, pz);

            if (distanciaTemp < distanciaActual) {
                distanciaActual = distanciaTemp;
                cercanoActual = verticeTemp;
                nombreActual = fig.getNombre();
            }
        }

        // Crear una figura con el nombre y agregar el vértice más cercano(único vertice de la fígura)
        Figura final(nombreActual);
        final.agregarVertice(cercanoActual);
        return final;
    }
    throw std::runtime_error("No hay figuras cargadas en la malla");
}






void MallaPoligonal::v_cercanos_caja(const std::string &nombre_objeto) {
    std::cout << "Los vértices del objeto \"" << nombre_objeto << "\" más cercanos a las esquinas de su caja envolvente son:\n";
    // Aquí podrías listar los vértices más cercanos a la caja envolvente
}

