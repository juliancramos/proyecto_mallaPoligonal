#ifndef _MANEJADOR_ARCHIVOS_H
#define _MANEJADOR_ARCHIVOS_H
#include "malla_poligonal.h"
#include <string>

class MallaPoligonal;

class ManejadorArchivos {
public:
  static void leerArchivo(const std::string &nombreArchivo,
                          MallaPoligonal &malla);

  static void escribirArchivoObjeto(Figura *figura,
                                    const std::string &nombreArchivo);

};

#endif