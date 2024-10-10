#include "ManejadorArchivos.h"
#include "Sistema.h"
#include "arista.h"
#include "cara.h"
#include "figura.h"
#include "malla_poligonal.h"
#include "vertice.h"
#include "ArbolKD.h"
#include "NodoKD.h"
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
                    std::cout << "Hay " << figuras.size() << " objetos en memoria: " << std::endl;
                    std::deque<Figura>::iterator it = figuras.begin();
                    for (; it != figuras.end(); it++) {
                        std::cout << it->getNombre() << " ";
                        std::cout << "contiene " << it->getNVertices() << " vertices, ";
                        std::cout << it->getNAristasFigura() << " aristas y " << it->getNCaras() << " caras" << std::endl;
                    }
                }
            } else if (comando == "envolvente") {
                try {
                    Figura figura =malla.envolvente();
                    malla.agregarFigura(figura);
                    std::cout << "La caja envolvente de los objetos en memoria se ha "
                                 "generado con el nombre env_global y se ha agregado a "
                                 "los objetos en memoria." << std::endl;
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
                    std::cout << "El objeto ha sido cargado exitosamente desde el archivo \"" << partes[1] << "\"." << std::endl;
                } catch (const std::exception &e) {
                    std::cerr << "Error al cargar el archivo: " << e.what() << std::endl;
                }
            } else if (comando == "envolvente") {
                try {
                    Figura figura = malla.envolventeObjeto(partes[1]);
                    malla.agregarFigura(figura);
                    std::cout << "La caja envolvente del objeto \"" << partes[1] << " se ha generado con el nombre \"env_" << partes[1] << "\" y se ha agregado a los objetos en memoria." << std::endl;
                } catch (const std::exception &e) {
                    std::cerr << "Error al generar el envolvente del objeto: " << e.what() << std::endl;
                }
            } else if (comando == "descargar") {
                if (malla.figuraExiste(partes[1])) {
                    malla.descargarObjeto(partes[1]);
                    std::cout << "El objeto \"" << partes[1] << "\" ha sido eliminado de la memoria de trabajo." << std::endl;
                } else {
                    std::cerr << "El objeto " << partes[1] << " no ha sido cargado en memoria" << std::endl;
                }
            } else if (comando == "v_cercanos_caja") {
                malla.envolvente();
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
                    std::cout << "La información del objeto \"" << partes[1] << "\" ha sido guardada exitosamente en el archivo \"" << partes[2] << "\"" << std::endl;
                } catch (const std::exception &e) {
                    std::cerr << "Error al guardar el objeto: " << e.what() << std::endl;
                }
            } else if (comando == "ruta_corta_centro") {
                //malla.ruta_corta_centro(stoi(partes[1]), partes[2]);
            } else {
                cout << "El comando \"" << comando << "\" no es válido" << endl;
            }
        } else if (partes.size() == 4) {
            if (comando == "v_cercano") {
                try {
                    Figura fig = malla.verticeCercano(stof(partes[1]), stof(partes[2]), stof(partes[3]));
                    float mejorDistancia = -1;
                    Vertice v = fig.getVertices()->verticeCercano(stof(partes[1]), stof(partes[2]), stof(partes[3]), 0, mejorDistancia);
                    float distancia = v.calcularDistancia(stof(partes[1]), stof(partes[2]), stof(partes[3]));
                    std::cout << "El vértice " << v.getIndice() << " (" << v.getX() << ", " << v.getY() << ", " << v.getZ() 
                              << ") del objeto " << fig.getNombre() << " es el más cercano al punto ("
                              << partes[1] << ", " << partes[2] << ", " << partes[3] << "), a una distancia de "
                              << distancia << "." << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << "\n" << std::endl;
                }
            }
        } else if (partes.size() == 5) {
            if (comando == "v_cercano") {
                float x = stof(partes[1]);
                float y = stof(partes[2]);
                float z = stof(partes[3]);
                std::string nombreFigura = partes[4];
                Vertice v = malla.verticeCercanoObjeto(x, y, z, nombreFigura);
                if (v.getIndice() != -1) {
                    std::cout << "El vertice " << v.getIndice() << " (" << v.getX() << ", " << v.getY() << ", " << v.getZ() 
                              << ") del objeto " << nombreFigura << ", es el más cercano al punto dado" << std::endl;
                } else {
                    std::cout << "No se encontró ningún vértice cercano." << std::endl;
                }
            } else {
                std::cout << "El comando \"" << comando << "\" no es válido" << std::endl;
            }
        } else {
            std::cout << "Error: Comando no reconocido" << std::endl;
        }
    }
}
