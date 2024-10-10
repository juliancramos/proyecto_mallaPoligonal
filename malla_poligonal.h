#ifndef MALLA_POLIGONAL_H
#define MALLA_POLIGONAL_H

#include "figura.h"
#include <deque>
#include <string>
#include <vector>

class ManejadorArchivos;

class MallaPoligonal {
private:
  std::deque<Figura> figuras;

public:

  void cargar(const std::string &nombre_archivo, MallaPoligonal &malla);
  void listado();
  Figura envolvente();
  Figura envolventeObjeto(const std::string &nombre_objeto);
  void descargarObjeto(const std::string &nombre_objeto);
  void guardarObjeto(const std::string &nombre_objeto, const std::string &nombre_archivo);
  std::deque<Vertice>  v_cercanos_caja(const std::string &nombre_objeto, const std::deque<Vertice>&preOrdenCaja);

  // Funciones complementarias
  Figura *getFigura(const std::string &nombreFigura); // Retorna una figura por su nombre
  bool figuraExiste(const std::string &nombreFigura);
  int getPosicionFigura(const std::string &nombreFigura);
  std::deque<Figura> getFiguras() const;
  void eliminarFigura(int posicion);
  void agregarFigura(const Figura &figura);

  Vertice verticeCercanoObjeto(float px, float py, float pz, const std::string&nombreObjeto);
  Figura verticeCercano(float px, float py, float pz);

  
};


#endif 
