#ifndef __FUNCIONES__HXX__
#define __FUNCIONES__HXX__
#include <iostream>
#include <string>

using namespace std;

// Parte 2.2
template <class I>
void v_cercano_objeto(I px, I py, I pz, const string &nombre_objeto) {
    cout << "El vertice i (vx ,vy ,vz ) del objeto \"" << nombre_objeto
         << "\" es el más cercano al punto (" << px << ", " << py << ", " << pz
         << " ), a una distancia de valor_distancia." << endl;
}

template <class I>
void v_cercano(I px, I py, I pz) {
    cout << "El vertice i (vx ,vy ,vz ) del objeto NOMBRE_OBJETO es el más cercano al punto ("
         << px << ", " << py << ", " << pz << " ), a una distancia de valor_distancia." << endl;
}

// Parte 2.3
template <class I>
void ruta_corta(I i1, I i2, const string &nombre_objeto) {
    cout << "La ruta más corta que conecta los vertices \"" << i1 << "\" y \"" << i2
         << "\" del objeto \"" << nombre_objeto << "\" pasa por: i1 ,v1 ,v2 ,...,vn ,i2 ; con una longitud de valor_distancia." << endl;
}

template <class I>
void ruta_corta_centro(I i1, const string &nombre_objeto) {
    cout << "La ruta más corta que conecta el vertice \"" << i1
         << "\" con el centro del objeto \"" << nombre_objeto
         << "\", ubicado en ct (ctx, cty, ctz ), pasa por: i1 ,v1 ,v2 ,...,ct ; con una longitud de valor_distancia." << endl;
}

#endif // __FUNCIONES__HXX__
