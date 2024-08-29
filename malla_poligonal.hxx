#ifndef MALLA_POLIGONAL_HXX
#define MALLA_POLIGONAL_HXX

#include <iostream>
#include <string>


// Plantillas de funciones

template <class I>
void MallaPoligonal::v_cercano_objeto(I px, I py, I pz, const std::string &nombre_objeto) {
    std::cout << "El vertice i (vx ,vy ,vz ) del objeto \"" << nombre_objeto
              << "\" es el más cercano al punto (" << px << ", " << py << ", " << pz
              << " ), a una distancia de valor_distancia." << std::endl;
}

template <class I>
void MallaPoligonal::v_cercano(I px, I py, I pz) {
    std::cout << "El vertice i (vx ,vy ,vz ) del objeto NOMBRE_OBJETO es el más cercano al punto ("
              << px << ", " << py << ", " << pz << " ), a una distancia de valor_distancia." << std::endl;
}

template <class I>
void MallaPoligonal::ruta_corta(I i1, I i2, const std::string &nombre_objeto) {
    std::cout << "La ruta más corta que conecta los vertices \"" << i1 << "\" y \"" << i2
              << "\" del objeto \"" << nombre_objeto << "\" pasa por: i1 ,v1 ,v2 ,...,vn ,i2 ; con una longitud de valor_distancia." << std::endl;
}

template <class I>
void MallaPoligonal::ruta_corta_centro(I i1, const std::string &nombre_objeto) {
    std::cout << "La ruta más corta que conecta el vertice \"" << i1
              << "\" con el centro del objeto \"" << nombre_objeto
              << "\", ubicado en ct (ctx, cty, ctz ), pasa por: i1 ,v1 ,v2 ,...,ct ; con una longitud de valor_distancia." << std::endl;
}

#endif // MALLA_POLIGONAL_HXX
