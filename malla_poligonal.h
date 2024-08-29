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
  void envolvente();
  Figura envolventeObjeto(const std::string &nombre_objeto);
  void descargarObjeto(const std::string &nombre_objeto);
  void guardarObjeto(const std::string &nombre_objeto,
                     const std::string &nombre_archivo);
  void v_cercanos_caja(const std::string &nombre_objeto);

  // Funciones complementarias
  Figura *getFigura(
      const std::string &nombreFigura); // Retorna una figura por su nombre
  bool figuraExiste(const std::string &nombreFigura);
  int getPosicionFigura(const std::string &nombreFigura);
  std::deque<Figura> getFiguras() const;
  void eliminarFigura(int posicion);
  void agregarFigura(const Figura &figura);

  // Plantillas de funciones
  template <class I>
  void v_cercano_objeto(I px, I py, I pz, const std::string &nombre_objeto);

  template <class I> void v_cercano(I px, I py, I pz);

  template <class I>
  void ruta_corta(I i1, I i2, const std::string &nombre_objeto);

  template <class I>
  void ruta_corta_centro(I i1, const std::string &nombre_objeto);
};

#include "malla_poligonal.hxx" // Incluir las definiciones de las plantillas

#endif // MALLA_POLIGONAL_H
