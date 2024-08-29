#include "ManejadorArchivos.h"
#include "Sistema.h"
#include "arista.h"
#include "cara.h"
#include "figura.h"
#include "malla_poligonal.h"
#include "vertice.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string entrada, comando, subcomando;
  vector<string> partes;
  MallaPoligonal malla;
  std::deque<Figura> figuras;
  std::deque<Vertice> vertices;
  std::deque<Cara> caras;
  std::deque<Arista> aristas;

  while (comando != "salir") {
    cout << "$ ";
    getline(cin, entrada);
    partes = Sistema::separarComando(entrada);

    if (partes.empty()) {
      cerr << "Error: Comando vacío" << endl;
      continue;
    }

    comando = partes[0];

    if (partes.size() == 1) {
      if (comando == "ayuda") {
        Sistema::ayuda(comando);
      } else if (comando == "listado") {
        figuras = malla.getFiguras();
        if (figuras.size() < 1) {
          std::cerr << "Ningun objeto ha sido cargado en memoria" << std::endl;
        } else {
          std::cout << "Hay " << figuras.size()
                    << " objetos en memoria: " << std::endl;
          std::deque<Figura>::iterator it = figuras.begin();
          for (; it != figuras.end(); it++) {
            std::cout << it->getNombre() << " ";
            std::cout << "contiene " << it->getNVertices() << " vertices, ";
            std::cout << it->getNAristasFigura() << " aristas y "
                      << it->getNCaras() << " caras" << std::endl;
          }
        }
        // malla.listado();
      } else if (comando == "envolvente") {
        try {
          malla.envolvente();
          std::cout << "La caja envolvente de los objetos en memoria se ha "
                       "generado con el nombre env_global y se ha agregado a "
                       "los objetos en memoria."
                    << std::endl;
        } catch (const std::exception &e) {
          std::cerr << "Error: " << e.what() << std::endl;
        }

      } else if (comando == "salir") {
        cout << "Saliendo del sistema..." << endl;
      } else {
        cout << "El comando \"" << comando << "\" no es válido" << endl;
      }
    } else if (partes.size() == 2) {
      if (comando == "cargar") {
        try {
          malla.cargar(partes[1], malla);
          std::cout
              << "El objeto ha sido cargado exitosamente desde el archivo \""
              << partes[1] << "\"." << std::endl;
        } catch (const std::exception &e) {
          std::cerr << "Error al cargar el archivo: " << e.what() << std::endl;
        }

      } else if (comando == "envolvente") {
        try {
          Figura figura = malla.envolventeObjeto(partes[1]);
          malla.agregarFigura(figura);
          std::cout << "La caja envolvente del objeto \"" << partes[1]
                    << " se ha generado con el nombre \"env_" << partes[1]
                    << "\" y se ha agregado a los objetos en memoria."
                    << std::endl;
        } catch (const std::exception &e) {
          std::cerr << "Error al generar el envolvente del objeto: " << e.what()
                    << std::endl;
        }
      } else if (comando == "descargar") {
        if (malla.figuraExiste(partes[1])) {
          malla.descargarObjeto(partes[1]);
          std::cout << "El objeto \"" << partes[1]
                    << "\" ha sido eliminado de la memoria de trabajo."
                    << std::endl;
        } else {
          std::cerr << "El objeto " << partes[1]
                    << " no ha sido cargado en memoria" << std::endl;
        }

      } else if (comando == "v_cercanos_caja") {
        malla.v_cercanos_caja(partes[1]);
      } else if (comando == "ayuda") {
        Sistema::ayuda(partes[1]);
      } else {
        cout << "El comando \"" << comando << "\" no es válido" << endl;
      }
    } else if (partes.size() == 3) {
      if (comando == "guardar") {
        try {
          malla.guardarObjeto(partes[1], partes[2]);
          std::cout << "La información del objeto \"" << partes[1]
                    << "\" ha sido guardada exitosamente en el archivo \""
                    << partes[2] << "\"" << std::endl;
        } catch (const std::exception &e) {
          std::cerr << "Error al guardar el objeto: " << e.what() << std::endl;
        }

      } else if (comando == "ruta_corta_centro") {
        malla.ruta_corta_centro(stoi(partes[1]), partes[2]);
      } else {
        cout << "El comando \"" << comando << "\" no es válido" << endl;
      }
    } else if (partes.size() == 4) {
      if (comando == "v_cercano") {
        malla.v_cercano(stoi(partes[1]), stoi(partes[2]), stoi(partes[3]));
      } else if (comando == "ruta_corta") {
        malla.ruta_corta(stoi(partes[1]), stoi(partes[2]), partes[3]);
      } else {
        cout << "El comando \"" << comando << "\" no es válido" << endl;
      }
    } else if (partes.size() == 5) {
      if (comando == "v_cercano") {
        malla.v_cercano_objeto(stoi(partes[1]), stoi(partes[2]),
                               stoi(partes[3]), partes[4]);
      } else {
        cout << "El comando \"" << comando << "\" no es válido" << endl;
      }
    } else {
      cout << "Error: Comando no reconocido" << endl;
    }
  }

  return 0;
}
