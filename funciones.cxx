#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "header.h"

using namespace std;
vector<string> separarComando(const string &entrada) {
    vector<string> partes;
    istringstream stream(entrada);
    string parte;

    while (stream >> parte) {
        partes.push_back(parte);
    }
    return partes;
}

void ayuda(const string &comando) {
    if (comando.empty() || comando == "ayuda") {
        cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n";
        cout << "            Comandos disponibles             \n";
        cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n\n";
        cout << "\n\033[1mGestionar de información básica de objetos 3D, a partir de archivos de mallas.\033[0m\n";
        cout << "1.Cargar\n";
        cout << "2.Listado\n";
        cout << "3.Envolvente\n";
        cout << "4.Descargar\n";
        cout << "5.Guardar\n";
        cout << "6.Salir\n\n";
        cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n\n";
        cout << "\n\033[1mIdentificar puntos (vértices) más cercanos en los objetos.\033[0m\n";
        cout << "7.v_cercano\n";
        cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n\n";
        cout << "\n\033[1mIdentificar las rutas más cortas que conectan diferentes vértices dentro de los objetos.\033[0m\n";
        cout << "8.ruta_corta\n";
    } 
    else if (comando == "cargar") {
        cout << "\n\033[1mDescripción: cargar nombre_archivo\033[0m\n";
        cout << "Carga en memoria la información del objeto contenido en el archivo especificado. El comando debe estructurar la información a partir del archivo de forma que sea fácil recuperar los datos posteriormente.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "El objeto ha sido cargado exitosamente desde el archivo especificado.\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "1. Archivo vacío o incompleto: El archivo no contiene un objeto 3D válido.\n";
        cout << "2. Archivo no existe: El archivo no existe o es ilegible.\n";
        cout << "3. Objeto ya existe: El objeto ya ha sido cargado en memoria.\n\n";
    } 
    else if (comando == "listado") {
        cout << "\n\033[1mDescripción\033[0m\n";
        cout << "Lista los objetos cargados actualmente en memoria, junto con la información básica de cada uno: cantidad de puntos, de aristas y de caras.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "Hay n objetos en memoria:\n nombre_objeto_1 contiene n_1 vertices, a_1 aristas y c_1 caras.\n nombre_objeto_2 contiene n_2 vertices, a_2 aristas y c_2 caras...\n\n";
        cout << "\033[1mMensajes de error (Memoria vacía)\033[0m\n";
        cout << "Ningún objeto ha sido cargado en memoria.\n\n";
    } 
        
    else if (comando == "envolvente") {
        cout << "\n\033[1mDescripción: Envolvente\033[0m\n";
        cout << "Calcula la caja envolvente que incluye a todos los objetos cargados actualmente en memoria. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_global.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "La caja envolvente de los objetos en memoria se ha generado con el nombre env_global y se ha agregado a los objetos en memoria.\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "Ningún objeto ha sido cargado en memoria.\n\n";

        cout << "\n\033[1mEnvolvente nombre_objeto\033[0m\n";
        cout << "Calcula la caja envolvente del objeto identificado por nombre_objeto. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "La caja envolvente del objeto nombre_objeto se ha generado con el nombre env_nombre_objeto y se ha agregado a los objetos en memoria.\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";
        }  
    else if (comando == "descargar") {
        cout << "\n\033[1mDescripción: Descargar nombre_objeto\033[0m\n";
        cout << "Descarga de la memoria toda la información básica del objeto identificado por nombre_objeto.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "El objeto nombre_objeto ha sido eliminado de la memoria de trabajo.\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";
    } 
    else if (comando == "guardar") {
        cout << "\n\033[1mDescripción: Guardar nombre_objeto nombre_archivo\033[0m\n";
        cout << "Escribe en un archivo de texto, identificado por nombre_archivo, la información básica del objeto identificado por nombre_objeto.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "La información del objeto nombre_objeto ha sido guardada exitosamente en el archivo nombre_archivo.\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";
    } 
    else if (comando == "v_cercano") {
        cout << "\n\033[1mDescripción: v_cercano px py pz nombre_objeto\033[0m\n";
        cout << "Identifica el vértice del objeto nombre_objeto más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px , py y pz . Informa en pantalla el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "El vertice i (vx ,vy ,vz ) del objeto nombre_objeto es el más cercano al punto (px ,py ,pz ), a una distancia de valor_distancia \n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";

        cout << "\n\033[1mDescripción: v_cercano px py pz\033[0m\n";
        cout << "Identifica el vértice del objeto nombre_objeto más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px , py y pz . Informa en pantalla el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << " El vertice i (vx ,vy ,vz ) del objeto nombre_objeto es el más cercano al punto (px ,py ,pz ), a una distancia de valor_distancia .\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "Ningun objeto ha sido cargado en memoria.\n\n";

        cout << "\n\033[1mDescripción: v_cercanos_caja nombre_objeto\033[0m\n";
        cout << "Identifica los vértices del objeto nombre_objeto más cercanos (en términos de la distancia euclidiana) a los puntos (vértices) que definen la respectiva caja envolvente del objeto. Informa en pantalla, en una tabla, las coordenadas de cada una de las esquinas de la caja envolvente, y para cada una de ellas, el índice del vértice más cercano, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra de la respectiva esquina.\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "Muestra los vertices del objeto nombre_objeto más cercanos a las esquinas de su caja envolvente en una tabla\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";
    }  
    else if (comando == "ruta_corta") {
        cout << "\n\033[1mDescripción: ruta_corta i1 i2 nombre_objeto\033[0m\n";
        cout << "Identifica los índices de los vértices que conforman la ruta más corta entre los vértices dados para el objeto nombre_objeto . La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "La ruta más corta que conecta los vertices i1 y i2 del objeto nombre_objeto pasa por: i1 ,v1 ,v2 ,...,vn ,i2 ; con una longitud de valor_distancia .\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "Objeto no existe: El objeto nombre_objeto no ha sido cargado en memoria.\n Índices iguales: Los indices de los vertices dados son iguales.\n Índices no existen: Algunos de los indices de vertices estan fuera de rango para el\n\n";

        cout << "\n\033[1mDescripción: ruta_corta_centro i1 nombre_objeto\033[0m\n";
        cout << "Identifica los índices de los vértices que conforman la ruta más corta entre el vértice dado y el centro del objeto nombre_objeto . El vértice centro del objeto se identifica calculando el centroide (coordenadas promedio) de todos los vértices del objeto, este punto es agregado entonces a la representación del objeto. Luego, se busca el vértice del objeto más cercano a ese centroide, y se conecta con el centroide por medio de una arista. Finalmente, se utiliza el mismo proceso del comando anterior para buscar la ruta más corta entre el centroide (ya conectado dentro del objeto) y el vértice dado. La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada\n\n";
        cout << "\n\033[1mMensaje de éxito\033[0m\n";
        cout << "La ruta más corta que conecta el vertice i1 con el centro del objeto nombre_objeto , ubicado en ct (ctx, cty, ctz ), pasa por: i1 ,v1 ,v2 ,...,ct ; con una longitud de valor_distancia .\n\n";
        cout << "\033[1mMensajes de error\033[0m\n";
        cout << "Objeto no existe: El objeto nombre_objeto no ha sido cargado en memoria.\nÍndice no existe: El indice de vertice esta fuera de rango para el objeto nombre_objeto .\n\n";
    } 
    else {
        cout << "Comando de ayuda no reconocido.\n\n" << endl;
    }
}

void cargar(const string &nombre_archivo) {
    cout << "El objeto ha sido cargado exitosamente desde el archivo \"" << nombre_archivo << "\"." << endl;
}

void listado() {
    cout << "Hay n objetos en memoria: " << endl;
}

void envolvente() {
    cout << "La caja envolvente de los objetos en memoria se ha generado con el nombre env_global y se ha agregado a los objetos en memoria." << endl;
}

void envolventeObjeto(const string &nombre_objeto) {
    cout << "La caja envolvente del objeto \"" << nombre_objeto << "\" se ha generado con el nombre \"" << "env_" << nombre_objeto << "\" y se ha agregado a los objetos en memoria." << endl;
}

void descargarObjeto(const string &nombre_objeto) {
    cout << "El objeto \"" << nombre_objeto << "\" ha sido eliminado de la memoria de trabajo." << endl;
}

void guardarObjeto(const string &nombre_objeto, const string &nombre_archivo) {
    cout << "La información del objeto \"" << nombre_objeto << "\" ha sido guardada exitosamente en el archivo \"" << nombre_archivo << "\"" << endl;
}

void v_cercano_objeto(const string &nombre_objeto) {
    cout << "Los vértices del objeto \"" << nombre_objeto << "\" son:\n";
}

void v_cercano(const string &nombre_objeto) {
    cout << "Los vértices del objeto \"" << nombre_objeto << "\" más cercanos a las esquinas de su caja envolvente son:\n";
}

void v_cercanos_caja(const string &nombre_objeto) {
    cout << "Los vértices del objeto \"" << nombre_objeto << "\" más cercanos a las esquinas de su caja envolvente son:\n";
}

void ruta_corta(const string &nombre_objeto) {
    cout << "Los vértices del objeto \"" << nombre_objeto << "\" más cercanos a las esquinas de su caja envolvente son:\n";
}

void ruta_corta_centro(const string &nombre_objeto) {
    cout << "Los vértices del objeto \"" << nombre_objeto << "\" más cercanos a las esquinas de su caja envolvente son:\n";
}
