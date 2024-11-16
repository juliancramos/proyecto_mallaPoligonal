#include <algorithm>
#include <limits>

#include "Grafo.h"

// Añadir arista entre dos nodos con un peso
template <typename T>
void Grafo<T>::agregarArista(const T& nodo1, const T& nodo2, double peso) {
    listaAdyacencia[nodo1].emplace_back(nodo2, peso); // Agregar nodo2 con peso a la lista de nodo1
    listaAdyacencia[nodo2].emplace_back(nodo1, peso); // Agregar nodo1 con peso a la lista de nodo2 (para grafos no dirigidos)
}

// Mostrar el Grafo con pesos
template <typename T>
void Grafo<T>::mostrarGrafo() const {
    for (const auto& entry : listaAdyacencia) {
        const auto& nodo = entry.first;
        const auto& vecinos = entry.second;
        std::cout << "Nodo: " << nodo << " -> ";
        //for (const auto& [vecino, peso] : vecinos) { //Para c++ 17
        for (const auto& vecino: vecinos) {
            std::cout << "(" << vecino.first << ", peso: " << vecino.second << ") ";
        }
        std::cout << std::endl;
    }
}

// DFS recursivo
template <typename T>
void Grafo<T>::dfs(const T& nodo, std::set<T>& visitados) const {
    visitados.insert(nodo);
    std::cout << nodo << " "; // Imprimir el nodo visitado

    for (const auto& vecino : listaAdyacencia.at(nodo)) {
        if (visitados.find(vecino) == visitados.end()) {
            dfs(vecino, visitados);
        }
    }
}

// Inicia el DFS y llama a la función recursiva
template <typename T>
void Grafo<T>::iniciarDFS(const T& nodoInicial) const {
    std::set<T> visitados; // Lleva registro de los nodos visitados
    dfs(nodoInicial, visitados); // Arranca con el nodo inicial
}

// BFS (anchura)
template <typename T>
void Grafo<T>::bfs(const T& nodoInicial) const {
    std::set<T> visitados; 
    std::queue<T> cola; // Nodos a visitar

    visitados.insert(nodoInicial);
    cola.push(nodoInicial); // Añade el nodo inicial a la cola

    while (!cola.empty()) {
        T nodo = cola.front();
        cola.pop();
        std::cout << nodo << " ";

            for (const auto& vecino : listaAdyacencia.at(nodo)) {
            if (visitados.find(vecino) == visitados.end()) {
                visitados.insert(vecino); // Marca como visitado
                cola.push(vecino); // Añade el vecino a la cola
            }
        }
    }
}

//Se usó Bellmand Ford -> Esto porque es desde un solo vértice de origen a todos los demás
template <typename T>
std::pair<std::vector<T>, double> Grafo<T>::rutaMasCorta(const T& origen, const T& destino) const {
    std::unordered_map<T, double> distancias;
    std::unordered_map<T, T> predecesores;

    for (typename std::unordered_map<T, std::vector<std::pair<T, double>>>::const_iterator it = listaAdyacencia.begin(); it != listaAdyacencia.end(); ++it) {
        distancias[it->first] = std::numeric_limits<double>::infinity();
    }
    distancias[origen] = 0.0;

    // Relajar las aristas V-1 veces
    for (size_t i = 0; i < listaAdyacencia.size() - 1; ++i) {
        for (const auto& par : listaAdyacencia) {
            T u = par.first;
            for (const auto& vecino : par.second) {
                T v = vecino.first;
                double peso = vecino.second;
                if (distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    predecesores[v] = u;
                }
            }
        }
    }

    // Verificar ciclos negativos
    for (const auto& par : listaAdyacencia) {
        T u = par.first;
        for (const auto& vecino : par.second) {
            T v = vecino.first;
            double peso = vecino.second;
            if (distancias[u] + peso < distancias[v]) {
                throw std::runtime_error("El grafo contiene un ciclo negativo");
            }
        }
    }

    std::vector<T> ruta;
    double distanciaTotal = distancias[destino];

    if (distanciaTotal == std::numeric_limits<double>::infinity()) {
        throw std::runtime_error("No se encontró una ruta al destino.");
    }

    T at = destino;
    while (at != origen) {
        ruta.push_back(at);
        at = predecesores[at];
    }
    ruta.push_back(origen);
    std::reverse(ruta.begin(), ruta.end());

    return {ruta, distanciaTotal};
}
