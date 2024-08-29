#include <vector>
#include <sstream>
#include <iostream>

#include "Sistema.h"
std::vector<std::string> Sistema::separarComando(const std::string &entrada) {
    std::vector<std::string> partes;
    std::istringstream stream(entrada);
    std::string parte;

    while (stream >> parte) {
        partes.push_back(parte);
    }
    return partes;
}

void Sistema::ayuda(const std::string &comando) {
    if (comando.empty() || comando == "ayuda") {
        std::cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n";
        std::cout << "            Comandos disponibles             \n";
        std::cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n\n";
        std::cout << "\n\033[1mGestionar de información básica de objetos 3D, a partir de archivos de mallas.\033[0m\n";
        std::cout << "1.Cargar\n";
        std::cout << "2.Listado\n";
        std::cout << "3.Envolvente\n";
        std::cout << "4.Descargar\n";
        std::cout << "5.Guardar\n";
        std::cout << "6.Salir\n\n";
        std::cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n\n";
        std::cout << "\n\033[1mIdentificar puntos (vértices) más cercanos en los objetos.\033[0m\n";
        std::cout << "7.v_cercano\n";
        std::cout << "⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆⋆⁺₊⋆ ☀︎ ⋆⁺₊⋆\n\n";
        std::cout << "\n\033[1mIdentificar las rutas más cortas que conectan diferentes vértices dentro de los objetos.\033[0m\n";
        std::cout << "8.ruta_corta\n";
    } 
    else if (comando == "cargar") {
        std::cout << "\n\033[1mDescripción: cargar nombre_archivo\033[0m\n";
        std::cout << "Carga en memoria la información del objeto contenido en el archivo especificado. El comando debe estructurar la información a partir del archivo de forma que sea fácil recuperar los datos posteriormente.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "El objeto ha sido cargado exitosamente desde el archivo especificado.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "1. Archivo vacío o incompleto: El archivo no contiene un objeto 3D válido.\n";
        std::cout << "2. Archivo no existe: El archivo no existe o es ilegible.\n";
        std::cout << "3. Objeto ya existe: El objeto ya ha sido cargado en memoria.\n\n";
    } 
    else if (comando == "listado") {
        std::cout << "\n\033[1mDescripción\033[0m\n";
        std::cout << "Lista los objetos cargados actualmente en memoria, junto con la información básica de cada uno: cantidad de puntos, de aristas y de caras.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "Hay n objetos en memoria:\n nombre_objeto_1 contiene n_1 vertices, a_1 aristas y c_1 caras.\n nombre_objeto_2 contiene n_2 vertices, a_2 aristas y c_2 caras...\n\n";
        std::cout << "\033[1mMensajes de error (Memoria vacía)\033[0m\n";
        std::cout << "Ningún objeto ha sido cargado en memoria.\n\n";
    } 
    else if (comando == "envolvente") {
        std::cout << "\n\033[1mDescripción: Envolvente\033[0m\n";
        std::cout << "Calcula la caja envolvente que incluye a todos los objetos cargados actualmente en memoria. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_global.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "La caja envolvente de los objetos en memoria se ha generado con el nombre env_global y se ha agregado a los objetos en memoria.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "Ningún objeto ha sido cargado en memoria.\n\n";
        std::cout << "\n\033[1mEnvolvente nombre_objeto\033[0m\n";
        std::cout << "Calcula la caja envolvente del objeto identificado por nombre_objeto. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "La caja envolvente del objeto nombre_objeto se ha generado con el nombre env_nombre_objeto y se ha agregado a los objetos en memoria.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";
    }  
    else if (comando == "descargar") {
        std::cout << "\n\033[1mDescripción: Descargar nombre_objeto\033[0m\n";
        std::cout << "Descarga de la memoria toda la información básica del objeto identificado por nombre_objeto.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "El objeto nombre_objeto ha sido eliminado de la memoria de trabajo.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";
    } 
    else if (comando == "guardar") {
        std::cout << "\n\033[1mDescripción: Guardar nombre_objeto nombre_archivo\033[0m\n";
        std::cout << "Escribe en un archivo de texto, identificado por nombre_archivo, la información básica del objeto identificado por nombre_objeto.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "La información del objeto nombre_objeto ha sido guardada exitosamente en el archivo nombre_archivo.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n\n";
    } 
    else if (comando == "v_cercano") {
        std::cout << "\n\033[1mDescripción: v_cercano px py pz nombre_objeto\033[0m\n";
        std::cout << "Identifica el vértice del objeto nombre_objeto más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px , py y pz . Informa en pantalla el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "El vértice más cercano al punto (px, py, pz) ha sido encontrado y su información ha sido mostrada en pantalla.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n";
        std::cout << "Las coordenadas px, py y pz no son válidas.\n\n";
    }
    else if (comando == "v_cercano_caja") {
        std::cout << "\n\033[1mDescripción: v_cercano_caja px py pz nombre_objeto\033[0m\n";
        std::cout << "Identifica el vértice del objeto nombre_objeto más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px , py y pz, y se encuentra dentro de la caja envolvente del objeto. Informa en pantalla el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "El vértice más cercano al punto (px, py, pz) dentro de la caja envolvente ha sido encontrado y su información ha sido mostrada en pantalla.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n";
        std::cout << "Las coordenadas px, py y pz no son válidas.\n";
        std::cout << "El objeto no tiene una caja envolvente definida.\n\n";
    }
    else if (comando == "ruta_corta") {
        std::cout << "\n\033[1mDescripción: ruta_corta nombre_objeto\033[0m\n";
        std::cout << "Calcula la ruta más corta entre todos los vértices del objeto nombre_objeto. La ruta se basa en las aristas del objeto. La ruta más corta es informada en pantalla.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "La ruta más corta entre los vértices del objeto nombre_objeto ha sido calculada y mostrada en pantalla.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n";
        std::cout << "No se puede calcular la ruta más corta debido a que el objeto no tiene aristas definidas.\n\n";
    }
    else if (comando == "ruta_corta_centro") {
        std::cout << "\n\033[1mDescripción: ruta_corta_centro nombre_objeto\033[0m\n";
        std::cout << "Calcula la ruta más corta entre los vértices del objeto nombre_objeto desde y hacia el centroide del objeto. La ruta se basa en las aristas del objeto. La ruta más corta es informada en pantalla.\n\n";
        std::cout << "\n\033[1mMensaje de éxito\033[0m\n";
        std::cout << "La ruta más corta entre los vértices del objeto nombre_objeto desde y hacia el centroide ha sido calculada y mostrada en pantalla.\n\n";
        std::cout << "\033[1mMensajes de error\033[0m\n";
        std::cout << "El objeto nombre_objeto no ha sido cargado en memoria.\n";
        std::cout << "No se puede calcular la ruta más corta debido a que el objeto no tiene aristas definidas.\n\n";
    }
    else {
        std::cout << "Comando desconocido: " << comando << ". Use 'ayuda' para ver la lista de comandos disponibles.\n";
    }
}