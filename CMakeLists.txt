cmake_minimum_required(VERSION 3.10)  # Versión mínima de CMake
project(MallaPoligonal)  # Nombre del proyecto

# Estándar de C++
set(CMAKE_CXX_STANDARD 11)  # Usamos C++11 como en tu compilación actual

# Lista de archivos fuente
set(SOURCES
        main.cpp
        arista.cxx
        figura.cxx
        malla_poligonal.cxx
        vertice.cxx
        ManejadorArchivos.cxx
        Sistema.cxx
        cara.cxx
)
#Lista de encabezados
set(HEADERS
        arista.h
        figura.h
        malla_poligonal.h
        vertice.h
        ManejadorArchivos.h
        Sistema.h
        cara.h
)

# Creación del ejecutable
add_executable(p ${SOURCES} ${HEADERS})
