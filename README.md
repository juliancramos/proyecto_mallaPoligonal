# Polygon Mesh System

A command-line application for loading, managing, and querying 3D polygon mesh objects. The system reads mesh files, stores them using a hierarchy of data structures, and provides operations like bounding box generation, nearest-vertex search using a KD-Tree, and shortest-path calculation using the Bellman-Ford algorithm.

## How It Works

The system is built around the concept of a **polygon mesh** (`MallaPoligonal`), which is a collection of 3D figures. Each level contains the next:

1. **Polygon Mesh** (`MallaPoligonal`): The top-level container. It holds all the figures loaded in memory and manages operations across them (like finding the nearest vertex among all figures, or computing a global bounding box).

2. **Figure** (`Figura`): Represents a single 3D object (e.g., a cube, a pyramid). Each figure is made up of faces, and internally stores its vertices in a **KD-Tree** for spatial queries and its connectivity in a **weighted graph** for shortest-path calculations.

3. **Face** (`Cara`): A flat surface of the figure, defined by a group of vertices. Each face automatically generates its **edges** by connecting consecutive vertices.

4. **Edge** (`Arista`): A connection between two vertices, represented by their indices. Each edge stores the **Euclidean distance** between its two vertices.

5. **Vertex** (`Vertice`): The most basic element — a point in 3D space with coordinates `x`, `y`, `z` and a unique index.

```
Polygon Mesh
└── Figure 1, Figure 2, ...
    └── Face 1, Face 2, ...
        └── Edge 1, Edge 2, ...
            └── Vertex A ↔ Vertex B
```

When a mesh file is loaded, the system parses the vertices and faces, computes the Euclidean distance for every edge, and builds both the KD-Tree (for neighbor searches) and the graph (for shortest-path queries) automatically.

---


### Custom C++ Templates

The three main data structures (`ArbolKD`, `NodoKD`, `Grafo`) are **hand-written C++ class templates**. Their definitions live in `.hxx` files, which are included at the bottom of each `.h` header.

| Template | Header | Implementation | Used with |
|---|---|---|---|
| `NodoKD<T>` | `NodoKD.h` | `NodoKD.hxx` | `Vertice` |
| `ArbolKD<T>` | `ArbolKD.h` | `ArbolKD.hxx` | `Vertice` |
| `Grafo<T>` | `Grafo.h` | `Grafo.hxx` | `int` |

---

## Data Structures

### KD-Tree (`ArbolKD<Vertice>`)

A 3-dimensional KD-Tree used to store the vertices of each figure. The tree splits by a different coordinate at each level: `x → y → z → x → ...`

**Insertion** (`NodoKD::insertar`): Compares the new vertex against the current node using the coordinate for the current depth (`depth % 3`). Goes left or right through pointers (`hijoIzq`, `hijoDer`), creating new nodes when needed. This is done recursively.

**Nearest-neighbor search** (`ArbolKD::buscarVerticeCercano`): Finds the closest vertex to a given 3D point. It works recursively by:
1. Going into the subtree that is closer to the query point first.
2. Updating the best match if the current node is closer.
3. Only checking the other subtree if the distance to the splitting plane is less than the current best — this avoids checking parts of the tree that can't have a closer point.

**Finding min/max** (`encontrarMinimo`, `encontrarMaximo`): Goes through both subtrees recursively to find the vertex with the smallest or largest coordinates in all three dimensions. This is used to compute bounding boxes.

**Tree traversals**: Pre-order, in-order, post-order (all recursive), and level-order (uses a `std::queue`). The pre-order traversal returns a `std::deque<T>` and is used when saving objects back to files.

### Weighted Graph (`Grafo<int>`)

An undirected graph with weights, used to represent how vertices are connected within a figure. Stored as an adjacency list using `std::unordered_map<int, std::vector<std::pair<int, double>>>`.

**Building the graph** (`Figura::llenarGrafo`): Goes through all faces and their edges, adding each edge to the graph with its Euclidean distance as weight. Uses a `std::set` to avoid adding duplicate edges (since two faces can share the same edge).

**Shortest path — Bellman-Ford** (`Grafo::rutaMasCorta`): Finds the shortest path between two vertices. The algorithm:
1. Sets all distances to infinity, except the source which starts at zero.
2. Repeats `|V| - 1` times: for each edge, checks if going through it gives a shorter path (relaxation).
3. Checks for negative cycles (to detect errors).
4. Rebuilds the path using a map of predecessors.

### Other Structures

- **`std::deque`**: Used for ordered collections of figures, faces, edges, and vertices.
- **Pointers (`NodoKD<T>*`, `ArbolKD<Vertice>*`)**: Raw pointers are used to manage tree nodes and allow the tree to grow dynamically. Each `Figura` owns its KD-Tree through a pointer.

---


## CLI Commands

| Command | Arguments | Description |
|---|---|---|
| `cargar` | `filename` | Load a mesh object from a `.txt` file |
| `listado` | — | List all loaded objects with vertex/edge/face counts |
| `envolvente` | `[object_name]` | Compute bounding box (for one object or all) |
| `descargar` | `object_name` | Remove an object from memory |
| `guardar` | `object_name filename` | Save an object to a `.txt` file |
| `v_cercano` | `px py pz [object_name]` | Find the nearest vertex to a 3D point |
| `v_cercanos_caja` | `object_name` | Find nearest vertices to bounding box corners |
| `ruta_corta` | `i1 i2 object_name` | Shortest path between two vertices (Bellman-Ford) |
| `ruta_corta_centro` | `i1 object_name` | Shortest path from a vertex to the centroid |
| `ayuda` | `[command]` | Show help |
| `salir` | — | Exit |

---

## Project Structure

```
├── src/                        # Source files (.cxx, .cpp)
│   ├── main.cpp                # Entry point and command handler
│   ├── ManejadorArchivos.cxx   # File reading and writing
│   ├── Sistema.cxx             # Command parsing and help text
│   ├── malla_poligonal.cxx     # Mesh-level operations
│   ├── figura.cxx              # Figure operations (bounding box, centroid, graph)
│   ├── cara.cxx                # Face and edge assignment
│   ├── arista.cxx              # Edge constructor and getters
│   └── vertice.cxx             # Vertex distance and operators
│
├── include/                    # Header files (.h, .hxx)
│   ├── ArbolKD.h / .hxx        # KD-Tree template
│   ├── NodoKD.h / .hxx         # KD-Tree node template
│   ├── Grafo.h / .hxx          # Weighted graph template (Bellman-Ford, DFS, BFS)
│   ├── figura.h                # Figure class
│   ├── malla_poligonal.h       # Polygon mesh class
│   ├── cara.h                  # Face class
│   ├── arista.h                # Edge class
│   ├── vertice.h               # Vertex class (3D point)
│   ├── ManejadorArchivos.h     # File handler
│   └── Sistema.h               # System utilities
│
├── data/                       # Sample mesh files
│   ├── cube.txt
│   ├── pyramid.txt
│   ├── tetrahedron.txt
│   ├── octahedron.txt
│   ├── icosahedron.txt
│   ├── rectangular_prism.txt
│   └── rotated_rectangular_prism.txt
│
├── docs/                       # Documentation
│   └── Apuntes.txt
│
├── CMakeLists.txt
└── .gitignore
```

---

## Setup

### Requirements

- C++ compiler with C++11 support (g++, clang++, or MSVC)
- CMake 3.10+ (optional)

### Build with g++

```bash
g++ -std=c++11 -Iinclude src/*.cxx src/main.cpp -o malla_poligonal
```

### Build with CMake

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Run

```bash
./malla_poligonal
```

### Example Session

```
$ cargar data/cube.txt
El objeto ha sido cargado exitosamente desde el archivo "data/cube.txt".
$ listado
Hay 1 objetos en memoria:
Cube contiene 8 vertices, 12 aristas y 12 caras
$ envolvente Cube
La caja envolvente del objeto "Cube" se ha generado con el nombre "env_Cube" y se ha agregado a los objetos en memoria.
$ ruta_corta 0 7 Cube
La ruta más corta que conecta los vértices 0 y 7 del objeto Cube pasa por: 0 2 3 7 ; con una longitud de 5.46.
$ salir
```

### Mesh File Format

```
ObjectName
num_vertices
x1 y1 z1
x2 y2 z2
...
num_vertices_face1 idx1 idx2 idx3
num_vertices_face2 idx1 idx2 idx3 idx4
...
-1
```

Vertices are listed first (starting from index 0), followed by face definitions where each line starts with the number of vertices in that face, then their indices. The file ends with `-1`.
