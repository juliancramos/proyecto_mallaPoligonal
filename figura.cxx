#include "figura.h"
#include <string>
#include <set>
#include <iostream>


Figura::Figura(const std::string & n): nombre(n){}

void Figura:: agregarCara(const Cara & c){
    caras.push_back(c);
}
void Figura:: agregarVertice(const Vertice &v){
    vertices.push_back(v);
}

std::deque<Cara>&Figura:: getCaras(){
    return caras;
}
std::deque<Vertice>& Figura::getVertices(){
    return vertices;
    
}

std::deque<Vertice> Figura::envolventeObjeto(){
    int mayorX, menorX, mayorY, menorY, mayorZ, menorZ;
    std::deque<Vertice>::iterator it=vertices.begin();
    for(; it!=vertices.end(); it++){
        if(it->getX()>mayorX){
            mayorX=it->getX();
        }else if(it->getX()<menorX){
            menorX=it->getX();
        }
        if(it->getY()>mayorY){
            mayorY=it->getY();
        }else if(it->getY()<menorY){
            menorY=it->getY();
        }
        if(it->getZ()>mayorZ){
            mayorZ=it->getZ();
        }else if(it->getZ()<menorZ){
            menorZ=it->getZ();
        }
    }
    Vertice vMayor(mayorX, mayorY, mayorZ, 0);
    Vertice vMenor(menorX, menorY, menorZ, 1);
    //std::cout<<vMayor.getX()<<" "<<vMayor.getY()<<" "<<vMayor.getZ()<<std::endl;
    //std::cout<<vMenor.getX()<<" "<<vMenor.getY()<<" "<<vMayor.getZ()<<std::endl;
    std::deque<Vertice> envolvente;
    envolvente.push_back(vMayor);
    envolvente.push_back(vMenor);
    
    return envolvente;
}

int Figura:: buscarIndiceVertice(float x, float y, float z){
    std::deque<Vertice>::iterator it=vertices.begin();
    for(; it!= vertices.end(); it++){
        if(it->getX()==x && it->getY()==y && it->getZ()==z){
            return it->getIndice();
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
    return vertices.size();
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
    
    
/*
int Figura::getNAristasFigura() const{
    std::deque<Arista>aristas;
    std::deque<Arista>aristasTemp;
    std::deque<Cara>::const_iterator it=caras.begin();
    std::deque<Arista>::const_iterator itArista;
        std::deque<Arista>::const_iterator itA;

    bool repetida;

    int total=0;
    for(; it!=caras.end(); it++){
        aristasTemp=it->getAristas;
        if(aristas.size<1){
            for(itArista=aristasTemp.begin(); itArista!=aristasTemp.end(); itArista++){
                aristas.push_back(*itArista);
            }
        }else{
            for(itArista=aristasTemp.begin(); itArista!= aristasTemp.end(); itArista++){
                for(itA=aristas.begin(); itA!=aristas.end(); itA++){
                    repetida=itArista->compararArista(itA->getVertice1(), itA->getVertice2);
                    if(repetida==false){
                        aristas.push_back(*itArista);
                    }
                }
            }
        }
        
        
    }
    for(itA=aristas.begin(); itA!= aristas.end(); itA++){
        total++;
    }
    return total;
}
*/