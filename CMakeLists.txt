cmake_minimum_required(VERSION 3.10)
project(MallaPoligonal)

# Estándar de C++
set(CMAKE_CXX_STANDARD 11)

# Directorio de headers
include_directories(include)

# Lista de archivos fuente
set(SOURCES
        src/main.cpp
        src/arista.cxx
        src/figura.cxx
        src/malla_poligonal.cxx
        src/vertice.cxx
        src/ManejadorArchivos.cxx
        src/Sistema.cxx
        src/cara.cxx
)

# Lista de encabezados
set(HEADERS
        include/arista.h
        include/figura.h
        include/malla_poligonal.h
        include/vertice.h
        include/ManejadorArchivos.h
        include/Sistema.h
        include/cara.h
        include/ArbolKD.h
        include/ArbolKD.hxx
        include/NodoKD.h
        include/NodoKD.hxx
        include/Grafo.h
        include/Grafo.hxx
)

# Creación del ejecutable
add_executable(malla_poligonal ${SOURCES} ${HEADERS})
